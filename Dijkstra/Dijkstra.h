#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include<iostream>
#include<vector>
#include"piror_queue.h"

using namespace std;

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
    int distance;
    Vertex* parent;
    int number;
    bool operator<(const Vertex& v)
    {
        if(distance<v.distance) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator>(const Vertex& v)
    {
        if(distance>v.distance) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator==(const Vertex& v)
    {
        return v.distance==distance;
    }
    Vertex():head(NULL),distance(0),parent(NULL),number(0) {}
    Vertex(const Vertex& v):head(NULL),distance(v.distance),parent(NULL),number(v.number) {}  //只为实现算法，简化下不处理指针
    Vertex& operator=(const Vertex& v)  //只为实现算法，简化下不处理指针
    {
        distance=v.distance;
        number=v.number;
        return *this;
    }
};

class Link_Graph
{
public:
    Vertex* v;
    int sz;
    Link_Graph(int s):v(NULL),sz(s)
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
                delete_single_edge(i,v[i].head->end);
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
        Edge* tmp=v[s].head,*pre=NULL;
        while(tmp&&tmp->end<e) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp&&tmp->end==e) {
            delete p;
        }
        else {
            pre->next=p;
            p->next=tmp;
        }
    }
    void add_double_edge(int s,int e,int val)
    {
        add_single_edge(s,e,val);
        add_single_edge(e,s,val);
    }
    void delete_single_edge(int s,int e)
    {
        Edge* p=v[s].head,*pre=NULL;
        while(p&&p->end<e) {
            pre=p;
            p=p->next;
        }
        if(p==NULL||p->end>e) {
            return;
        }
        else {
            if(pre==NULL) {
                v[s].head=v[s].head->next;
            }
            else {
                pre->next=p->next;
            }
            delete p;
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
    void Dijkstra(int s)
    {
        initialize_single_source(s);
        Piror_Queue<Vertex> q;
        for(int i=1;i!=sz+1;++i) {
            q.queue_insert(v[i]);
        }
        while(!q.is_empty()) {
            Vertex u=q.queue_extract_min();
            Edge* tmp=v[u.number].head;
            while(tmp) {
                relax(tmp);
                tmp=tmp->next;
            }
        }
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
        }
    }
    void relax(Edge* p)
    {
        if(v[p->start].distance==numeric_limits<int>::max()) {
            return;
        }
        if(v[p->end].distance>v[p->start].distance+p->value) {
            v[p->end].distance=v[p->start].distance+p->value;
            v[p->end].parent=&v[p->start];
        }
    }
};

#endif // DIJKSTRA_H_INCLUDED
