#include"piror_queue.h"
#include"Dijkstra.h"
#include<fstream>

using namespace std;

int main()
{
    int n;
    ifstream is("graph.txt");
    is>>n;
    Link_Graph* p=new Link_Graph(n);
    int a,b,c;
    while(is>>a>>b>>c&&a&&b&&c) {
        p->add_single_edge(a,b,c);
    }
    p->print();
    p->Dijkstra(1);
    p->print_path();
    delete p;
    is.close();
    return 0;
}
