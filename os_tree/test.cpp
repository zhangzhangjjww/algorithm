#include<iostream>
#include"os_tree.h"
#include"os_tree.cpp"

template<class T> int get_inversions(OS_Node<T>* z,int p,int r);//14.1-7

int main()
{
    OS_Tree<int> tree;
    OS_Node<int> node[20];
    int number[20]={3,10,12,7,14,16,14,17,21,19,20,21,26,41,30,28,38,35,39,47};
    for(int i=0;i!=20;++i)
    {
        node[i].key=number[i];
        node[i].data=node[i].key;
        tree.os_tree_insert(&node[i]);
    }
    tree.os_tree_walk_in_order(tree.root);
    std::cout<<std::endl;
    OS_Node<int>* tmp=tree.os_tree_select(tree.root,17);
    std::cout<<tmp->key<<" "<<tmp->color<<" "<<tmp->os_rank<<std::endl;
    OS_Node<int>* tmp2=tree.os_tree_no_recurse_select(tree.root,17);
    std::cout<<tmp2->key<<" "<<tmp2->color<<" "<<tmp2->os_rank<<std::endl;
    tree.os_tree_delete(&node[2]);
    std::cout<<tree.os_tree_rank(&node[16])<<std::endl;
    std::cout<<tree.os_tree_recurse_rank(tree.root,&node[16])<<std::endl;
    //tree.os_tree_delete(&node[3]);
    //tree.os_tree_walk_in_order(tree.root);
    std::cout<<get_inversions(node,0,19)<<std::endl;
    return 0;
}


template<class T> int get_inversions(OS_Node<T>* z,int p,int r)
{
    int sum=0;int tmp;
    OS_Tree<T> tree2;
    for(int i=p;i!=r+1;++i)
    {
        tree2.os_tree_insert(&z[i]);
        tmp=i+1-tree2.os_tree_rank(&z[i]);
        //std::cout<<tmp<<std::endl;
        sum+=tmp;
    }
    return sum;
}
