#ifndef BELL_H_INCLUDED
#define BELL_H_INCLUDED

#include<iostream>
#include<string>
#include<limits>
#include<vector>


using namespace std;

struct Edge
{
   int start;
   int end;
   int value;
   Edge* next;
   Edge(int s,int e ,int v):start(s),end(e),value(v),next(NULL) {}
};

enum color {white,gray,black};

struct Vertex
{
    Edge* head;
    int distance;
    Vertex* parent;
    int number;
    color cc;
    int beg;
    int finish;
    int circle;
    Vertex():head(NULL),distance(0),parent(NULL),number(0),cc(white),beg(0),finish(0),circle(0) {}
};

class Link_Graph
{
public:
    int sz;
    Vertex* v;
    vector<int> topological;
    Link_Graph(int n):sz(n),v(NULL)
    {
        v=new Vertex[sz+1];
        for(int i=0;i!=sz+1;++i) {
            v[i].number=i;
        }
    }
    ~Link_Graph()
    {
        for(int i=0;i!=sz+1;++i) {
            while(v[i].head!=NULL) {
                delete_single_edge(v[i].head->start,v[i].head->end);
            }
        }
        delete [] v;
    }
    void add_single_edge(int s,int e,int val=1)
    {
        Edge* p=new Edge(s,e,val);
        if(v[s].head==NULL||v[s].head->end>e) {
            p->next=v[s].head;
            v[s].head=p;
            return;
        }
        Edge* tmp=v[s].head,* pre=NULL;
        while(tmp&&tmp->end<e) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp&&tmp->end==e) {
            delete [] p;
        }
        else {
            pre->next=p;
            p->next=tmp;
        }
    }
    void add_double_edge(int s,int e,int val=1)
    {
        add_single_edge(s,e,val);
        add_single_edge(e,s,val);
    }
    void delete_single_edge(int s,int e)
    {
        Edge* tmp=v[s].head,*pre=NULL;
        while(tmp&&tmp->end<e) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp->end>e) {
            return;
        }
        else {
            if(pre==NULL) {
                v[s].head=v[s].head->next;
                delete [] tmp;
            }
            else {
                pre->next=tmp->next;
                delete [] tmp;
            }
        }
    }
    void delete_double_edge(int s,int e)
    {
        delete_single_edge(s,e);
        delete_single_edge(e,s);
    }
    void print()
    {
        for(int i=1;i!=sz+1;++i) {
            cout<<i;
            Edge* tmp=v[i].head;
            while(tmp) {
                cout<<"->"<<tmp->end<<"("<<tmp->value<<")";
                tmp=tmp->next;
            }
            cout<<endl;
        }
    }
    bool Bellman_Ford(int s)  //变体，将负环标记出
    {
        if(s<=0||s>sz) {
            cout<<"wrong!\n";
            return false;
        }
        initialize_single_source(s);
        for(int i=1;i!=sz;++i) {
            for(int j=1;j!=sz+1;++j) {
                Edge* tmp=v[j].head;
                while(tmp) {
                    relax(tmp);
                    tmp=tmp->next;
                }
            }
        }
        bool re=true;
        int pos=0;
        for(int i=1;i!=sz+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(v[tmp->end].distance>tmp->value+v[tmp->start].distance) {
                    re=false;
                    if(pos==0) {
                        pos=tmp->end;
                        //pos=1;
                    }
                    //v[tmp->end].distance=numeric_limits<int>::min();
                }
                tmp=tmp->next;
            }
        }
        //for(int i=1;i!=sz+1;++i) {     //注释处用于追踪所有经过负环路的节点
         //   if(v[i].distance==numeric_limits<int>::min()) {
         //       set_negative_pre(v[i].parent->number);
          //  }
        //}
        set_negative_cycle(pos);
        return re;
    }
    bool Bellman_Ford_mod(int s)  //变体，减小循环次数
    {
        if(s<0||s>sz) {
            cout<<"wrong";
            return false;
        }
        initialize_single_source(s);
        bool change=true;
        while(change) {
            change=false;
            int c=0;
            for(int i=1;i!=sz+1;++i) {
                Edge* tmp=v[i].head;
                while(tmp) {
                    bool tt=relax_mod(tmp);
                    if(c==0&&tt) {
                        ++c;
                        change=true;
                    }
                    tmp=tmp->next;
                }
            }
        }
        for(int i=1;i!=sz+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(v[tmp->end].distance>v[tmp->start].distance+tmp->value) {
                    return false;
                }
                tmp=tmp->next;
            }
        }
        return true;
    }
    bool Bellman_Ford_mod2() //变体。判断所有点的最短距离
    {
        for(int i=1;i!=sz+1;++i) {
            v[i].parent=NULL;
            v[i].distance=numeric_limits<int>::max();
        }
        for(int i=1;i!=sz;++i) {
            for(int j=1;j!=sz+1;++j) {
                Edge* tmp=v[j].head;
                while(tmp) {
                    relax_mod2(tmp);
                    tmp=tmp->next;
                }
            }
        }
        for(int i=1;i!=sz+1;++i) {
            Edge* tmp=v[i].head;
            while(tmp) {
                if(v[tmp->end].distance>v[tmp->start].distance+tmp->value) {
                    return false;
                }
                tmp=tmp->next;
            }
        }
        return true;
    }
    void print_path()
    {
        for(int i=1;i!=sz+1;++i) {
            cout<<i<<" distance:"<<v[i].distance<<" parent:";
            if(v[i].parent!=NULL) {
                cout<<v[i].parent->number<<endl;
            }
            else {
                cout<<"NULL"<<endl;
            }
        }
    }
    void DFS()
    {
        for(int i=1;i!=sz+1;++i) {
            v[i].beg=0;
            v[i].finish=0;
            v[i].parent=NULL;
            v[i].cc=white;
        }
        int time=0;
        for(int i=1;i!=sz+1;++i) {
            if(v[i].cc==white) {
                DFS_VISIT(i,time);
            }
        }
    }
    void DFS_VISIT(int s,int& time)
    {
        ++time;
        v[s].cc=gray;
        Edge* tmp=v[s].head;
        while(tmp) {
            if(v[tmp->end].cc==white) {
                v[tmp->end].parent=&v[s];
                DFS_VISIT(tmp->end,time);
            }
            tmp=tmp->next;
        }
        ++time;
        v[s].cc=black;
        v[s].finish=time;
        topological.push_back(s);
    }
    void Dag_shortest_path(int s)  //用于有向无环图
    {
        DFS();
        initialize_single_source(s);
        for(int i=topological.size()-1;i>-1;--i) {
            //cout<<topological[i]<<endl;
            Edge* tmp=v[topological[i]].head;
            while(tmp) {
                relax(tmp);
                tmp=tmp->next;
            }
            //print_path();
            //cout<<endl;
        }
    }
