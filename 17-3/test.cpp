#include<iostream>
#include"binary_tree.h"
#include"binary_tree.cpp"


using namespace std;

int main()
{
    Binary_Tree<int> t;
    Data<int> dd[14];
    for(int i=0;i!=7;++i)
    {
        dd[i].key=2*i;
        dd[i].value=i;
    }
    for(int i=5;i!=12;++i)
    {
        dd[i].key=2*(i-5)+1;
        dd[i].value=i;
    }

    for(int i=0;i!=14;++i)
        t.binary_tree_insert(dd[i]);
    //t.binary_tree_delete(dd[3]);
    t.binary_tree_walk_in_order2(t.root);
    return 0;
}
