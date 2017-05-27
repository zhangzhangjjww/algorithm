#include"binary_tree.h"
#include<iostream>
#include"random_matrix.cpp"


template<class T>  b_search_tree<T>::b_search_tree(Node<T>* a,int p,int r):root(0)
{
    random_matrix(a,p,r);
    for(int i=p;i!=r+1;++i)
        tree_insert(&a[i]);
}

template<class T> void b_search_tree<T>::tree_insert(Node<T>* z)
{
    Node<T>* y=0;
    Node<T>* x=root;
    while(x!=0)
    {
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    if(y==0)
        root=z;
    else
        if(z->key<y->key)
            y->left=z;
        else
            y->right=z;
    z->parent=y;
}

template<class T> void b_search_tree<T>::recurse_tree_insert(Node<T>* x,Node<T>* z)
{
    if(z->key<x->key)
    {
        if(x->left==0)
        {
            x->left=z;
            z->parent=x;
            return;
        }
        else
            recurse_tree_insert(x->left,z);
    }
    else
    {
        if(x->right==0)
        {
            x->right=z;
            z->parent=x;
        }
        else
            recurse_tree_insert(x->right,z);
    }
}
template<class T> void b_search_tree<T>::inorder_tree_walk(Node<T>* p)
{
    if(p!=0)
    {
        inorder_tree_walk(p->left);
        std::cout<<p->key<<" "<<p->data<<std::endl;
        inorder_tree_walk(p->right);
    }
}

template<class T> void b_search_tree<T>::no_recurse_using_stack_inorder_tree_walk()
{
    Node<T>* stack1[100];
    int top=-1;
    Node<T>* tmp=root;
    while(tmp!=0||top>-1)
    {
        while(tmp!=0)
        {
            stack1[++top]=tmp;
            tmp=tmp->left;
        }
        if(top>-1)
        {
            tmp=stack1[top--];
            std::cout<<tmp->key<<" "<<tmp->data<<std::endl;
            tmp=tmp->right;
        }
    }
}

template<class T> void b_search_tree<T>::no_recurse_no_stack_inorder_tree_walk()
{
    Node<T>* tmp=root;
    while(tmp!=0)
    {
        while(tmp->left!=0&&!tmp->left->visited)
            tmp=tmp->left;
        if(!tmp->visited)
        {
            std::cout<<tmp->key<<" "<<tmp->data<<std::endl;
            tmp->visited=true;
        }
        if(tmp->right!=0&&!tmp->right->visited)
            tmp=tmp->right;
        else
            tmp=tmp->parent;
    }
}

template<class T> Node<T>* b_search_tree<T>::tree_search(Node<T>* p,int k)
{
    if(p==0)
    {
        std::cout<<"error, no exist"<<std::endl;
        return 0;
    }
    if(p->key==k)
        return p;
    else
        if(k<p->key)
           tree_search(p->left,k);
        else
            tree_search(p->right,k);
}

template<class T> Node<T>* b_search_tree<T>::iterative_tree_search(Node<T>* p,int k)
{
    while(p!=0&&k!=p->key)
    {
        if(k<p->key)
            p=p->left;
        else
            p=p->right;
    }
    return p;
}

template<class T> Node<T>* b_search_tree<T>::tree_minimum(Node<T>* p)
{
    while(p->left!=0)
        p=p->left;
    return p;
}

template<class T> Node<T>* b_search_tree<T>::tree_maximum(Node<T>* p)
{
    while(p->right!=0)
        p=p->right;
    return p;
}

template<class T> Node<T>* b_search_tree<T>::tree_successor(Node<T>* p)
{
    if(p->right!=0)
        return tree_minimum(p->right);
    Node<T>* y=p->parent;
    while(y!=0&&y->right==p)
    {
        p=y;
        y=y->parent;
    }
    return y;
}

template<class T> Node<T>* b_search_tree<T>::tree_predecessor(Node<T>* p)
{
    if(p->left!=0)
        return tree_maximum(p->left);
    Node<T>* y=p->parent;
    while(y!=0&&y->left==p)
    {
        p=y;
        y=y->parent;
    }
    return y;
}

template<class T> void b_search_tree<T>::transplant(Node<T>* u,Node<T>* v)
{
    if(u->parent==0)
        root=v;
    else
        if(u==u->parent->left)
            u->parent->left=v;
        else
            u->parent->right=v;
    if(v!=0)
        v->parent=u->parent;
}

template<class T> void b_search_tree<T>::tree_delete(Node<T>* z)
{
    if(z->left==0)
        transplant(z,z->right);
    else
        if(z->right==0)
            transplant(z,z->left);
        else
        {
            Node<T>* y=tree_minimum(z->right);
            if(y->parent!=z)
            {
                transplant(y,y->right);
                y->right=z->right;
                y->right->parent=y;
            }
            transplant(z,y);
            y->left=z->left;
            z->left->parent=y;
        }
}
