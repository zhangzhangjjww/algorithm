#include<iostream>
#include<cstdlib>
#include"tree.h"

template<class T> void tree<T>::tree_insert(Node<T>* x)
{
    Node<T>* y=root;Node<T>* z=0;
    while(y!=0)
    {
        z=y;
        if(x->key<y->key)
            y=y->left;
        else
            y=y->right;
    }
    if(y==0)
        root=x;
    else
        if(x->key<z->key)
            z->left=x;
        else
            z->right=x;
    x->parent=z;
}

template<class T> void tree<T>::recurse_tree_insert(Node<T>* x,Node<T>* z)
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

template<class T> Node<T>* tree<T>::tree_search(Node<T>* x,int k)
{
    if(x==0)
    {
        std::cout<<"Don't exist!"<<std::endl;
        return 0;
    }
    if(x->key==k)
        return x;
    else
        if(k<x->key)
            tree_search(x->left,k);
        else
            tree_search(x->right,k);
}

template<class T> Node<T>* tree<T>::iterative_tree_search(Node<T>* x,int k)
{
    while(x!=0&&k!=x->key)
    {
        if(k<x->key)
            x=x->left;
        else
            x=x->right;
    }
    if(x==0)
    {
        std::cout<<"Don't exist!"<<std::endl;
    }
    return x;
}

template<class T> void tree<T>::transplant(Node<T>* u,Node<T>* v)
{
    if(v->parent==0)
        root=u;
    if(v==v->parent->left)
        v->parent->left=u;
    else
        v->parent->right=u;
    if(u!=0)
        u->parent=v->parent;
}

template<class T> void tree<T>::tree_delete1(Node<T>* x)
{
    if(x->left==0)
        transplant(x->right,x);
    else
        if(x->right==0)
            transplant(x->left,x);
        else
        {
            Node<T>* y=tree_minimum(x->right);
            if(y!=x->right)
            {
                transplant(y->right,y);
                y->right=x->right;
                y->right->parent=y;
            }
            transplant(y,x);
            y->left=x->left;
            y->left->parent=y;
        }
}

template<class T> void tree<T>::tree_delete2(Node<T>* x)
{
    if(x->left==0)
        transplant(x->right,x);
    else
        if(x->right==0)
            transplant(x->left,x);
        else
        {
            Node<T>* y=tree_maximum(x->left);
            if(y!=x->left)
            {
                transplant(y->left,y);
                y->left=x->left;
                y->left->parent=y;
            }
            transplant(y,x);
            y->right=x->right;
            y->right->parent=y;
        }
}

template<class T> void tree<T>::tree_delete(Node<T>* x)
{
    int i=rand()%2;
    if(i==0)
        tree_delete1(x);
    else
        tree_delete2(x);
}

template<class T> Node<T>* tree<T>::tree_minimum(Node<T>* x)
{
    while(x->left!=0)
        x=x->left;
    return x;
}

template<class T> Node<T>* tree_maximum(Node<T>* x)
{
    while(x->right!=0)
        x=x->right;
    return x;
}

template<class T> Node<T>* tree<T>::tree_successor(Node<T>* x)
{
    if(x->right!=0)
        return tree_minimum(x->right);
    else
    {
        Node<T>* y=x->parent;
        while(y!=0&&y->right==x)
        {
            x=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> Node<T>* tree<T>::tree_predecessor(Node<T>* x)
{
    if(x->left!=0)
        return tree_maximum(x->left);
    Node<T>* y=x->parent;
    while(y!=0&&y->left==x)
    {
        x=y;
        y=y->parent;
    }
    return y;
}

template<class T> void tree<T>::inorder_tree_walk(Node<T>* x)
{
    if(x!=0)
    {
        inorder_tree_walk(x->left);
        std::cout<<x->key<<" "<<x->data<<std::endl;
        inorder_tree_walk(x->right);
    }
}

template<class T> void tree<T>::no_recurse_using_stack_inorder_tree_walk()
{
    int top=-1;
    const int N=100;
    Node<T>* stack1[N];
    Node<T>* x=root;
    while(x!=0||top>-1)
    {
        while(x->left!=0)
        {
            stack1[++top]=x;
            x=x->left;
        }
        if(top>-1)
        {
            x=stack1[top--];
            std::cout<<x->key<<" "<<x->data<<std::endl;
            x=x->right;
        }
    }
}

template<class T> void tree<T>::no_recurse_no_stack_inorder_tree_walk() //缺少重置，只能使用一次
{
    Node<T>* x=root;
    while(x!=0)
    {
        while(x->left!=0&&!x->left->visited)
            x=x->left;
        if(!x->visited)
        {
            std::cout<<x->key<<" "<<x->data<<std::endl;
            x->visited=true;
        }
        if(x->right!=0&&!x->right->visited)
            x=x->right;
        else
            x=x->parent;
    }

}

template<class T> Node<T>* tree<T>::use_succ_find_parent(Node<T>* x)
{
    if(x->right==0)
    {
        if(x->succ->left==x)
            return x->succ;
        else
        {
            Node<T>* z1=x->succ;
            return find_parent(z1,x);
        }
    }
    else
    {
        Node<T>* y=tree_maximum(x->right);
        if(y->succ->left==x)
            return y->succ;
        else
        {
            Node<T>* z2=y->succ;
            return find_parent(z2,x);
        }
    }
}

template<class T> Node<T>* tree<T>::find_parent(Node<T>* z,Node<T>* x)
{
    Node<T>* m,p;
    if(z==0)
        m=root;
    else
        m=z->left;
    while(m!=x)
    {
        p=m;
        m=m->right;
    }
    return p;
}
