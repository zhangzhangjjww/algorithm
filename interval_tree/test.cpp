#include<iostream>
#include<cstdlib>
#include"interval_tree.h"
#include"interval_tree.cpp"


int main()
{
    Interval_Tree<int> tree;
    Interval_Node<int> node[20];
    int number[20]={3,10,12,7,14,16,14,17,21,19,20,21,26,41,30,28,38,35,39,47};
    for(int i=0;i!=20;++i)
    {
        node[i].key.low=number[i];
        node[i].key.high=number[i]+5;
        node[i].data=node[i].key.high;
        node[i].max=node[i].key.low;
        tree.Interval_Tree_insert(&node[i]);
    }
    tree.Interval_Tree_walk_in_order(tree.root);
    std::cout<<std::endl;
    interval test(4,13);
    Interval_Node<int>* tmp=tree.Interval_Tree_overlaps(test);
    std::cout<<tmp->key.low<<" "<<tmp->key.high<<" "<<tmp->max<<" "<<tmp->color<<" "<<tmp->data<<std::endl;
    std::cout<<std::endl;
    tmp=tree.Interval_Tree_min_overlaps(tree.root,test);
    std::cout<<tmp->key.low<<" "<<tmp->key.high<<" "<<tmp->max<<" "<<tmp->color<<" "<<tmp->data<<std::endl;
    std::cout<<std::endl;
    tree.Interval_Tree_all_overlaps(tree.root,test);
    std::cout<<std::endl;
    tree.Interval_Tree_delete(&node[19]);
    tree.Interval_Tree_walk_in_order(tree.root);
    std::cout<<std::endl;
    tree.Interval_Tree_insert(&node[19]);
    tree.Interval_Tree_walk_in_order(tree.root);
    std::cout<<std::endl;
    system("pause");
    return 0;
}
