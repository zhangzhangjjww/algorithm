#include<iostream>
#include<limits>
#include<stack>

const int MAX=100;

using namespace std;

struct Edge {
    int start;
    int end;
    int value;
    Edge* next;
    bool is_tree;
    Edge(int s,int e,int v):start(s),end(e),value(v),next(NULL),is_tree(0) {}
};

enum color {white,gray,black};

struct Vertex{
    Edge* head;
    color cc;
    int scc;
    int number;
    Vertex* parent;
    int beg;
    int finish;
    Vertex():head(NULL),cc(white),number(0),parent(NULL),beg(0),finish(0),scc(0) {}
};

struct Link_Graph {
    int size;
    Vertex* v;
    Link_Graph(int nums):size(nums),v(0) {
    v=new Vertex[size+1];
    for(int i=0;i!=size+1;++i) {
        v[i].number=i;
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
    void DFS()
    {
        for(int i=1;i!=size+1;++i) {
            v[i].cc=white;
            v[i].parent=NULL;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=0;
                tmp=tmp->next;
            }
        }
        int time=0;int porper=0;
        for(int i=1;i!=size+1;++i) {
            if(v[i].cc==white) {
                ++porper;
                DFS_VISIT(i,time,porper);
            }
        }
    }
    void DFS_VISIT(int s,int& time,int& porper)
    {
        time++;
        v[s].beg=time;
        v[s].cc=gray;
        v[s].scc=porper;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].parent=&v[s];
                tmp->is_tree=1;
                v[tmp->end].scc=porper;
                DFS_VISIT(tmp->end,time,porper);
            }
            tmp=tmp->next;
        }
        v[s].cc=black;
        ++time;
        v[s].finish=time;
    }
    void DFS_VISIT2(int s,int& time)
    {
        v[s].cc=gray;
        ++time;
        v[s].beg=time;
        stack<int> st;
        st.push(s);
        while(!st.empty()) {
            int u=st.top();
            cout<<u<<endl;
            bool isaleaf=true;
            Edge* tmp=v[u].head;
            while(tmp) {
                if(v[tmp->end].cc==white) {
                    v[tmp->end].cc=gray;
                    v[tmp->end].parent=&v[u];
                    tmp->is_tree=true;
                    ++time;
                    v[tmp->end].beg=time;
                    st.push(tmp->end);
                    isaleaf=false;
                    break;
                }
                else {
                    tmp=tmp->next;
                }
            }
                if(isaleaf==true) {
                    v[u].cc=black;
                    ++time;
                    v[u].finish=time;
                    st.pop();
                }
        }
    }
    void print_edge()
    {
        cout<<"Edge:"<<endl;
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(tmp->is_tree) {
                    cout<<tmp->start<<"->"<<tmp->end<<" Tree"<<endl;
                }
                else {
                    int m=tmp->start;
                    int n=tmp->end;
                    if(v[m].beg<v[n].beg&&v[n].finish<v[m].finish) {
                        cout<<tmp->start<<"->"<<tmp->end<<" Forward"<<endl;
                    }
                    else {
                        if(v[n].beg<=v[m].beg&&v[m].finish<=v[n].finish) {
                            cout<<tmp->start<<"->"<<tmp->end<<" Backward"<<endl;
                        }
                        else {
                            cout<<tmp->start<<"->"<<tmp->end<<" Cross"<<endl;
                        }
                    }
                }
                tmp=tmp->next;
            }
        }
    }
    bool test_singly_connected()
    {
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(!tmp->is_tree&&(v[i].beg<v[tmp->end].beg&&v[tmp->end].finish<v[i].finish)) {
                    return false;
                }
                else {
                    if(v[tmp->end].finish<v[i].beg) {
                        return false;
                    }
                    else {
                        tmp=tmp->next;
                    }
                }
            }
        }
        return true;
    }
};

int main()
{
    cout<<"enter the number of the vertex:";
    int n;
    cin>>n;
    Link_Graph* p=new Link_Graph(n);
    int a;int b;
    while(cin>>a>>b&&a&&b) {
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
        cout<<" scc:"<<p->v[i].scc<<endl;
    }
    p->print_edge();
    if(p->test_singly_connected()) {
        cout<<"The Graph is singly connected"<<endl;
    }
    else {
        cout<<"The Graph is not singly connected"<<endl;
    }
    delete p;
    return 0;
}
