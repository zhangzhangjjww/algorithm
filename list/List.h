#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<iostream>

template<class T> struct Node
{
    Node* prev;
    Node* next;
    T  content;
    Node(T x):prev(0),next(0),content(x) {}
};

template<class T> struct List
{
    Node<T>* head;
    List():head(0) {}
    bool empty()
    {
        if(head==0)
            return true;
        else
            return false;
    }
    void insert(Node<T>& x)
    {
        x.next=head;
        if(head!=0)
            head->prev=&x;
        head=&x;
        x.prev=0;
    }

    Node<T>& search(Node<T>& k)
    {
        Node<T>* x=head;
        while(x!=0&&x->content!=k.content) {
            x=x->next;}
        return *x;
    }

    void delete1(Node<T>& x)
    {
        if(x.prev!=0)
            x.prev->next=x.next;
        else
            head=x.next;
        if(x.next!=0)
            x.next->prev=x.prev;
    }
    void display()
    {
        Node<T>* tmp=head;
        while(tmp!=0)
        {
            std::cout<<tmp->content<<std::endl;
            tmp=tmp->next;
        }
    }
};

#endif // LIST_H_INCLUDED