private:
    void initialize_single_source(int s)
    {
        for(int i=1;i!=sz+1;++i) {
            if(i==s) {
                v[s].distance=0;
            }
            else {
                v[i].distance=numeric_limits<int>::max();
            }
            v[i].parent=NULL;
            v[i].circle=0;
        }
    }
    void relax(Edge* p)
    {
        if(v[p->start].distance==numeric_limits<int>::max()) {
            return;
        }
        else {
            if(v[p->end].distance>v[p->start].distance+p->value) {
                v[p->end].distance=v[p->start].distance+p->value;
                v[p->end].parent=&v[p->start];
            }
        }
    }
    bool relax_mod(Edge* p)
    {
        if(v[p->start].distance==numeric_limits<int>::max()) {
            return false;
        }
        else {
            if(v[p->end].distance>v[p->start].distance+p->value) {
                v[p->end].distance=v[p->start].distance+p->value;
                v[p->end].parent=&v[p->start];
                return true;
            }
            else {
                return false;
            }
        }
    }
    void relax_mod2(Edge* p)
    {
        int min=p->value+(v[p->start].distance<0?v[p->start].distance:0);
        cout<<p->start<<" "<<p->end<<" "<<min<<endl;
        if(v[p->end].distance>min) {
            v[p->end].distance=min;
            v[p->end].parent=&v[p->start];
        }
    }
    void set_negative_cycle(int s)
    {
        v[s].circle=1;
        v[s].distance=numeric_limits<int>::min();
        while(v[s].parent->circle==0) {
            s=v[s].parent->number;
            v[s].circle=1;
            v[s].distance=numeric_limits<int>::min();
        }
    }
    void set_negative_pre(int s)
    {
        if(v[s].parent!=NULL&&v[s].distance!=numeric_limits<int>::min()) {
            v[s].distance=numeric_limits<int>::min();
            set_negative_pre(v[s].parent->number);
        }
        else {
            return;
        }
    }
};
#endif // BELL_H_INCLUDED
