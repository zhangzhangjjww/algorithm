#include<iostream>
#include<queue>
#include<limits>

const int MAX=100;

using namespace std;

struct Edge
{
    int start;
    int end;
    int value;
    Edge* next;
    bool is_tree;
    Edge(int s,int e,int v=1):start(s),end(e),value(v),next(NULL),is_tree(0) {}
};

enum color {white,gray,black};
struct Vertex
{
    Edge* head;
    color cc;
    int distance;
    int number;
    Vertex* parent;
    bool is_source;
    Vertex():head(NULL),parent(NULL),cc(white),distance(0),number(0),is_source(0) {}
};

struct Link_Graph
{
    int size;
    Vertex* v;
    Link_Graph(int num):size(num),v(0)
    {
        v=new Vertex[size+1];
        for(int i=0;i!=size+1;++i) {
            v[i].number=i;
        }
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
        while(tmp!=NULL&&tmp->end<end) {
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp&&tmp->end==end) {
            delete p;
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
        if(p&&p->end>end) {
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
            while(v[i].head!=NULL) {
                delete_single_edge(v[i].head->start,v[i].head->end);
            }
        }
        delete [] v;
    }
    void print()
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
    void BFS(int s)
    {
        for(int i=1;i!=s;++i) {
            v[i].cc=white;
            v[i].distance=numeric_limits<int>::max();
            v[i].parent=NULL;
            v[i].is_source=0;
        }
        for(int i=s+1;i!=size+1;++i) {
            v[i].cc=white;
            v[i].distance=numeric_limits<int>::max();
            v[i].parent=NULL;
            v[i].is_source=0;
        }
        v[s].is_source=1;
        v[s].cc=gray;
        v[s].distance=0;
        v[s].parent=NULL;
        queue<Vertex> que;
        que.push(v[s]);
        while(!que.empty()) {
            Vertex u=que.front();
            Edge* tmp=u.head;
            while(tmp) {
                if(v[tmp->end].cc==white) {
                    v[tmp->end].cc=gray;
                    v[tmp->end].distance=u.distance+1;
                    v[tmp->end].parent=&v[tmp->start];
                    que.push(v[tmp->end]);
                }
                tmp=tmp->next;
            }
            u.cc=black;
            que.pop();;
        }
    }
    void print_path(int s,int p)
    {
        if(s==p)
            cout<<s<<endl;
        else {
            if(v[p].parent==NULL) {
                cout<<"No path from "<<s<<" to "<<v<<" exist"<<endl;
            }
            else {
                print_path(s,v[p].parent->number);
                cout<<"->"<<p;
            }
        }
    }
};

struct Mat_Graph
{
  int size;
  color* cc;
  int* distance;
  int* parent;
  int** matrix;
  Mat_Graph(int num):size(num),matrix(0),cc(0),distance(0),parent(0)
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
      cc=new color[size+1];
      distance=new int[size+1];
      parent=new int[size+1];
      for(int i=0;i!=size+1;++i) {
        parent[i]=0;
        distance[i]=0;
        cc[i]=white;
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
  void BFS(int s)
  {
      for(int i=1;i!=s;++i) {
        parent[i]=0;
        cc[i]=white;
        distance[i]=numeric_limits<int>::max();
      }
      for(int i=s+1;i!=size+1;++i) {
        parent[i]=0;
        cc[i]=white;
        distance[i]=numeric_limits<int>::max();
      }
      parent[s]=0;
      cc[s]=gray;
      distance[s]=0;
      queue<int> que;
      que.push(s);
      while(!que.empty()) {
        int tmp=que.front();
        que.pop();
        for(int i=1;i!=size+1;++i) {
            if(matrix[tmp][i]!=0&&cc[i]==white) {
                cc[i]=gray;
                parent[i]=tmp;
                distance[i]=distance[tmp]+matrix[tmp][i];
                que.push(i);
            }
        }
        cc[tmp]=black;
      }
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
  int tree_diameter()
  {
      BFS(1);
      int s=0;
      int d=distance[1];
      for(int i=1;i!=size+1;++i) {
        if(distance[i]>d) {
            d=distance[i];
            s=i;
        }
      }
      BFS(s);
      int t;
      d=distance[1];
      for(int i=1;i!=size+1;++i) {
        if(distance[i]>d) {
            d=distance[i];
            t=i;
        }
      }
      cout<<"the diameter of the tree is "<<d<<" form "<<s<<" to "<<t<<endl;
  }
};

int main()
{
    cout<<"Enter the number of vertex:";
    int n;
    cin>>n;
    int a,b;
    //Link_Graph* p=new Link_Graph(n);
    Mat_Graph* p=new Mat_Graph(n);
    while(cin>>a>>b&&a&&b) {
        p->add_double_edge(a,b);
    }
    p->print();
    p->BFS(4);
    for(int i=1;i!=n+1;++i) {
        cout<<i<<"  distance:"<<p->distance[i]<<" parent:"<<p->parent[i];
        cout<<endl;
    }
    p->tree_diameter();
    delete p;
    return 0;
}
