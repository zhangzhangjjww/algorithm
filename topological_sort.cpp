#include<iostream>
#include<stack>
#include<limits>
#include<queue>
#include<fstream>
#include<cstdlib>
//#include"radix_sort_for_topological_sort.cpp"
const int MAX=100;

using namespace std;

struct Set  //计数和基数排序所用集合，对结点排序时，x表示scc,y表示节点序号；而在编排序上，x为起始的连通分量，y为终点所在联通分量
{
    int x;
    int y;
    Set& operator=(const Set& s)
    {
        x=s.x;
        y=s.y;
        return *this;
    }
};

void count_sort1(Set* a,Set* b,int k) //对节点排序
{
    int* c=new int[k+1];
    for(int i=0;i!=k+1;++i) {
        c[i]=0;
    }
    for(int j=1;j!=k+1;++j) {
        c[a[j].x]=c[a[j].x]+1;
    }
    for(int i=1;i!=k+1;++i) {
        c[i]=c[i]+c[i-1];
    }
    for(int i=k;i!=0;--i) {
        b[c[a[i].x]]=a[i];
        c[a[i].x]--;
    }
}
void count_sort2(Set* a,Set* b,int k)
{
    int* c=new int[k+1];
    for(int i=0;i!=k+1;++i) {
        c[i]=0;
    }
    for(int j=1;j!=k+1;++j) {
        c[a[j].y]=c[a[j].y]+1;
    }
    for(int i=1;i!=k+1;++i) {
        c[i]=c[i]+c[i-1];
    }
    for(int i=k;i!=0;--i) {
        b[c[a[i].y]]=a[i];
        c[a[i].y]--;
    }
}
void count_sort(Set* a,Set* b,int k,int i)
{
    if(i==1) {
        count_sort1(a,b,k);
    }
    else {
        count_sort2(a,b,k);
    }
}
void radix_sort(Set* a,Set* b,int k) //对连通分量边进行排序，基数排序
{
    count_sort(a,b,k,2);
    count_sort(b,a,k,1);
}




struct Edge
{
    int start;
    int end;
    int value;
    bool is_tree; //是否为树边
    Edge* next;
    Edge(int s,int e,int v):start(s),end(e),value(v),is_tree(0),next(NULL) {}
};

enum color {white,gray,black};
struct Vertex
{
    Edge* head;
    color cc;
    Vertex* parent;
    int number; //节点编号
    int beg;
    int finish;
    int tree; //DFS是否属于同一棵树
    int scc; //DFS是否属于同一强联通分量
    int position;//用于拓扑排序中，以此来判断是否有从一节点到另一节点路径，详见path_number()
    Vertex():head(NULL),parent(NULL),cc(white),number(0),beg(0),finish(0),scc(0),position(0),tree(0) {}
};

