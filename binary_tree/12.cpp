#include<iostream>
#include<ctime>
#include"binary_tree.h"
#include"binary_tree.cpp"

using namespace std;

const int N=10;

int main()
{
    srand(time(0));
    Node<int> a[N];
    for(size_t i=0;i!=N;++i)
    {
        a[i].key=N-i;
        a[i].data=i;
    }
    b_search_tree<int> t(a,0,N-1);
    for(int i=0;i!=N;++i)
        cout<<a[i].key<<" "<<a[i].data<<endl;
    cout<<endl;
    t.inorder_tree_walk(t.root);
    return 0;
}
