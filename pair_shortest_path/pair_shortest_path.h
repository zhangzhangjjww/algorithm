#ifndef PAIR_SHORTEST_PATH_H_INCLUDED
#define PAIR_SHORTEST_PATH_H_INCLUDED

#include<iostream>
#include<vector>
#include<limits>

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
    int number;
    Vertex* parent;
    Edge* head;
    int distance;
    Vertex():number(0),parent(NULL),head(NULL),distance(0) {}
};

class Link_Graph
{
public:
    Vertex* v;
    int sz;
    int** link_matrix;
    int** pairs_shortest_path;
    int** pairs_parent;
    Link_Graph(int s):v(NULL),sz(s),link_matrix(NULL),pairs_shortest_path(NULL),pairs_parent(NULL)
    {
        v=new Vertex[sz+1];
        for(int i=0;i!=sz+1;++i) {
            v[i].number=i;
        }
        link_matrix=new int*[sz+1];
        pairs_shortest_path=new int*[sz+1];
        pairs_parent=new int*[sz+1];
        for(int i=0;i!=sz+1;++i) {
            link_matrix[i]=new int[sz+1];
            pairs_shortest_path[i]=new int[sz+1];
            pairs_parent[i]=new int[sz+1];
        }
        for(int i=0;i!=sz+1;++i) {
            for(int j=0;j!=sz+1;++j) {
                link_matrix[i][j]=numeric_limits<int>::max();
                pairs_shortest_path[i][j]=numeric_limits<int>::max();
                pairs_parent[i][j]=0;
            }
        }
        for(int i=0;i!=sz+1;++i) {
            link_matrix[i][i]=0;
        }
    }
    ~Link_Graph()
    {
        delete [] v;
        for(int i=0;i!=sz+1;++i) {
            delete [] link_matrix[i];
            delete [] pairs_shortest_path[i];
            delete [] pairs_parent[i];
        }
        delete [] link_matrix;
        delete [] pairs_shortest_path;
        delete [] pairs_parent;
    }
    void add_single_edge(int s,int e,int val=1)
    {
        if(link_matrix[s][e]==numeric_limits<int>::max()) {
            link_matrix[s][e]=val;
        }
    }
    void add_double_edge(int s,int e,int val=1)
    {
        add_single_edge(s,e,val);
        add_single_edge(e,s,val);
    }
    void delete_single_edge(int s,int e)
    {
        if(link_matrix[s][e]!=numeric_limits<int>::max()) {
            link_matrix[s][e]=numeric_limits<int>::max();
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
            for(int j=1;j!=sz+1;++j) {
                cout<<link_matrix[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void slow_all_pairs_shortest_path()
    {
        int** l_pre=new int*[sz+1];
        for(int i=0;i!=sz+1;++i) {
            l_pre[i]=new int[sz+1];
        }
        for(int i=0;i!=sz+1;++i) {
            for(int j=0;j!=sz+1;++j) {
                l_pre[i][j]=link_matrix[i][j];
            }
        }
        for(int i=2;i!=sz+1;++i) {
            extend_shortest_path(l_pre,pairs_shortest_path,link_matrix);
            int** tmp=l_pre;
            l_pre=pairs_shortest_path;
            pairs_shortest_path=tmp;
            for(int j=1;j!=sz+1;++j) {
                for(int k=1;k!=sz+1;++k) {
                    cout<<l_pre[j][k]<<"\t";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        int** tmp=l_pre;
        l_pre=pairs_shortest_path;
        pairs_shortest_path=tmp;
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                if(i==j) {
                    continue;
                }
                else {
                    for(int k=1;k!=sz+1;++k) {
                        if(k==j) {
                            continue;
                        }
                        if(pairs_shortest_path[i][j]!=numeric_limits<int>::max()&&pairs_shortest_path[i][k]!=numeric_limits<int>::max()&&link_matrix[k][j]!=numeric_limits<int>::max()) {
                            if(pairs_shortest_path[i][j]==pairs_shortest_path[i][k]+link_matrix[k][j]) {
                                pairs_parent[i][j]=k;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i!=sz+1;++i) {
            pairs_parent[i][i]=0;
        }
        for(int i=0;i!=sz+1;++i) {
            delete [] l_pre[i];
        }
        delete [] l_pre;
    }
    void fast_all_pairs_shortest_path()
    {
        int** l_pre=new int*[sz+1];
        for(int i=0;i!=sz+1;++i) {
            l_pre[i]=new int[sz+1];
        }
        for(int i=0;i!=sz+1;++i) {
            for(int j=0;j!=sz+1;++j) {
                l_pre[i][j]=link_matrix[i][j];
            }
        }
        for(int i=1;i<sz;i=i*2) {
            extend_shortest_path(l_pre,pairs_shortest_path,l_pre);
            int** tmp=l_pre;
            l_pre=pairs_shortest_path;
            pairs_shortest_path=tmp;
            for(int j=1;j!=sz+1;++j) {
                for(int k=1;k!=sz+1;++k) {
                    cout<<l_pre[j][k]<<"\t";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        int** tmp=l_pre;
        l_pre=pairs_shortest_path;
        pairs_shortest_path=tmp;
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                if(i==j) {
                    continue;
                }
                else {
                    for(int k=1;k!=sz+1;++k) {
                        if(k==j) {
                            continue;
                        }
                        if(pairs_shortest_path[i][j]!=numeric_limits<int>::max()&&pairs_shortest_path[i][k]!=numeric_limits<int>::max()&&link_matrix[k][j]!=numeric_limits<int>::max()) {
                            if(pairs_shortest_path[i][j]==pairs_shortest_path[i][k]+link_matrix[k][j]) {
                                pairs_parent[i][j]=k;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i!=sz+1;++i) {
            pairs_parent[i][i]=0;
        }
        for(int i=0;i!=sz+1;++i) {
            delete [] l_pre[i];
        }
        delete [] l_pre;
    }
    void print_all_pairs_shortest_path(int i,int j)
    {
        if(i==j) {
            cout<<i<<" ";
        }
        else {
            if(pairs_parent[i][j]==0) {
                cout<<"no path from "<<i<<" to"<<j<<endl;
            }
            else {
                print_all_pairs_shortest_path(i,pairs_parent[i][j]);
                cout<<j<<" ";
            }
        }
    }
private:
    void extend_shortest_path(int** l_pre,int** l_now,int** w)
    {
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                l_now[i][j]=numeric_limits<int>::max();
                for(int k=1;k!=sz+1;++k) {
                    if(l_pre[i][k]==numeric_limits<int>::max()||w[k][j]==numeric_limits<int>::max()) {

                    }
                    else {
                        if(l_pre[i][k]+w[k][j]<l_now[i][j]) {
                            l_now[i][j]=l_pre[i][k]+w[k][j];
                        }
                    }
                }
            }
        }
    }
};




#endif // PAIR_SHORTEST_PATH_H_INCLUDED
