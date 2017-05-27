#include"rb_tree.h"
#include"rb_tree.cpp"


int main()
{
    RB_Tree<int> tree;
    RB_Node<int> node[20];
    int number[20]={3,10,12,7,14,16,14,17,21,19,20,21,26,41,30,28,38,35,39,47};
    for(int i=0;i!=20;++i)
    {
        node[i].key=number[i];
        node[i].data=node[i].key;
        tree.rb_tree_insert(&node[i]);
    }
    tree.walk_in_order(tree.rb_root);
   // tree.rb_tree_delete(&node[3]);
   // std::cout<<std::endl;
   // tree.walk_in_order(tree.rb_root);
    return 0;
}
