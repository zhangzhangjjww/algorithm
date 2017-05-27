#include<iostream>
#include"interval_tree.h"

int maximum(int a1,int a2,int a3);
int maximum(int a1,int a2);


template<class T> void Interval_Tree<T>::Interval_Tree_left_rotate(Interval_Node<T>* z)
{
    Interval_Node<T>* y=z->right;
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
    y->max=z->max;
    z->max=maximum(z->left->max,z->key.high,z->right->max);
}

template<class T> void Interval_Tree<T>::Interval_Tree_right_rotate(Interval_Node<T>* z)
{
    Interval_Node<T>* y=z->left;
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
    y->max=z->max;
    z->max=maximum(z->left->max,z->key.high,z->right->max);
}

template<class T> void Interval_Tree<T>::Interval_Tree_set_nil()
{
    nil->parent=nil;
    nil->left=nil;
    nil->right=nil;
    nil->color=black;
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_search(Interval_Node<T>* z,interval k)
{
    if(z==nil)
    {
        std::cout<<"NO exist!"<<std::endl;
        return nil;
    }
    if(z->key==k)
        return z;
    else
        if(k.low<z->key.low)
            return Interval_Tree_search(z->left,k);
        else
            return Interval_Tree_search(z->right,k);
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_maximum(Interval_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->right!=nil)
        z=z->right;
    return z;
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_minimum(Interval_Node<T>* z)
{
    if(z==nil)
        return nil;
    while(z->left!=nil)
        z=z->left;
    return z;
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_successor(Interval_Node<T>* z)
{
    if(z->right!=nil)
        return Interval_Tree_minimum(z->right);
    else
    {
        Interval_Node<T>* y=z->parent;
        while(y!=nil&&z==y->right)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_predecessor(Interval_Node<T>* z)
{
    if(z->left!=nil)
        return Interval_Tree_maximum(z->left);
    else
    {
        Interval_Node<T>* y=z->parent;
        while(y!=nil&&z==y->left)
        {
            z=y;
            y=y->parent;
        }
        return y;
    }
}
template<class T> void Interval_Tree<T>::Interval_Tree_walk_in_order(Interval_Node<T>* z)
{
    if(z->left!=nil)
        Interval_Tree_walk_in_order(z->left);
    std::cout<<z->key.low<<" "<<z->key.high<<" "<<z->max<<" "<<z->color<<" "<<z->data<<" "<<std::endl;
    if(z->right!=nil)
        Interval_Tree_walk_in_order(z->right);
}

template<class T> void Interval_Tree<T>::Interval_Tree_insert(Interval_Node<T>* z)
{
    z->max=z->key.high;
    Interval_Node<T>* y=nil;
    Interval_Node<T>* x=root;
    while(x!=nil)
    {
        y=x;
        y->max=maximum(y->max,z->key.high);
        if(z->key.low<x->key.low)
            x=x->left;
        else
            x=x->right;
    }
    if(y==nil)
        root=z;
    else
    if(z->key.low<y->key.low)
        y->left=z;
    else
        y->right=z;
    z->parent=y;
    z->left=nil;
    z->right=nil;
    z->color=red;
    Interval_Tree_insert_fixup(z);
}

template<class T> void Interval_Tree<T>::Interval_Tree_insert_fixup(Interval_Node<T>* z)
{
    while(z->parent->color==red)
    {
        if(z->parent==z->parent->parent->left)
        {
            Interval_Node<T>* y=z->parent->parent->right;
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
                    Interval_Tree_left_rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                Interval_Tree_right_rotate(z->parent->parent);
            }
        }
        else
        {
            Interval_Node<T>* y=z->parent->parent->left;
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
                    Interval_Tree_right_rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                Interval_Tree_left_rotate(z->parent->parent);
            }
        }
    }
    root->color=black;
}

template<class T> void Interval_Tree<T>::Interval_Tree_transplant(Interval_Node<T>* u,Interval_Node<T>* v)
{
   if(u==u->parent->left)
        u->parent->left=v;
   else
        u->parent->right=v;
   v->parent=u->parent;
}

template<class T> void Interval_Tree<T>::Interval_Tree_delete(Interval_Node<T>* z)
{
    Interval_Node<T>* y=z;
    Interval_Node<T>* x=0;
    r_or_b y_original_color=y->color;
    if(z->left==nil)
    {
        x=z->right;
        Interval_Tree_transplant(z,z->right);
    }
    else
    {
        if(z->right==nil)
        {
            x=z->left;
            Interval_Tree_transplant(z,z->left);
        }
        else
        {
            y=Interval_Tree_minimum(z->right);
            y_original_color=y->color;
            x=y->right;
            if(z==y->parent)
                x->parent=y;
            else
            {
                Interval_Tree_transplant(y,x);
                y->right=z->right;
                y->right->parent=y->right;
                y->max=z->max;
            }
            Interval_Tree_transplant(z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }
    }
    Interval_Tree_delete_max_fixup(x);
    if(y_original_color==black)
        Interval_Tree_delete_fixup(x);
}

template<class T> void Interval_Tree<T>::Interval_Tree_delete_max_fixup(Interval_Node<T>* z)
{
    Interval_Node<T>* y=z->parent;
    while(y!=nil)
    {
        y->max=maximum(y->left->max,y->right->max,y->key.high);
        y=y->parent;
    }
}

template<class T> void Interval_Tree<T>::Interval_Tree_delete_fixup(Interval_Node<T>* x)
{
    while(x!=root&&x->color==black)
    {
        Interval_Node<T>* w=0;
        if(x==x->parent->left)
        {
            w=x->parent->right;
            if(w->color==red)
            {
                w->color=black;
                x->parent->color=red;
                Interval_Tree_left_rotate(x->parent);
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
                        Interval_Tree_right_rotate(w);
                        w=x->parent->right;
                    }
                    w->color=x->parent->color;
                    x->parent->color=black;
                    w->right->color=black;
                    Interval_Tree_left_rotate(x->parent);
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
               Interval_Tree_right_rotate(x->parent);
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
                       Interval_Tree_left_rotate(w);
                       w=x->parent->left;
                   }
                   w->color=x->parent->color;
                   x->parent->color=black;
                   w->left->color=black;
                   Interval_Tree_right_rotate(x->parent);
                   x=root;
               }
           }
        }
    }
    x->color=black;
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_overlaps(interval& i)
{
    Interval_Node<T>* x=root;
    while(x!=nil&&(i.low>x->key.high||i.high<x->key.low))
    {
        if(x->left!=nil&&x->left->max>=i.low)
            x=x->left;
        else
            x=x->right;
    }
    return x;
}

template<class T> Interval_Node<T>* Interval_Tree<T>::Interval_Tree_min_overlaps(Interval_Node<T>* x,interval& i)
{
    Interval_Node<T>* y=0;
    if(x->left!=nil&&x->left->max>=i.low)
    {
        y=Interval_Tree_min_overlaps(x->left,i);
        if(y!=nil)
            return y;
        else
        {
            if(!(x->key.low>i.high||x->key.high<i.low))
                return x;
            else
                return nil;
        }
    }
    else
    {
        if(!(x->key.low>i.high||x->key.high<i.low))
            return x;
        else
            return Interval_Tree_min_overlaps(x->right,i);
    }
}

template<class T> void Interval_Tree<T>::Interval_Tree_all_overlaps(Interval_Node<T>* x,interval& i)
{
    if(!(x->key.low>i.high||x->key.high<i.low))
        std::cout<<x->key.low<<" "<<x->key.high<<" "<<x->max<<" "<<x->color<<" "<<x->data<<std::endl;
    if(x->left!=nil&&x->max>=i.low)
        Interval_Tree_all_overlaps(x->left,i);
    if(x->right!=nil&&x->key.low<=i.high)
        Interval_Tree_all_overlaps(x->right,i);
}
