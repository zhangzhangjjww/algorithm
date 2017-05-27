#include"Floyd_Warshall.h"
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
    //p->print();
    p->floyd_warshall();
    p->transive_closure();
    //p->print_all_pairs_shortest_path(1,2);
    delete p;
    is.close();
    return 0;
}
