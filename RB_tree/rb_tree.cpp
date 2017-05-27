#include<iostream>
#include"rb_tree.h"

template<class T> void RB_Tree<T>::rb_tree_set_value(RB_Node<T>* z)
{
    z->parent=nil;
    z->left=nil;
    z->right=nil;
    z->color=black;
}

template<class T> void RB_Tree<T>::walk_in_order(RB_Node<T>* z)
{
    if(z->left!=nil)
        walk_in_order(z->left);
    std::cout<<z->key<<" "<<z->color<<" "<<z->data<<std::endl;
    if(z->right!=nil)
        walk_in_order(z->right);
}

template<class T> RB_Node<T>* RB_Tree<T>::rb_tree_search(RB_Node<T>* z,int k)
{
    if(z==nil)
    {
        std::cout<<"No exist"<<std::endl;
        return nil;
    }
    if(z->key==k)
        return z;
    else
        if(k<z->key)
            return rb_tree_search(z->left,k);
        else
            return rb_tree_search(z->right,k);
}

template<class T> RB_Node<T>* RB_Tree<T>::rb_tree_maximum(RB_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->right!=nil)
        z=z->right;
    return z;
}

template<class T> RB_Node<T>* RB_Tree<T>::rb_tree_minimum(RB_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->left!=nil)
        z=z->left;
    return z;
}

template<class T> RB_Node<T>* RB_Tree<T>::rb_tree_successor(RB_Node<T>* z)
{
    if(z->right!=nil)
        return rb_tree_maximum(z->right);
    else
    {
        RB_Node<T>* y=z->parent;
        while(y!=nil&&z==y->right)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> RB_Node<T>* RB_Tree<T>::rb_tree_decessor(RB_Node<T>* z)
{
    if(z->left!=nil)
        return rb_minimum(z->left);
    else
    {
        RB_Node<T>* y=z->parent;
        while(y!=nil&&z=y->left)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> void RB_Tree<T>::right_rotate(RB_Node<T>* z)
{
    RB_Node<T>* y=z->left;
    if(z->parent==nil)
        rb_root=y;
    else
    if(z==z->parent->left)
        z->parent->left=y;
    else
        z->parent->right=y;
    y->parent=z->parent;
    z->left=y->right;
    if(y->right!=nil)
        z->left->parent=z;
    y->right=z;
    z->parent=y;
}

template<class T> void RB_Tree<T>::left_rotate(RB_Node<T>* z)
{
    RB_Node<T>* y=z->right;
    z->right=y->left;
    if(y->left!=nil)
        y->left->parent=z;
    if(z->parent==nil)
        rb_root=y;
    else
        if(z==z->parent->left)
            z->parent->left=y;
        else
            z->parent->right=y;
    y->parent=z->parent;
    y->left=z;
    z->parent=y;
}

template<class T> void RB_Tree<T>::rb_tree_insert(RB_Node<T>* z)
{
    RB_Node<T>* x=rb_root;
    RB_Node<T>* y=nil;
    while(x!=nil)
    {
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    if(y==nil)
        rb_root=z;
    else
    if(z->key<y->key)
        y->left=z;
    else
        y->right=z;
    z->parent=y;
    z->left=nil;
    z->right=nil;
    z->color=red;
    rb_tree_insert_fixup(z);
}

template<class T> void RB_Tree<T>::rb_tree_insert_fixup(RB_Node<T>* z)
{
    while(z->parent->color==red)
    {
        if(z->parent==z->parent->parent->left)
        {
            RB_Node<T>* y=z->parent->parent->right;
            if(y->color==red)
            {
                z->parent->color=black;
                y->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)
                {
                    z=z->parent;
                    left_rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                right_rotate(z->parent->parent);
            }
        }
        else
        {
            RB_Node<T>* y=z->parent->parent->left;
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
                    right_rotate(z);
                }
                z->parent->parent->color=red;
                z->parent->color=black;
                left_rotate(z->parent->parent);
            }
        }
    }
    rb_root->color=black;
}

template<class T> void RB_Tree<T>::rb_tree_transplant(RB_Node<T>* u,RB_Node<T>* v)
{
    if(u->parent==nil)
        rb_root=v;
    else
        if(u==u->parent->left)
            u->parent->left=v;
        else
            u->parent->right=v;
    v->parent=u->parent;
}

template<class T> void RB_Tree<T>::rb_tree_delete(RB_Node<T>* z)
{
    RB_Node<T>* y=z;
    RB_Node<T>* x=0;
    r_or_b y_original_color=y->color;
    if(z->left==nil)
    {
        x=z->right;
        rb_tree_transplant(z,z->right);
    }
    else{
        if(z->right==nil)
        {
            x=z->left;
            rb_tree_transplant(z,z->left);
        }
        else
        {
            y=rb_tree_minimum(z->right);
            y_original_color=y->color;
            x=y->right;
            if(y->parent==z)
                x->parent=y;
            else
            {
                rb_tree_transplant(y,y->right);
                y->right=z->right;
                y->right->parent=y;
            }
            rb_tree_transplant(z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }}
    if(y_original_color==black)
        rb_tree_delete_fixup(x);
}

template<class T> void RB_Tree<T>::rb_tree_delete_fixup(RB_Node<T>* x)
{
   RB_Node<T>* w=0;
    while(x!=rb_root&&x->color==black)
    {
        if(x==x->parent->left)
        {
            w=x->parent->right;
            if(w->color==red)
            {
                w->color=black;
                x->parent->color=red;
                left_rotate(x->parent);
                w=x->parent->right;
            }
            if(w->left->color==black&&w->right->color==black)
            {
                w->color=red;
                x=x->parent;
            }
            else
            {
                if(w->right->color==black)
                {
                    w->left->color=black;
                    w->color=red;
                    right_rotate(w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color=black;
                w->right->color=black;
                left_rotate(x->parent);
                x=rb_root;
            }
        }
        else
        {
            w=x->parent->left;
            if(w->color==red)
            {
                w->color=black;
                x->parent->color=red;
                right_rotate(x->parent);
                w=x->parent->left;
            }
            if(w->right->color==black&&w->left->color==black)
            {
                w->color=red;
                x=x->parent;
            }
            else
            {
                if(w->left->color==black)
                {
                    w->color=red;
                    w->right->color=black;
                    left_rotate(w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color=black;
                w->left->color=black;
                right_rotate(x->parent);
                x=rb_root;
            }
        }
    }
    x->color=black;
}
