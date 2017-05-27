#include<iostream>
#include"os_tree.h"

template<class T> void OS_Tree<T>::os_tree_left_rotate(OS_Node<T>* z)
{
    OS_Node<T>* y=z->right;
    y->parent=z->parent;
    if(z->parent==nil)
        root=y;
    else
        if(z==z->parent->left)
            z->parent->left=y;
        else
            z->parent->right=y;
    z->right=y->left;
    if(y->left!=nil)
        y->left->parent=z;
    y->left=z;
    z->parent=y;
    y->os_rank=z->os_rank;
    z->os_rank=z->left->os_rank+z->right->os_rank+1;
}

template<class T> void OS_Tree<T>::os_tree_right_rotate(OS_Node<T>* z)
{
    OS_Node<T>* y=z->left;
    y->parent=z->parent;
    if(z->parent==nil)
        root=y;
    else
        if(z==z->parent->left)
            z->parent->left=y;
        else
            z->parent->right=y;
    z->left=y->right;
    if(y->right!=nil)
        y->right->parent=z;
    y->right=z;
    z->parent=y;
    y->os_rank=z->os_rank;
    z->os_rank=z->left->os_rank+z->right->os_rank+1;
}

template<class T> void OS_Tree<T>::os_tree_set_nil()
{
    nil->parent=nil;
    nil->left=nil;
    nil->right=nil;
    nil->color=black;
    nil->os_rank=0;
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_search(OS_Node<T>* z,int k)
{
    if(z==nil)
    {
        std::cout<<"NO exist!"<<std::endl;
        return nil;
    }
    if(z->key==k)
        return z;
    else
        if(k<z->key)
            return os_tree_search(z->left,k);
        else
            return os_tree_search(z->right,k);
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_maximum(OS_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->right!=nil)
        z=z->right;
    return z;
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_minimum(OS_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->left!=nil)
        z=z->left;
    return z;
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_successor(OS_Node<T>* z)
{
    if(z->right!=nil)
        return os_tree_minimum(z->right);
    else
    {
        OS_Node<T>* y=z->parent;
        while(y!=nil&&z==y->right)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_predecessor(OS_Node<T>* z)
{
    if(z->left!=nil)
        return os_tree_maximum(z->left);
    else
    {
        OS_Node<T>* y=z->parent;
        while(y!=nil&&z==y->left)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}
template<class T> void OS_Tree<T>::os_tree_walk_in_order(OS_Node<T>* z)
{
    if(z->left!=nil)
        os_tree_walk_in_order(z->left);
    std::cout<<z->key<<" "<<z->data<<" "<<z->os_rank<<" "<<z->color<<std::endl;
    if(z->right!=nil)
        os_tree_walk_in_order(z->right);
}

template<class T> void OS_Tree<T>::os_tree_insert(OS_Node<T>* z)
{
    OS_Node<T>* y=nil;
    OS_Node<T>* x=root;
    while(x!=nil)
    {
        y=x;
        ++y->os_rank;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    if(y==nil)
        root=z;
    else
    if(z->key<y->key)
        y->left=z;
    else
        y->right=z;
    z->parent=y;
    z->left=nil;
    z->right=nil;
    z->color=red;
    os_tree_insert_fixup(z);
}

template<class T> void OS_Tree<T>::os_tree_insert_fixup(OS_Node<T>* z)
{
    while(z->parent->color==red)
    {
        if(z->parent==z->parent->parent->left)
        {
            OS_Node<T>* y=z->parent->parent->right;
            if(y->color==red)
            {
                y->color=black;
                z->parent->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)
                {
                    z=z->parent;
                    os_tree_left_rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                os_tree_right_rotate(z->parent->parent);
            }
        }
        else
        {
            OS_Node<T>* y=z->parent->parent->left;
            if(y->color==red)
            {
                y->color=black;
                z->parent->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->left)
                {
                    z=z->parent;
                    os_tree_right_rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                os_tree_left_rotate(z->parent->parent);
            }
        }
    }
    root->color=black;
}

template<class T> void OS_Tree<T>::os_tree_transplant(OS_Node<T>* u,OS_Node<T>* v)
{
   if(u==u->parent->left)
        u->parent->left=v;
   else
        u->parent->right=v;
   v->parent=u->parent;
}

template<class T> void OS_Tree<T>::os_tree_delete(OS_Node<T>* z)
{
    OS_Node<T>* y=z;
    OS_Node<T>* x=0;
    r_or_b y_original_color=y->color;
    os_tree_rank_fixup(z);
    if(z->left==nil)
    {
        x=z->right;
        os_tree_transplant(z,z->right);
    }
    else
    {
        if(z->right==nil)
        {
            x=z->left;
            os_tree_transplant(z,z->left);
        }
        else
        {
            y=os_tree_minimum(z->right);
            y_original_color=y->color;
            x=y->right;
            if(z==y->parent)
                x->parent=y;
            else
            {
                os_tree_transplant(y,x);
                y->right=z->right;
                y->right->parent=y->right;
                y->os_rank=z->os_rank;
            }
            os_tree_transplant(z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }
    }
    if(y_original_color==black)
        os_tree_delete_fixup(x);
}

template<class T> void OS_Tree<T>::os_tree_rank_fixup(OS_Node<T>* z)
{
    OS_Node<T>* y=0;
    if(z->left==nil||z->right==nil)
        y=z;
    else
        y=os_tree_minimum(z->right);
    OS_Node<T>* p=y->parent;
    while(p!=nil)
    {
        --p->os_rank;
        p=p->parent;
    }
}

template<class T> void OS_Tree<T>::os_tree_delete_fixup(OS_Node<T>* x)
{
    while(x!=root&&x->color==black)
    {
        OS_Node<T>* w=0;
        if(x==x->parent->left)
        {
            w=x->parent->right;
            if(w->color==red)
            {
                w->color=black;
                x->parent->color=red;
                os_tree_left_rotate(x->parent);
                w=x->parent->right;
            }
            else
            {
                if(w->left->color==black&&w->right->color==black)
                {
                    w->color=red;
                    x=x->parent;
                }
                else
                {
                    if(w->right->color==black)
                    {
                        w->color=red;
                        w->left->color=black;
                        os_tree_right_rotate(w);
                        w=x->parent->right;
                    }
                    w->color=x->parent->color;
                    x->parent->color=black;
                    w->right->color=black;
                    os_tree_left_rotate(x->parent);
                    x=root;
                }
            }
        }
        else
        {
           w=x->parent->left;
           if(w->color==red)
           {
               w->color=black;
               x->parent->color=red;
               os_tree_right_rotate(x->parent);
               w=x->parent->left;
           }
           else
           {
               if(w->right->color==black&&w->left->color==black)
               {
                   w->color=red;
                   x=x->parent;
               }
               else
               {
                   if(w->left->color==black)
                   {
                       w->right->color=black;
                       w->color=red;
                       os_tree_left_rotate(w);
                       w=x->parent->left;
                   }
                   w->color=x->parent->color;
                   x->parent->color=black;
                   w->left->color=black;
                   os_tree_right_rotate(x->parent);
                   x=root;
               }
           }
        }
    }
    x->color=black;
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_select(OS_Node<T>* z,int k)
{
    int r=z->left->os_rank+1;
    if(r==k)
        return z;
    if(k<r)
        return os_tree_select(z->left,k);
    else
        return os_tree_select(z->right,k-r);
}

template<class T> int OS_Tree<T>::os_tree_rank(OS_Node<T>* z)
{
    int r=z->left->os_rank+1;
    while(z!=root)
    {
        if(z==z->parent->left)
            z=z->parent;
        else
        {
            r=r+z->parent->left->os_rank+1;
            z=z->parent;
        }
    }
    return r;
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_no_recurse_select(OS_Node<T>* z,int k)
{
    OS_Node<T>* y=z;
    while(y!=nil)
    {
        int r=y->left->os_rank+1;
        if(r==k)
            return y;
        else
            if(k<r)
                y=y->left;
            else
            {
                k=k-r;
                y=y->right;
            }
    }
}

template<class T> int OS_Tree<T>::os_tree_recurse_rank(OS_Node<T>* x,OS_Node<T>* z)
{
    if(x->key==z->key)
        return x->left->os_rank+1;
    else
        if(x->key>z->key)
            return os_tree_recurse_rank(x->left,z);
        else
            return x->left->os_rank+1+os_tree_recurse_rank(x->right,z);
}

template<class T> OS_Node<T>* OS_Tree<T>::os_tree_find_i_successor(OS_Node<T>* z,int i)
{
    int r=os_tree_rank(z);
    int s=r+i;
    return os_tree_select(root,s);
}

