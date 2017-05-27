#include<iostream>
#include<cstdlib>
#include<limits>
#include<fstream>
#include<list>

const int MAX=100;

using namespace std;

template<class T> struct Node
{
    T key;
    Node* pre_t;
    Node* next_t;
    Node(T k=0):key(k),pre_t(NULL),next_t(NULL) {}
};
template<class T> struct double_list
{
    Node<T>* list_head;
    double_list():list_head(NULL) {}
    double_list(const double_list& dl):list_head(NULL)
    {
        Node<T>* tmp=dl.list_head;
        while(tmp) {
            Node<T> * pp=list_head;
            if(pp==NULL) {
                list_insert(tmp->key,pp);
                tmp=tmp->next_t;
                continue;
            }
            while(pp->next_t!=NULL) {
                pp=pp->next_t;
            }
            list_insert(tmp->key,pp);
            tmp=tmp->next_t;
        }
    }
    double_list& operator=(const double_list& dl)
    {
        while(list_head!=NULL) {
            list_delete(list_head);
        }
        Node<T>* tmp=dl.list_head;
        while(tmp) {
            Node<T> * pp=list_head;
            if(pp==NULL) {
                list_insert(tmp->key,pp);
                tmp=tmp->next_t;
                continue;
            }
            while(pp->next_t!=NULL) {
                pp=pp->next_t;
            }
            list_insert(tmp->key,pp);
            tmp=tmp->next_t;
        }
        return *this;
    }
    ~double_list()
    {
        while(list_head!=NULL) {
            list_delete(list_head);
        }
    }
    void list_insert(T x,Node<T>* tmp)
    {
        Node<T>* p=new Node<T>(x);
        if(list_head==NULL) {
            list_head=p;
            return;
        }
        Node<T>* next=tmp->next_t;
        if(next!=NULL) {
            next->pre_t=p;
        }
        p->next_t=next;
        tmp->next_t=p;
        p->pre_t=tmp;
    }
    Node<T>* list_search(T x)
    {
        Node<T>* tmp=list_head;
        while(tmp!=NULL&&tmp->key!=x) {
            tmp=tmp->next_t;
        }
        return tmp;
    }
    void list_delete(Node<T>* tmp)
    {
        if(tmp->pre_t!=NULL) {
            tmp->pre_t->next_t=tmp->next_t;
        }
        else {
            list_head=tmp->next_t;
        }
        if(tmp->next_t!=NULL) {
            tmp->next_t->pre_t=tmp->pre_t;
        }
        delete tmp;
    }
    void list_delete(T x)
    {
        Node<T>* tmp=list_search(x);
        if(tmp!=NULL) {
            list_delete(tmp);
        }
    }
    void list_merge(double_list<T>& dl,Node<T>* tmp)
    {
        if(dl.list_head==NULL) {
            return;
        }
        else {
            if(tmp==list_head&&tmp==NULL) {
                *this=dl;
                return;
            }
            else {
                Node<T>* p=dl.list_head;
                while(p!=NULL) {
                    list_insert(p->key,tmp);
                    tmp=tmp->next_t;
                    p=p->next_t;
                }
            }
        }
    }
    void list_unique()
    {
        Node<T>* p=list_head,*pre=NULL;
        while(p->next_t!=NULL) {
            if(p->key==p->next_t->key) {
                pre=p->pre_t;
                list_delete(p);
                p=pre->next_t;
            }
            else {
                p=p->next_t;
            }
        }
    }
    void print()
    {
        Node<T>* p=list_head;
        //int c=1;
        while(p!=NULL) {
           cout<<p->key<<" ";
           p=p->next_t;
          // if(c%5==0) {
          //  cout<<endl;
         //  }
         //  ++c;
        }
        cout<<endl;
    }
    bool empty()
    {
        if(list_head==NULL) {
            return true;
        }
        else {
            return false;
        }
    }
};

struct Edge
{
    int start;
    int end;
    int value;
    Edge* next;
    Edge(int s,int e,int v):start(s),end(e),value(v),next(NULL) {}
};

struct Vertex
{
    Edge* head;
    int out_range;
    int number;
    Vertex():head(NULL),out_range(0),number(0) {}
};

