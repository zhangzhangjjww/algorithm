#include<iostream>
#include<limits>
#include<stack>
#include<fstream>
#include<cstdlib>

const int MAX=100;

using namespace std;

struct Edge
{
    int start;
    int end;
    int value;
    Edge* next;
    bool is_tree;
    Edge(int s,int e,int v):start(s),end(e),value(v),next(NULL) {}
};

enum color {white,gray,black};
struct Vertex
{
    Edge* head;
    int low;
    int dfs;
    color cc;
    int beg;
    int finish;
    int scc;
    int tree;
    int number;
    Vertex* parent;
    bool is_in_stack;
    int sons;
    int* sons_number;
    Vertex():head(NULL),low(0),dfs(0),cc(white),beg(0),finish(0),scc(0),tree(0),number(0),parent(NULL),is_in_stack(0),sons(0),sons_number(NULL) {}
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
        for(int i=0;i!=size+1;++i) {
            v[i].sons_number=new int[size+1];
        }
        for(int i=0;i!=size+1;++i) {
            for(int j=0;j!=size+1;++j) {
                v[i].sons_number[j]=0;
            }
        }
    }
    ~Link_Graph()
    {
        for(int i=0;i!=size+1;++i) {
            delete [] v[i].sons_number;
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
        delete [] p;
    }
    void delete_double_edge(int start,int end)
    {
        delete_single_edge(start,end);
        delete_single_edge(end,start);
    }
    void DFS()
    {
        for(int i=1;i!=size+1;++i) {
            v[i].cc=white;
            v[i].parent=0;
            v[i].beg=0;
            v[i].finish=0;
            v[i].scc=0;
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
                tmp->is_tree=true;
                v[tmp->end].parent=&v[s];
                DFS_VISIT(tmp->end,time,count);
            }
            else {
                tmp=tmp->next;
            }
        }
        ++time;
        v[s].finish=time;
        v[s].cc=black;
    }
    void tarjan()
    {
        for(int i=0;i!=size+1;++i) {
            v[i].low=0;
            v[i].dfs=0;
            v[i].cc=white;
            v[i].parent=NULL;
            v[i].sons=0;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=false;
                tmp=tmp->next;
            }
        }
        int time=0;stack<int> sta;int count=1;
        for(int i=1;i!=size+1;++i) {
            if(v[i].cc==white) {
                tarjan_visit(i,time,count,sta);
            }
        }
    }
    void tarjan_visit(int s,int& time,int& count,stack<int>& sta)
    {
        ++time;
        v[s].cc=gray;
        v[s].low=time;
        v[s].dfs=time;
        sta.push(s);
        v[s].is_in_stack=true;
        Edge* tmp=v[s].head;
        while(tmp) {
            int son_count=1;
            if(v[tmp->end].cc==white) {
                v[tmp->end].parent=&v[s];
                tmp->is_tree=true;
                edge_reverse(tmp)->is_tree=true;
                ++v[s].sons;
                v[s].sons_number[son_count]=tmp->end;
                ++son_count;
                tarjan_visit(tmp->end,time,count,sta);
                if(v[tmp->end].low<v[s].low) {
                    v[s].low=v[tmp->end].low;
                }
            }
            else {
                if(v[tmp->end].is_in_stack&&tmp->is_tree==false) {
                    if(v[s].low>v[tmp->end].dfs) {
                        v[s].low=v[tmp->end].dfs;
                    }
                }
            }
            tmp=tmp->next;
        }
        if(v[s].low==v[s].dfs) {
            int u;
            do {
                u=sta.top();
                v[u].scc=count;
                sta.pop();
                v[u].is_in_stack=false;
            } while(u!=s);
            ++count;
        }
    }
    Edge* edge_reverse(Edge* p)
    {
        Edge* tmp=v[p->end].head;
        while(tmp) {
            if(tmp->end==p->start) {
                break;
            }
            tmp=tmp->next;
        }
        return tmp;
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
    void connected_point()
    {
        cout<<"connected point:";
        tarjan();
        for(int i=1;i!=size+1;++i) {
            if(v[i].parent==NULL) {
                if(v[i].sons>1) {
                    cout<<v[i].number<<" ";
                }
            }
            else {
                if(v[i].sons==1&&v[i].dfs<=v[v[i].sons_number[1]].low) {
                    cout<<v[i].number<<" ";
                }
            }
        }
        cout<<endl;
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
        p->add_double_edge(a,b);
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
        cout<<" tree"<<p->v[i].tree<<endl;
    }
    //cout<<p->path_number(14,7)<<endl;
    //p->topological_sort();
    p->tarjan();
    for(int i=1;i!=n+1;++i) {
        cout<<p->v[i].number<<" "<<p->v[i].dfs<<" "<<p->v[i].low<<" "<<p->v[i].scc<<endl;
    }
    p->connected_point();
    is.close();
    delete p;
    system("pause");
    return 0;
}
