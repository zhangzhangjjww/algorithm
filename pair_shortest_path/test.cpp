#include"pair_shortest_path.h"
#include<fstream>

using namespace std;

int main()
{
    ifstream is("graph.txt");
    int n;
    is>>n;
    Link_Graph* p=new Link_Graph(n);
    int a,b,c;
    while(is>>a>>b>>c&&a&&b) {
        p->add_single_edge(a,b,c);
    }
    p->print();
    p->slow_all_pairs_shortest_path();
    /*for(int i=1;i!=n+1;++i) {
        for(int j=1;j!=n+1;++j) {
            cout<<p->pairs_parent[i][j]<<" ";
        }
        cout<<endl;
    }*/
    for(int i=1;i!=n+1;++i) {
        for(int j=1;j!=n+1;++j) {
            if(i==j) {
                continue;
            }
            p->print_all_pairs_shortest_path(i,j);
            cout<<endl;
        }
    }
    //p->print_all_pairs_shortest_path(1,2);
    delete p;
    is.close();
    return 0;
}
