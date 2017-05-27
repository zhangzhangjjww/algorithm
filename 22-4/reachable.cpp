#include<iostream>
#include<cstdlib>
#include<limits>
#include<ctime>
#include<fstream>

const int MAX=100;

using namespace std;

struct Edge
{
    int start;
    int end;
    int value;
    bool is_tree;
    Edge* next;
    Edge(int s,int e,int v):start(s),end(e),value(v),is_tree(false),next(NULL) {}
};

enum color {white,gray,black};
struct Vertex
{
    Edge* head;
    int beg;
    int finish;
    color cc;
    int number;
    Vertex* parent;
    int L;
    int min;
    int tree;
    Vertex():head(NULL),beg(0),finish(0),cc(white),number(0),parent(NULL),L(0),min(0),tree(0) {}
};

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i) {
        sum*=base;
    }
    return sum;
}
struct Set
{
    int x; //number
    int y;  //L
    Set& operator=(const Set& s)
    {
        x=s.x;
        y=s.y;
        return *this;
    }
};
void merge(Set* a,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    Set* Left=new Set[n1+1];
    Set* Right=new Set[n2+1];
    for(int i=0;i!=n1;++i) {
        Left[i]=a[p+i];
    }
    for(int i=0;i!=n2;++i) {
        Right[i]=a[q+1+i];
    }
    Left[n1].y=numeric_limits<int>::max();
    Right[n2].y=numeric_limits<int>::max();
    int i=0,j=0;
    for(int k=p;k!=r+1;++k) {
        if(Left[i].y<=Right[j].y) {
            a[k]=Left[i];
            ++i;
        }
        else {
            a[k]=Right[j];
            ++j;
        }
    }
    delete [] Left;delete [] Right;
}
void merge_sort(Set* a,int p,int r)
{
    if(p<r) {
        int q=(p+r)/2;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
}

struct Link_Graph
{
    int size;
    Vertex* v;
    Link_Graph(int nums):size(nums),v(NULL)
    {
        v=new Vertex[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
            v[i].min=numeric_limits<int>::max();
            v[i].L=rand()%exponent(size,3)+1;
        }
    }
    void add_single_edge(int start,int end,int value=1) {
    Edge* p=new Edge(start,end,value);
    if(v[start].head==NULL||v[start].head->end>end) {
        p->next=v[start].head;
        v[start].head=p;
        return;
    }
    Edge* tmp=v[start].head,*pre=NULL;
    while(tmp!=NULL&&tmp->end<end) {
        pre=tmp;
        tmp=tmp->next;
    }
    if(tmp&&tmp->end==end) {
        delete p;
        return;
    }
    else {
        pre->next=p;
        p->next=tmp;
    }
    }
    void add_double_edge(int start,int end,int value=1)
    {
        add_single_edge(start,end,value);
        add_single_edge(end,start,value);
    }
    void delete_single_edge(int start,int end)
    {
        Edge* p=v[start].head,*pre=NULL;
        while(p&&p->end<end) {
            pre=p;
            p=p->next;
        }
        if(p->end>end) {
            return;
        }
        if(pre==NULL) {
            v[start].head=p->next;
        }
        else {
            pre->next=p->next;
        }
        delete p;
    }
    void delete_double_edge(int start,int end)
    {
        delete_single_edge(start,end);
        delete_single_edge(end,start);
    }
    ~Link_Graph()
    {
        for(int i=0;i!=size+1;++i) {
            if(v[i].head!=NULL) {
                delete_single_edge(v[i].head->start,v[i].head->end);
            }
        }
        delete [] v;
    }
    void print()
    {
        for(int i=1;i!=size+1;++i) {
            cout<<i;
            Edge* p=v[i].head;
            while(p!=NULL) {
                cout<<"->"<<p->end;
                p=p->next;
            }
            cout<<endl;
        }
    }
    Link_Graph* reverse()
    {
        Link_Graph* p=new Link_Graph(size);
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                p->add_single_edge(tmp->end,tmp->start);
                tmp=tmp->next;
            }
        }
        for(int i=1;i!=size+1;++i) {
            p->v[i].number=v[i].number;
            p->v[i].min=v[i].min;
            p->v[i].L=v[i].L;
        }
        return p;
    }
    void DFS()
    {
        for(int i=1;i!=size+1;++i) {
            v[i].cc=white;
            v[i].parent=NULL;
            v[i].tree=0;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=false;
                tmp=tmp->next;
            }
        }
        int time=0;int count=0;
        for(int i=1;i!=size+1;++i) {
            if(v[i].cc==white) {
                ++count;
                DFS_VISIT(i,time,count);
            }
        }
    }
    void DFS_VISIT(int s,int& time,int& count)
    {
        ++time;
        v[s].cc=gray;
        v[s].beg=time;
        v[s].tree=count;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].parent=&v[s];
                tmp->is_tree=true;
                DFS_VISIT(tmp->end,time,count);
            }
            else {
                tmp=tmp->next;
            }
        }
        ++time;
        v[s].cc=black;
        v[s].finish=time;
    }
    void reachable()
    {
        Link_Graph* p=this->reverse();
        Set* test=new Set[size+1];
        for(int i=1;i!=size+1;++i) {
            test[i].x=v[i].number;
            test[i].y=v[i].L;
        }
        test[0].x=0;test[0].y=0;
        merge_sort(test,1,size);
        //for(int i=1;i!=size+1;++i) {
       //     cout<<test[i].x<<" "<<test[i].y<<endl;
      //  }
        p->DFS2(test);
        for(int i=1;i!=size+1;++i) {
            v[i].min=p->v[i].min;
        }
        delete p;
    }
    void DFS2(Set* test)
    {
        for(int i=1;i!=size+1;++i) {
            v[i].cc=white;
            v[i].parent=NULL;
            v[i].tree=0;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=false;
                tmp=tmp->next;
            }
        }
        int time=0;int count=0;int mm=0;
        for(int i=1;i!=size+1;++i) {
            if(v[test[i].x].cc==white) {
                ++count;mm=test[i].y;
                DFS_VISIT2(test[i].x,time,count,mm);
            }
        }
    }
    void DFS_VISIT2(int s,int& time,int& count,int mm)
    {
        ++time;
        v[s].cc=gray;
        v[s].beg=time;
        v[s].tree=count;
        v[s].min=mm;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].parent=&v[s];
                tmp->is_tree=true;
                DFS_VISIT2(tmp->end,time,count,mm);
            }
            else {
                tmp=tmp->next;
            }
        }
        ++time;
        v[s].cc=black;
        v[s].finish=time;
    }
};

