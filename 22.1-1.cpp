#include<iostream>

const int max=100;

using namespace std;

struct Vertex;
struct Mat_Graph;

struct Edge
{
    int start;
    int end;
    int value;
    Edge* next;
    Edge(int s,int e,int v=1):start(s),end(e),value(v),next(NULL) {}
};

struct Vertex
{
    Edge* head;
    Vertex():head(NULL) {}
};

struct Link_Graph
{
    int size;
    Vertex* v;
    Link_Graph(int num):size(num),v(0)
    {
        v=new Vertex[size+1];
    }
    void add_single_edge(int start,int end,int value=1)
    {
        Edge* tmp=new Edge(start,end);
        Edge* p=v[start].head,*pre;
        if(p==NULL||p->end>end) {
            tmp->next=p;
            v[start].head=tmp;
        }
        else {
            while(p!=NULL&&p->end<end) {
                pre=p;
                p=p->next;
            }
            if(p&&p->end==end) {
                delete tmp;
                return ;
            }
            else {
                pre->next=tmp;
                tmp->next=p;
            }
        }
    }
    void add_double_edge(int start,int end,int value=1)
    {
        add_single_edge(start,end,value);
        add_single_edge(end,start,value);
    }
    void delete_single_edge(int start,int end)
    {
        Edge* tmp=v[start].head,*pre;
        while(tmp!=NULL&&tmp->end<end) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp->end>end) {
            return ;
        }
        else {
            if(tmp==v[start].head) {
                v[start].head=tmp->next;
            }
            else {
                pre->next=tmp->next;
            }
            delete tmp;
        }
    }
    void delete_double_edge(int start,int end)
    {
        delete_single_edge(start,end);
        delete_single_edge(end,start);
    }
    ~Link_Graph()
    {
        for(int i=1;i!=size+1;++i) {
            while(v[i].head!=NULL) {
                delete_single_edge(v[i].head->start,v[i].head->end);
            }
        }
        delete [] v;
    }
    void out_range()
    {
        for(int i=1;i!=size+1;++i) {
            int count=0;
            Edge* tmp=v[i].head;
            while(tmp!=NULL) {
                ++count;
                tmp=tmp->next;
            }
            cout<<"out_range of "<<i<<" is "<<count<<endl;
        }
    }
    void in_range()
    {
        int* p=new int[size+1];
        for(int i=0;i!=size+1;++i) {
            p[i]=0;
        }
        for(int i=0;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp!=NULL) {
                ++p[tmp->end];
                tmp=tmp->next;
            }
        }
        for(int i=1;i!=size+1;++i) {
            cout<<"in_range of "<<i<<"is "<<p[i]<<endl;
        }
        delete [] p;
    }
    void print()
    {
        for(int i=1;i!=size+1;++i){
            Edge* tmp=v[i].head;
            cout<<i;
            while(tmp!=NULL) {
                cout<<"->"<<tmp->end;
                tmp=tmp->next;
            }
            cout<<endl;
        }
    }
    Link_Graph* reverse()
    {
        Link_Graph* p=new Link_Graph(size);
        for(int i=1;i!=size+1 ;++i) {
            Edge* tmp=v[i].head;
            while(tmp!=NULL) {
                p->add_single_edge(tmp->end,tmp->start);
                tmp=tmp->next;
            }
        }
        return p;
    }
    Link_Graph* square()
    {
        Link_Graph* p=new Link_Graph(size);
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp!=NULL) {
                p->add_single_edge(tmp->start,tmp->end);
                Edge* tmp2=v[tmp->end].head;
                while(tmp2!=NULL) {
                    p->add_single_edge(tmp->start,tmp2->end);
                    tmp2=tmp2->next;
                }
                tmp=tmp->next;
            }
        }
        return p;
    }
};

