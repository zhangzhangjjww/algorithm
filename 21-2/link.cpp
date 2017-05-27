#include<iostream>
#include<limits>
#include<cstdlib>
#include<fstream>

using namespace std;

template <class T> struct Node
{
    T key;
    Node* next;
    Node* pre;
    Node(T k):key(k),next(NULL),pre(NULL) {}
};

template <class T> struct List
{
    Node<T>* head;
    Node<T>* tail;
    int vol;
    List():head(NULL),tail(NULL),vol(0) {}
    ~List()
    {
        while(head!=NULL) {
            List_delete(head);
        }
    }
    Node<T>* List_search(T k)
    {
        Node<T>* tmp=head;
        while(tmp&&tmp->key<k) {
            tmp=tmp->next;
        }
        if(tmp&&tmp->key==k) {
            return tmp;
        }
        else {
            return NULL;
        }
    }
    void List_insert(T k)
    {
        Node<T>* p=new Node<T>(k);
        Node<T>* tmp=head;
        if(head==NULL) {
            head=p;
            tail=p;
            ++vol;
            return;
        }
        if(head&&head->key>k) {
            p->next=head;
            head->pre=p;
            head=p;
            ++vol;
            return;
        }
        Node<T>* prevv=NULL;
        while(tmp&&tmp->key<k) {
            prevv=tmp;
            tmp=tmp->next;
        }
        if(tmp==NULL) {
            tail->next=p;
            p->pre=tail;
            tail=p;
            ++vol;
            return;
        }
        else {
            prevv->next=p;
            p->pre=prevv;
            p->next=tmp;
            tmp->pre=p;
            ++vol;
        }
    }
    void List_delete(T k)
    {
        Node<T>* tmp=List_search(k);
        if(tmp==NULL) {
            return;
        }
        else {
            List_delete(tmp);
        }
    }
    void List_delete(Node<T>* tmp)
    {
        Node<T>* p1=head,*p2=NULL;
        if(tmp==p1) {
            head=head->next;
            --vol;
            delete p1;
            return;
        }
        while(p1&&p1!=tmp) {
            p2=p1;
            p1=p1->next;
        }
        if(p1==tail) {
            tail=p1->pre;
            --vol;
            delete p1;
            return;
        }
        else {
            p2->next=p1->next;
            p1->next->pre=p2;
            --vol;
            delete p1;
        }
    }
    void List_union(List<T>& p)
    {
        Node<T>* tmp=p.head;
        while(tmp) {
            List_insert(tmp->key);
            tmp=tmp->next;
        }
        while(p.head) {
            p.List_delete(p.head);
        }
    }
};

struct Edge
{
    int start;
    int end;
    int value;
    Edge* e_next;
    Edge(int s,int e,int v):start(s),end(e),value(v),e_next(NULL) {}
};

struct Vertex
{
    Edge* e_head;
    int number;
    int scc;
    Vertex():e_head(NULL),number(0),scc(0) {}
};

struct Link_Graph
{
    int size;
    Vertex* v;
    Link_Graph(int nums):size(nums),v(0)
    {
        v=new Vertex[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
        }
    }
    ~Link_Graph()
    {
        for(int i=0;i!=size+1;++i) {
            //Edge* tmp=v[i].e_head;
            while(v[i].e_head) {
                delete_single_edge(i,v[i].e_head->end);
            }
        }
        delete [] v;
    }
    void add_single_edge(int start,int end,int value=1)
    {
        Edge* p=new Edge(start,end,value);
        if(v[start].e_head==NULL||v[start].e_head->end>end) {
            p->e_next=v[start].e_head;
            v[start].e_head=p;
            return;
        }
        Edge* tmp=v[start].e_head,*prev=NULL;
        while(tmp&&tmp->end<end) {
            prev=tmp;
            tmp=tmp->e_next;
        }
        if(tmp&&tmp->end==end) {
            delete p;
            return;
        }
        else {
            prev->e_next=p;
            p->e_next=tmp;
        }
    }
    void add_double_edge(int start,int end,int value=1)
    {
        add_single_edge(start,end,value);
        add_single_edge(end,start,value);
    }
    void delete_single_edge(int start,int end)
    {
        Edge* tmp=v[start].e_head,*prev=NULL;
        while(tmp&&tmp->end<end) {
            prev=tmp;
            tmp=tmp->e_next;
        }
        if(tmp&&tmp->end>end) {
            return;
        }
        if(prev==NULL) {
            v[start].e_head=tmp->e_next;
        }
        else {
            prev->e_next=tmp->e_next;
        }
        delete tmp;
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
            Edge* tmp=v[i].e_head;
            while(tmp) {
                cout<<"->"<<tmp->end;
                tmp=tmp->e_next;
            }
            cout<<" scc:"<<v[i].scc;
            cout<<endl;
        }
    }
    void connected_components()
    {
        List<int> *ll=new List<int>[size+1];
        for(int i=1;i!=size+1;++i) {
            ll[i].List_insert(i);
        }
        for(int i=1;i!=size+1;++i) {
            Edge* tmp=v[i].e_head;
            while(tmp) {
                int key1=find_set(ll,tmp->start);
                int key2=find_set(ll,tmp->end);
                if(key1!=key2) {
                    if(ll[key1].vol<=ll[key2].vol) {
                        ll[key2].List_union(ll[key1]);
                    }
                    else {
                        ll[key1].List_union(ll[key2]);
                    }
                }
                tmp=tmp->e_next;
            }
        }
        int num=0;
        for(int i=1;i!=size+1;++i) {
            if(ll[i].head!=NULL) {
                ++num;
                Node<int>* lp=ll[i].head;
                while(lp) {
                    v[lp->key].scc=num;
                    lp=lp->next;
                }
            }
        }
        delete [] ll;
    }
    int find_set(List<int>* ll,int u)
    {
        for(int i=1;i!=size+1;++i) {
            Node<int>* tmp=ll[i].head;
            while(tmp&&tmp->key<u) {
                tmp=tmp->next;
            }
            if(tmp&&tmp->key==u) {
                return i;
            }
        }
        return 0;
    }
};
int main()
{
    /*List<int> l,l2;
    for(int i=0;i!=9;++i) {
        l.List_insert(10-i);
        l2.List_insert(10+i);
    }
    l.List_delete(3);
    Node<int>* tmp=l.head;
    l.List_union(l2);
    cout<<l.vol<<" "<<l2.vol<<endl;
    while(tmp) {
        cout<<tmp->key<<endl;
        tmp=tmp->next;
    }*/
    int n;
    cout<<"enter:";
    cin>>n;
    Link_Graph* p=new Link_Graph(n);
    int a=0,b=0;
    while(cin>>a>>b&&a&&b) {
        p->add_double_edge(a,b);
    }
    p->print();
    p->connected_components();
    p->print();
    delete p;
    return 0;
}
