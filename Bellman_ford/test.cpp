#include"Bell.h"
#include<fstream>

int main()
{
    ifstream is("graph2.txt");
    int n;
    is>>n;
    Link_Graph* lp=new Link_Graph(n);
    int a,b,c;
    while(is>>a>>b>>c&&a&&b) {
        lp->add_single_edge(a,b,c);
    }
    lp->print();
    if(lp->Bellman_Ford_mod(1)) {
        lp->print_path();
    }
    else {
        cout<<"a negative cycle"<<endl;
        lp->print_path();
    }
    //lp->Dag_shortest_path(2);
   // lp->print_path();
    delete  lp;
    is.close();
    return 0;
}