struct Mat_Graph
{
    int size;
    int** matrix;
    Mat_Graph(int num):size(num),matrix(0)
    {
        matrix=new int*[size+1];
        for(int i=0;i!=size+1;++i) {
            matrix[i]=new int[size+1];
        }
        for(int i=0;i!=size+1;++i) {
            for(int j=0;j!=size+1;++j) {
                matrix[i][j]=0;
            }
        }
    }
    ~Mat_Graph()
    {
        for(int i=0;i!=size+1;++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    void add_single_edge(int start,int end,int value=1)
    {
        matrix[start][end]=value;
    }
    void add_double_edge(int start,int end,int value=1)
    {
        add_single_edge(start,end,value);
        add_single_edge(end,start,value);
    }
    void delete_single_edge(int start,int end)
    {
        matrix[start][end]=0;
    }
    void delete_double_edge(int start,int end)
    {
        delete_single_edge(start,end);
        delete_single_edge(end,start);
    }
    void out_range()
    {
        for(int i=1;i!=size+1;++i) {
            int count=0;
            for(int j=1;j!=size+1;++j) {
                if(matrix[i][j]!=0) {
                    ++count;
                }
            }
            cout<<"out_range of "<<i<<" is "<<count<<endl;
        }
    }
    void in_range()
    {
        for(int i=1;i!=size+1;++i) {
            int count=0;
            for(int j=1;j!=size+1;++j) {
                if(matrix[j][i]!=0) {
                    ++count;
                }
            }
            cout<<"in_range of "<<i<<" is "<<count<<endl;
        }
    }
    Mat_Graph* reverse()
    {
        Mat_Graph* p=new Mat_Graph(size);
        for(int i=1;i!=size+1;++i) {
            for(int j=1;j!=size+1;++j) {
                if(matrix[i][j]!=0) {
                    p->matrix[j][i]=matrix[i][j];
                }
            }
        }
        return p;
    }
    Mat_Graph* square()
    {
        Mat_Graph* p=new Mat_Graph(size);
        for(int i=1;i!=size+1;++i) {
            for(int j=1;j!=size+1;++j) {
                if(matrix[i][j]!=0) {
                    p->matrix[i][j]=matrix[i][j];
                }
                for(int k=1;k!=size+1;++k) {
                    if(matrix[j][k]!=0) {
                        p->matrix[i][k]=matrix[j][k];//若有权重时，结果可能不对，需要修正
                    }
                }
            }
        }
        return p;
    }
    void print()
    {
        for(int i=1;i!=size+1;++i) {
            for(int j=1;j!=size+1;++j) {
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    bool is_sink(int k)
    {
        for(int i=1;i!=size+1;++i) {
            if(matrix[k][i]!=0) {
                return false;
            }
            if(matrix[i][k]==0&&i!=k) {
                return false;
            }
        }
        return true;
    }
    void universe_sink()
    {
        int i=1,j=1;
        while(i<size+1&&j<size+1) {
            if(matrix[i][j]!=0) {
                ++i;
            }
            else {
                ++j;
            }
        }
        if(i>=size+1) {
            cout<<"Don't exist"<<endl;
        }
        else {
            if(is_sink(i)) {
                cout<<i<<" is a sink"<<endl;
            }
            else {
                cout<<"Don't exist"<<endl;
            }
        }
    }
    friend Mat_Graph* transform(Link_Graph* l);
    /*{
        Mat_Graph* p=new Mat_Graph(l->size);
        for(int i=1;i!=p->size+1;++i) {
            Edge* tmp=l->v[i].head;
            while(tmp!=NULL) {
                p->matrix[tmp->start][tmp->end]=tmp->value;
                tmp=tmp->next;
            }
        }
        return p;
    }*/
};

Mat_Graph* transform(Link_Graph* l)
    {
        Mat_Graph* p=new Mat_Graph(l->size);
        for(int i=1;i!=p->size+1;++i) {
            Edge* tmp=l->v[i].head;
            while(tmp!=NULL) {
                p->matrix[tmp->start][tmp->end]=tmp->value;
                tmp=tmp->next;
            }
        }
        return p;
    }

int main()
{
    int n;
    cout<<"enter the number of vertex:";
    cin>>n;
    Link_Graph* p=new Link_Graph(n);
    int a,b;
    while(cin>>a>>b&&a&&b) {
        p->add_single_edge(a,b);
    }
    p->out_range();
    p->in_range();
    p->print();
    //Link_Graph* p2=p->reverse();
  //  p2->print();
   // Link_Graph* p3=p->square();
   // p3->print();
    Mat_Graph* m=transform(p);
    m->print();
    m->universe_sink();
    delete p;
    return 0;
}