struct Link_Graph
{
    int size;
    Vertex* v;
    Link_Graph(int nums):size(nums),v(NULL)
    {
        v=new Vertex[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
        }
    }
    Link_Graph(const Link_Graph& lg):size(lg.size),v(NULL)
    {
        v=new Vertex[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=lg.v[i].head;
            while(tmp) {
                add_single_edge(tmp->start,tmp->end);
                tmp=tmp->next;
            }
        }
    }
    ~Link_Graph()
    {
        for(int i=0;i!=size+1;++i) {
            while(v[i].head!=NULL) {
                delete_single_edge(i,v[i].head->end);
            }
        }
        delete [] v;
    }
    void add_single_edge(int start,int end,int value=1)
    {
        Edge* p=new Edge(start,end,value);
        if(v[start].head==NULL||v[start].head->end>end) {
            p->next=v[start].head;
            v[start].head=p;
            ++v[start].out_range;
            return;
        }
        Edge* tmp=v[start].head,*pre=NULL;
        while(tmp&&tmp->end<end) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp&&tmp->end==end) {
            delete p;
            return;
        }
        pre->next=p;
        p->next=tmp;
        ++v[start].out_range;
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
        if(p&&p->end>end) {
            return;
        }
        if(pre==NULL) {
            v[start].head=p->next;
        }
        else {
            pre->next=p->next;
        }
        --v[start].out_range;
        delete [] p;
    }
    void delete_double_edge(int start,int end)
    {
        delete_single_edge(start,end);
        delete_single_edge(end,start);
    }
    void print()
    {
        for(int i=1;i!=size+1;++i) {
            cout<<i;
            Edge* tmp=v[i].head;
            while(tmp) {
                cout<<"->"<<tmp->end;
                tmp=tmp->next;
            }
            cout<<endl;
        }
    }
    double_list<int> Euler_tour()
    {
        double_list<int> TT,L;
        Link_Graph* test=new Link_Graph(*this);
        L.list_insert(1,L.list_head);
        while(L.list_head!=NULL) {
            int pos=L.list_head->key;
            Node<int>* tmp=TT.list_search(pos);
            L.list_delete(pos);
            double_list<int> C=test->visit(pos,L);
            if(tmp==NULL) {
                TT=C;
            }
            else {
                TT.list_merge(C,tmp);
            }
            TT.list_unique();
            //TT.print();
            if(L.list_head==NULL) {
                cout<<"done!"<<endl;
            }
            Node<int>* test_out=L.list_head;
            while(test_out&&test->v[test_out->key].out_range==0) {
                L.list_delete(test_out);
                test_out=L.list_head;
            }
        }
        delete test;
        return TT;
    }
    double_list<int> visit(int pos,double_list<int>& L)
    {
        double_list<int> C;
        int u=pos;
        while(v[u].out_range>0) {
            int w=v[u].head->end;
            delete_single_edge(u,w);
            Node<int> * pp=C.list_head;
            if(pp==NULL) {
                C.list_insert(u,pp);
            }
            else {
            while(pp->next_t!=NULL) {
                pp=pp->next_t;
            }
            C.list_insert(u,pp);
            }
            if(v[u].out_range>0) {
                L.list_insert(u,L.list_head);
            }
            u=w;
        }
         Node<int> * pp2=C.list_head;
            if(pp2==NULL) {
                C.list_insert(u,pp2);
            }
            else {
            while(pp2->next_t!=NULL) {
                pp2=pp2->next_t;
            }
            C.list_insert(pos,pp2);
            }
        //C.print();
        //L.print();
        return C;
    }
};

/*int main()
{
    double_list<int> dd,dd2;
    for(int i=0;i!=5;++i) {
        dd.list_insert(i,dd.list_head);
    }
    dd2=dd;
    dd.list_merge(dd2,dd.list_head);
    dd.print();
    return 0;
}*/

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
    double_list<int> re=p->Euler_tour();
    re.print();
    //cout<<p->path_number(14,7)<<endl;
    //p->topological_sort();
    is.close();
    delete p;
    //system("pause");
    return 0;
}
