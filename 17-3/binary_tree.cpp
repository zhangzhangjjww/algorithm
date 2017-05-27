#include<iostream>
#include"binary_tree.h"
#include<queue>

using std::queue;

template<class T> Node<T>* Binary_Tree<T>::allocate_node()
{
    Node<T>* x=new Node<T>();
    return x;
}

template<class T> void Binary_Tree<T>::recursive_clear(Node<T>* x)
{
    if(x->left!=0)
    {
        recursive_clear(x->left);
    }
    if(x->right!=0)
        recursive_clear(x->right);
    delete x;
}

template<class T> Binary_Tree<T>::Binary_Tree():root(0)
{
    //root=allocate_node();
}

template<class T> Binary_Tree<T>::~Binary_Tree()
{
    recursive_clear(root);
    root=0;
}

template<class T> bool Binary_Tree<T>::isempty()
{
    if(root==0)
        return true;
    else
        return false;
}

template<class T> void Binary_Tree<T>::binary_tree_left_rotate(Node<T>* x)
{
    Node<T>* y=x->right;
    x->right=y->left;
    if(y->left!=0)
        y->left->parent=x;
    y->parent=x->parent;
    if(x==root)
    {
        root=y;
    }
    else
    {
        if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
    y->size=x->size;
    if(x->left==0&&x->right==0)
        x->size=1;
    if(x->right!=0&&x->left==0)
        x->size=x->right->size+1;
    if(x->left!=0&&x->right==0)
        x->size=x->left->size+1;
    if(x->left!=0&&x->right!=0)
        x->size=x->left->size+x->right->size+1;

}

template<class T> void Binary_Tree<T>::binary_tree_right_rotate(Node<T>* x)
{
    Node<T>* y=x->left;
    x->left=y->right;
    if(y->right!=0)
        y->right->parent=x;
    y->parent=x->parent;
    if(x==root)
    {
        root=y;
        y->parent=0;
    }
    else
    {
        if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
    }
    y->right=x;
    x->parent=y;
    y->size=x->size;
    if(x->left==0&&x->right==0)
        x->size=1;
    if(x->right!=0&&x->left==0)
        x->size=x->right->size+1;
    if(x->left!=0&&x->right==0)
        x->size=x->left->size+1;
    if(x->left!=0&&x->right!=0)
        x->size=x->left->size+x->right->size+1;
}

template<class T> Node<T>* Binary_Tree<T>::binary_tree_search(Node<T>* x,Data<T> d)
{
    if(x==0)
        return 0;
    else
    {
        if(x->data.key==d.key)
            return x;
        else
            if(d.key<x->data.key)
               return binary_tree_search(x->left,d);
        else
            return binary_tree_search(x->right,d);
    }
}

template<class T> void Binary_Tree<T>::binary_tree_insert(Data<T> d)
{
    Node<T>* x=allocate_node();
    x->data.key=d.key;
    x->data.value=d.value;
    if(isempty())
    {
        root=x;
        return;
    }
    Node<T>* y=root;Node<T>* z=0;
    while(y!=0)
    {
        z=y;
        ++z->size;
        if(x->data.key<=y->data.key)
            y=y->left;
        else
            y=y->right;
    }
    if(x->data.key<=z->data.key)
        z->left=x;
    else
        z->right=x;
    x->parent=z;
    binary_tree_insert_fixup(z);
}

template<class T> void Binary_Tree<T>::binary_tree_insert2(Node<T>* x,Node<T>* y)
{
   Node<T>* z=0;
   while(x!=0)
   {
       z=x;
       //std::cout<<x->data.key<<std::endl;
       ++z->size;
       if(y->data.key<=x->data.key)
           x=x->left;
       else
           x=x->right;
   }
   if(y->data.key<=z->data.key)
       z->left=y;
   else
       z->right=y;
   y->parent=z;
   fix(y);
}

template<class T> void Binary_Tree<T>::binary_tree_transplant(Node<T>* x,Node<T>* y)
{
    if(x->parent==0)
        root=y;
    else
        if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
    if(y!=0)
        y->parent=x->parent;
}

template<class T> void Binary_Tree<T>::fix(Node<T>* x)
{
    if(x->left==0&&x->right==0)
        x->size=1;
    if(x->right!=0&&x->left==0)
        x->size=x->right->size+1;
    if(x->left!=0&&x->right==0)
        x->size=x->left->size+1;
    if(x->left!=0&&x->right!=0)
        x->size=x->left->size+x->right->size+1;
}

template<class T> void Binary_Tree<T>::binary_tree_insert_fixup(Node<T>* x)
{
    Node<T>* ttt=x;
    if(x==0)
        return;
    int xsize=x->size*alfa;
    //std::cout<<x->size<<" "<<xsize<<std::endl;
    //std::cout<<x->parent->size<<" "<<xsize<<std::endl;
    if((x->left==0&&x->right!=0&&x->right->size<=xsize)||(x->right==0&&x->left!=0&&x->left->size<=xsize)||(x->left&&x->right&&x->left->size<=xsize&&x->right->size<=xsize))
           return binary_tree_insert_fixup(x->parent);
    if(x->left!=0&&x->left->size>xsize)
    {
        if(x->right==0)
        {
            Node<T>* y=x->left;
            if(x->left->left==0)
            {
                binary_tree_left_rotate(y);
                y=x->left;
            }
            binary_tree_right_rotate(x);
            return binary_tree_insert_fixup(y->parent);
        }
        else
        {
            Node<T>* y=x->left;
            Node<T>* z=binary_tree_maximum(y);
            Node<T>* tmp=z->parent;
            while(tmp!=0)
            {
                --tmp->size;
                tmp=tmp->parent;
            }
            binary_tree_transplant(z,z->right);
            binary_tree_transplant(x,z);
            z->right=x->right;
            z->right->parent=z;
            z->left=x->left;
            z->left->parent=z;
            fix(z);
            x->parent=0;x->left=0;x->right=0;
            binary_tree_insert2(z,x);
            tmp=z->parent;
            while(tmp!=0)
            {
                ++tmp->size;
                tmp=tmp->parent;
            }
            binary_tree_insert_fixup(ttt);
            binary_tree_insert_fixup(z->right);
            return binary_tree_insert_fixup(z->parent);
        }
    }
    else
        if(x->right!=0&&x->right->size>xsize)
    {
        if(x->left==0)
        {
            Node<T>* y=x->right;
            if(y->right==0)
            {
                binary_tree_right_rotate(y);
                y=x->right;
            }
            binary_tree_left_rotate(x);
            return binary_tree_insert_fixup(y->parent);
        }
        else
        {
            Node<T>* y=x->right;
            Node<T>* z=binary_tree_minimum(y);
            //std::cout<<z->data.key<<std::endl;
            Node<T>* tmp=z->parent;
            while(tmp!=0)
            {
                --tmp->size;
                tmp=tmp->parent;
            }
            binary_tree_transplant(z,z->right);
            binary_tree_transplant(x,z);
            z->left=x->left;
            z->left->parent=z;
            z->right=x->right;
            z->right->parent=z;
            fix(z);
            x->parent=0;x->left=0;x->right=0;
            binary_tree_insert2(z,x);
            tmp=z->parent;
            while(tmp!=0)
            {
                ++tmp->size;
                tmp=tmp->parent;
            }
            binary_tree_insert_fixup(ttt);
            binary_tree_insert_fixup(z->left);
            return binary_tree_insert_fixup(z->parent);
        }
    }
}

template<class T> void Binary_Tree<T>::binary_tree_delete(Data<T> d)
{
    Node<T>* x=binary_tree_search(root,d);
    if(x->left==0)
    {
        binary_tree_transplant(x,x->right);
        return;
    }
    else
        if(x->right==0)
        {
            binary_tree_transplant(x,x->left);
            return;
        }
        else
        {
            Node<T>* y=binary_tree_successor(x);
            if(y->parent!=x)
            {
                binary_tree_transplant(y,y->right);
                y->right=x->right;
                y->right->parent=y;
            }
            binary_tree_transplant(x,y);
            y->left=x->left;
            y->left->parent=y;
            return;
        }
}

template<class T> Node<T>* Binary_Tree<T>::binary_tree_maximum(Node<T>* x)
{
    while(x->right!=0)
        x=x->right;
    return x;
}

template<class T> Node<T>* Binary_Tree<T>::binary_tree_minimum(Node<T>* x)
{
    while(x->left!=0)
        x=x->left;
    return x;
}

template<class T> Node<T>* Binary_Tree<T>::binary_tree_predecessor(Node<T>* x)
{
    if(x->left!=0)
        return binary_tree_maximum(x->left);
    else
    {
        Node<T>* y=x->parent;
        while(y!=0&&x!=y->left)
        {
            x=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> Node<T>* Binary_Tree<T>::binary_tree_successor(Node<T>* x)
{
    if(x->right!=0)
        return binary_tree_minimum(x->right);
    else
    {
        Node<T>* y=x->parent;
        while(y!=0&&x!=y->right)
        {
            x=y;
            y=y->parent;
        }
        return y;
    }
}

template<class T> void Binary_Tree<T>::binary_tree_walk_in_order(Node<T>* x)
{
    if(x->left!=0)
        binary_tree_walk_in_order(x->left);
    std::cout<<x->size<<" "<<x->data.key<<" "<<x->data.value<<std::endl;
    if(x->right!=0)
        binary_tree_walk_in_order(x->right);
}

template<class T> void Binary_Tree<T>::binary_tree_walk_in_order2(Node<T>* x)
{
    queue<Node<T>*> myqueue;
    int depth=0;
    myqueue.push(x);
    while(!myqueue.empty())
    {
        queue<Node<T>*> nextlevel;
        std::cout<<"depth"<<depth<<std::endl;
        while(!myqueue.empty())
        {
            Node<T>* y=myqueue.front();
            myqueue.pop();
            std::cout<<y->size<<" "<<y->data.key<<" "<<y->data.value<<"||";
            if(y->parent!=0)
                std::cout<<y->parent->data.key<<"|";
            if(y->left!=0)
                nextlevel.push(y->left);
            if(y->right!=0)
                nextlevel.push(y->right);
        }
        std::cout<<std::endl;
        myqueue=nextlevel;
        ++depth;
    }
}