int main()
{
    //cout<<"Enter the number of the vertex:";
    int n=0;
    //cin>>n;
    ifstream is("topological_sort.txt");
    int a,b;
    while(is>>a>>b) {
        if(a==0&&b==0) {
            break;
        }
        if(a>n) {
            n=a;
        }
        if(b>n) {
            n=b;
        }
    }
    Link_Graph* p=new Link_Graph(n);
    is.close();
    is.open("topological_sort.txt");
    while(is>>a>>b&&a&&b) {
        p->add_single_edge(a,b);
    }
    p->print();
    p->DFS();
    for(int i=1;i!=n+1;++i) {
        cout<<i<<" begin:"<<p->v[i].beg<<" finish:"<<p->v[i].finish;
        if(p->v[i].parent!=NULL) {
            cout<<" parent:"<<p->v[i].parent->number;
        }
        else {
            cout<<" parent:"<<0;
        }
        cout<<" tree:"<<p->v[i].tree;
        cout<<" L:"<<p->v[i].L<<endl;
    }
    cout<<endl;
    //cout<<p->path_number(14,7)<<endl;
    //p->topological_sort();
    p->reachable();
    for(int i=1;i!=n+1;++i) {
        cout<<p->v[i].number<<" "<<p->v[i].min<<endl;
    }
    is.close();
    delete p;
    system("pause");
    return 0;
}