struct Link_Graph
{
    int size;
    Vertex* v;
    int* link_list; //拓扑排序顺序链表
    int edge_size; //边的总数
    Link_Graph(int nums):size(nums),v(0),link_list(0),edge_size(0)
    {
        v=new Vertex[size+1];
        link_list=new int[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
            link_list[i]=0;
        }
    }
    Link_Graph(const Link_Graph& lg):size(lg.size),v(0),link_list(0),edge_size(lg.edge_size)
    {
        v=new Vertex[size+1];
        link_list=new int[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
            link_list[i]=0;
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=lg.v[i].head;
            while(tmp) {
                add_single_edge(i,tmp->end);
                tmp=tmp->next;
            }
        }
    }
    void add_single_edge(int start,int end,int value=1)
    {
        Edge* p=new Edge(start,end,value);
        if(v[start].head==NULL||v[start].head->end>end) {
            p->next=v[start].head;
            v[start].head=p;
            ++edge_size;
            return;
        }
        Edge* re=v[start].head,*pre=NULL;
        while(re&&re->end<end) {
            pre=re;
            re=re->next;
        }
        if(re&&re->end==end) {
            delete p;
            return;
        }
        pre->next=p;
        p->next=re;
        ++edge_size;
    }
    void add_double_edge(int start,int end,int value=1)
    {
        add_single_edge(start,end,value);
        add_single_edge(end,start,value);
    }
    void delete_single_edge(int start,int end)
    {
        Edge* re=v[start].head,*pre=NULL;
        if(re&&re->end<end) {
            pre=re;
            re=re->next;
        }
        if(re->end>end) {
            return;
        }
        else {
            if(pre==NULL) {
                v[start].head=v[start].head->next;
            }
            else {
                pre->next=re->next;
            }
            delete re;
            --edge_size;
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
        delete [] link_list;
    }
    void print() //打印所有的邻接链表
    {
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            cout<<i;
            while(tmp) {
                cout<<"->"<<tmp->end;
                tmp=tmp->next;
            }
            cout<<endl;
        }
    }
    void DFS() //深搜
    {
        for(int i=1;i!=size+1;++i) {
            v[i].parent=NULL;
            v[i].beg=0;
            v[i].finish=0;
            v[i].cc=white;
            v[i].scc=0;
            v[i].position=0;
            v[i].tree=0;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=false;
                tmp=tmp->next;
            }
        }
        int time=0;int count=0;int sz=size;
        for(int i=1;i!=size+1;++i) {
            if(v[i].cc==white) {
                ++count;
                DFS_VISIT(i,time,count,sz);
            }
        }
    }
    void DFS_VISIT(int s,int& time,int& count,int& sz)
    {
        v[s].cc=gray;
        ++time;
        v[s].beg=time;
        v[s].tree=count;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].tree=count;
                v[tmp->end].cc=gray;
                v[tmp->end].parent=&v[s];
                tmp->is_tree=true;
                DFS_VISIT(tmp->end,time,count,sz);
            }
            else {
                tmp=tmp->next;
            }
        }
        ++time;
        v[s].finish=time;
        v[s].cc=black;
        link_list[sz]=s;
        v[s].position=sz;
        --sz;
    }
    void print_edge() //打印所有边，并判断边的类型
    {
        cout<<"Edges:"<<endl;
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(tmp->is_tree) {
                    cout<<i<<"->"<<tmp->end<<" Tree"<<endl;
                }
                else {
                    if(v[i].beg<v[tmp->end].beg&&v[i].finish>v[tmp->end].finish) {
                        cout<<i<<"->"<<tmp->end<<" Forward"<<endl;
                    }
                    else {
                        if(v[i].beg>=v[tmp->end].beg&&v[i].finish<=v[tmp->end].finish) {
                            cout<<i<<"->"<<tmp->end<<" Backward"<<endl;
                        }
                        else {
                            cout<<i<<"->"<<tmp->end<<" Cross"<<endl;
                        }
                    }
                }
                tmp=tmp->next;
            }
        }
    }
    int path_number(int s,int e) //给出从节点s到节点e的路径数，线性算法
    {
        DFS();
        int n1,n2;
        n1=v[s].position;
        n2=v[e].position;
        int sz=n2-n1;
        int* p=new int[sz];
        for(int i=0;i!=sz;++i) {
            p[i]=0;
        }
        for(int i=0;i!=sz;++i) {
            Edge* tmp=v[link_list[n2-i-1]].head;
            while(tmp) {
                if(tmp->end==e) {
                    ++p[i];
                }
                else {
                    int pos=v[tmp->end].position;
                    if(pos<v[e].position&&pos>v[link_list[n2-i-1]].position) {
                        p[i]=p[i]+p[n2-pos-1];
                    }
                }
                tmp=tmp->next;
            }
        }
        int re=p[sz-1];
        delete [] p;
        return re;
    }
    void topological_sort() //基于队列实现拓扑排序
    {
        Link_Graph *lg=new Link_Graph(*this);
        //lg->print();
        int* in_degree=new int[size+1];
        for(int i=0;i!=size+1;++i) {
            in_degree[i]=0;
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=lg->v[i].head;
            while(tmp) {
                ++in_degree[tmp->end];
                tmp=tmp->next;
            }
        }
        queue<int> qu;
        cout<<endl;
        for(int i=1;i!=size+1;++i) {
            if(in_degree[i]==0) {
                qu.push(i);
            }
        }
        while(!qu.empty()) {
            int u=qu.front();
            cout<<u<<" ";
            qu.pop();
            Edge* tmp=v[u].head;
            while(tmp) {
                --in_degree[tmp->end];
                if(in_degree[tmp->end]==0) {
                    qu.push(tmp->end);
                }
                tmp=tmp->next;
            }
        }
        cout<<endl;
        int i;
        for(i=1;i!=size+1;++i) {
            if(in_degree[i]!=0) {
                break;
            }
        }
        if(i==size+1) {
            cout<<"No circle"<<endl;
        }
        else {
            cout<<"Have circle"<<endl;
        }
        delete lg;delete [] in_degree;
    }
    Link_Graph* reverse()
    {
        Link_Graph* p=new Link_Graph(size);
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                p->add_single_edge(tmp->end,i);
                tmp=tmp->next;
            }
        }
        return p;
    }
    void strong_connected_components() //强连通分量
    {
        DFS();
        Link_Graph* p=this->reverse();
        p->DFS2(link_list);
        cout<<endl;
        for(int i=1;i!=size+1;++i) {
            v[i].scc=p->v[i].scc;
        }
        delete p;
    }
    void strong_connected_components2() //强连通分量，输出所有的点的连通分量以及连通分量图
    {
        DFS();
        Link_Graph* p=this->reverse();
        //p->print();
        p->DFS2(link_list);
        cout<<endl;
        Set* ss=new Set[size+1];
        Set* ss2=new Set[size+1];
        for(int i=1;i!=size+1;++i) {
            ss[i].x=p->v[i].scc;
            ss[i].y=p->v[i].number;
            ss2[i].x=0;ss2[i].y=0;
        }
        count_sort1(ss,ss2,size);
        for(int i=1;i!=size+1;++i) {
            cout<<ss2[i].x<<" "<<ss2[i].y<<endl;
        }
        cout<<endl;
        Set* edge_ss=new Set[size+1];
        Set *edge_ss2=new Set[size+1];
        int edge_number=1;
        for(int i=1;i!=size+1;++i) {
            v[i].scc=p->v[i].scc;
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(v[i].scc!=v[tmp->end].scc) {
                    edge_ss[edge_number].x=v[i].scc;
                    edge_ss[edge_number].y=v[tmp->end].scc;
                    ++edge_number;
                }
                tmp=tmp->next;
            }
        }
        radix_sort(edge_ss,edge_ss2,size);
        for(int i=1;i!=size+1;++i) {
            if(edge_ss[i].x==0||(edge_ss[i].x==edge_ss[i-1].x&&edge_ss[i].y==edge_ss[i-1].y)) {
                continue;
            }
            cout<<edge_ss[i].x<<" "<<edge_ss[i].y<<endl;
        }
        delete [] edge_ss2;delete [] edge_ss;
        delete [] ss;delete [] ss2;
        delete p;
    }
    void DFS2(int* ll)
    {
        for(int i=1;i!=size+1;++i) {
            v[i].parent=NULL;
            v[i].beg=0;
            v[i].finish=0;
            v[i].cc=white;
            v[i].scc=0;
            v[i].tree=0;
            v[i].position=0;
            Edge* tmp=v[i].head;
            while(tmp) {
                tmp->is_tree=false;
                tmp=tmp->next;
            }
        }
        int time=0;int count=0;int sz=size;
        for(int i=1;i!=size+1;++i) {
            if(v[ll[i]].cc==white) {
                ++count;
                cout<<ll[i]<<" ";
                DFS_VISIT2(ll[i],time,count,sz);
            }
        }
    }
    void DFS_VISIT2(int s,int& time,int& count,int& sz)
    {
        v[s].cc=gray;
        ++time;
        v[s].beg=time;
        v[s].scc=count;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].scc=count;
                v[tmp->end].cc=gray;
                v[tmp->end].parent=&v[s];
                tmp->is_tree=true;
                DFS_VISIT2(tmp->end,time,count,sz);
            }
            else {
                tmp=tmp->next;
            }
        }
        ++time;
        v[s].finish=time;
        v[s].cc=black;
        link_list[sz]=s;
        v[s].position=sz;
        --sz;
    }
    void add_circle(Set* ss,int v_s,int v_e)
    {
        if(v_s==v_e) {
            return;
        }
        for(int i=v_s;i!=v_e;++i) {
            add_single_edge(ss[i].y,ss[i+1].y);
        }
        add_single_edge(ss[v_e].y,ss[v_s].y);
    }
    Link_Graph* equal_graph() //实现等效图，相同强连通分量，相同分量图，边的数目减少
    {
        Link_Graph* re=new Link_Graph(size);
        DFS();
        Link_Graph* p=this->reverse();
        p->DFS2(link_list);
        cout<<endl;
        Set* ss=new Set[size+1];
        Set* ss2=new Set[size+1];
        for(int i=1;i!=size+1;++i) {
            ss[i].x=p->v[i].scc;
            ss[i].y=p->v[i].number;
            ss2[i].x=0;ss2[i].y=0;
        }
        count_sort1(ss,ss2,size);
        int tmp_ver=1;int v_s=1;int v_e=1;
        int iii=1;
        while(iii<size+1) {
            if(ss2[iii].x==tmp_ver) {
                v_e=iii;
                if(iii==size) {
                    re->add_circle(ss2,v_s,v_e);
                }
                ++iii;
            }
            else {
                ++tmp_ver;
                re->add_circle(ss2,v_s,v_e);
                v_s=iii;
                v_e=iii;
            }
        }
        Set* edge_ss=new Set[size+1];
        Set *edge_ss2=new Set[size+1];
        int edge_number=1;
        for(int i=1;i!=size+1;++i) {
            v[i].scc=p->v[i].scc;
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(v[i].scc!=v[tmp->end].scc) {
                    edge_ss[edge_number].x=v[i].scc;
                    edge_ss[edge_number].y=v[tmp->end].scc;
                    ++edge_number;
                }
                tmp=tmp->next;
            }
        }
        radix_sort(edge_ss,edge_ss2,size);
        int n1,n2;
        for(int i=1;i!=size+1;++i) {
            if(edge_ss[i].x==0||(edge_ss[i].x==edge_ss[i-1].x&&edge_ss[i].y==edge_ss[i-1].y)) {
                continue;
            }
            for(int j=1;j!=size+1;++j) {
                if(ss2[j].x==edge_ss[i].x) {
                    n1=ss2[j].y;
                    break;
                }
            }
            for(int j=1;j!=size+1;++j) {
                if(ss2[j].x==edge_ss[i].y) {
                    n2=ss2[j].y;
                    break;
                }
            }
            re->add_single_edge(n1,n2);
        }
        delete [] edge_ss2;delete [] edge_ss;
        delete [] ss;delete [] ss2;
        delete p;
        return re;
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
    cout<<p->edge_size<<endl;
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
        cout<<" scc"<<p->v[i].scc<<endl;
    }
    p->print_edge();
    for(int i=1;i!=n+1;++i) {
        cout<<p->link_list[i]<<" ";
        if(i%5==0) {
            cout<<endl;
        }
    }
    cout<<endl;
    //cout<<p->path_number(14,7)<<endl;
    //p->topological_sort();
    p->strong_connected_components2();
    Link_Graph* eq=p->equal_graph();
    eq->print();
    is.close();
    delete p;delete eq;
    system("pause");
    return 0;
}
