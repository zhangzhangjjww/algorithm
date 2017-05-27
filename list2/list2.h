#ifndef LIST2_H_INCLUDED
#define LIST2_H_INCLUDED

#include<iostream>

template<class T> struct Node
{
    Node* prev;
    Node* next;
    T key;
    Node(T n=0):prev(0),next(0),key(n) {}
};

template<class T> struct List2
{
private:
    Node<T> nil1;
public:
    Node<T>* nil;
    List2():nil(0) {nil=&nil1;nil->next=nil;nil->prev=nil;}
    bool empty()
    {
        if(nil->next==0)
            return true;
        else
            return false;
    }
    void insert(Node<T>& x)
    {
        x.prev=nil;
        x.next=nil->next;
        nil->next->prev=&x;
        nil->next=&x;
    }
    Node<T>& search(const Node<T>& x)
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil&&tmp->key!=x.key)
            tmp=tmp->next;
        return *tmp;
    }
    void delete1(Node<T>& x)
    {
        x.prev->next=x.next;
        x.next->prev=x.prev;
    }
    void display()
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil) {
            std::cout<<tmp->key<<std::endl;
            tmp=tmp->next;}
    }
};
#endif // LIST2_H_INCLUDED
