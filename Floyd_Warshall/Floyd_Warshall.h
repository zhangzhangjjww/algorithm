#ifndef FLOYD_WARSHALL_H_INCLUDED
#define FLOYD_WARSHALL_H_INCLUDED

#include<iostream>
#include<limits>

using namespace std;

struct Link_Graph
{
    int sz;
    int** link_matrix;
    int** pairs_shortest_path;
    int** pairs_parent;
    Link_Graph(int s):sz(s),link_matrix(NULL),pairs_shortest_path(NULL),pairs_parent(NULL)
    {
        link_matrix=new int*[sz+1];
        pairs_shortest_path=new int*[sz+1];
        pairs_parent=new int*[sz+1];
        for(int i=0;i!=sz+1;++i) {
            pairs_shortest_path[i]=new int[sz+1];
            pairs_parent[i]=new int[sz+1];
            link_matrix[i]=new int[sz+1];
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
        for(int i=0;i!=sz+1;++i) {
            delete [] link_matrix[i];
            delete [] pairs_parent[i];
            delete [] pairs_shortest_path[i];
        }
        delete [] link_matrix;
        delete [] pairs_parent;
        delete [] pairs_shortest_path;
    }
    void add_single_edge(int s,int e,int v=1)
    {
        if(link_matrix[s][e]==numeric_limits<int>::max()) {
            link_matrix[s][e]=v;
        }
    }
    void add_double_edge(int s,int e,int v=1)
    {
        add_single_edge(s,e,v);
        add_single_edge(e,s,v);
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
    void floyd_warshall()
    {
        for(int i=0;i!=sz+1;++i) {
            for(int j=0;j!=sz+1;++j) {
                pairs_shortest_path[i][j]=link_matrix[i][j];
            }
        }
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                if(i==j) {
                    pairs_parent[i][j]=0;
                }
                else {
                    if(link_matrix[i][j]==numeric_limits<int>::max()) {
                        pairs_parent[i][j]=0;
                    }
                    else {
                        pairs_parent[i][j]=i;
                    }
                }
            }
        }
        for(int k=1;k!=sz+1;++k) {
            for(int i=1;i!=sz+1;++i) {
                for(int j=1;j!=sz+1;++j) {
                    if(pairs_shortest_path[i][k]!=numeric_limits<int>::max()&&pairs_shortest_path[k][j]!=numeric_limits<int>::max()) {
                        if(pairs_shortest_path[i][j]>pairs_shortest_path[i][k]+pairs_shortest_path[k][j]) {
                            pairs_shortest_path[i][j]=pairs_shortest_path[i][k]+pairs_shortest_path[k][j];
                            pairs_parent[i][j]=pairs_parent[k][j];
                        }
                    }
                }
            }
            print_path();
            print_parent();
        }
    }
    void print_path()
    {
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                cout<<pairs_shortest_path[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void print_parent()
    {
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                cout<<pairs_parent[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void transive_closure()
    {
        int** t=new int*[sz+1];
        for(int i=0;i!=sz+1;++i) {
            t[i]=new int[sz+1];
        }
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                if(i==j||link_matrix[i][j]!=numeric_limits<int>::max()) {
                    t[i][j]=1;
                }
                else {
                    t[i][j]=0;
                }
            }
        }
        for(int k=1;k!=sz+1;++k) {
            for(int i=1;i!=sz+1;++i) {
                for(int j=1;j!=sz+1;++j) {
                    t[i][j]=t[i][j]||(t[i][k]&&t[k][j]);
                }
            }
        }
        for(int i=1;i!=sz+1;++i) {
            for(int j=1;j!=sz+1;++j) {
                cout<<t[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0;i!=sz+1;++i) {
            delete [] t[i];
        }
        delete [] t;
    }
};

#endif // FLOYD_WARSHALL_H_INCLUDED
