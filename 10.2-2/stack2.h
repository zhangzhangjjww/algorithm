#ifndef STACK2_H_INCLUDED
#define STACK2_H_INCLUDED
#include<iostream>

template<class T> struct Node
{
    Node* next;
    T key;
    Node(T n=0):next(0),key(n) {};
};

template<class T> struct singlelist
{
    Node<T>* head;
    singlelist():head(0) {}
    bool empty()
    {
        if(head==0)
            return true;
        else
            return false;
    }
    void insert(Node<T>& x)
    {
        if(head==0)
        {
            head=&x;
        }
        else
        {
            x.next=head;
            head=&x;
        }
    }
    Node<T>& search(const Node<T>& x)
    {
        Node<T>* tmp=head;
        while(tmp!=0&&tmp->key!=x.key)
        {
            tmp=tmp->next;
        }
        return *tmp;
    }
    void delete1(Node<T>& x)
    {
        Node<T>* tmp=head;
        if(tmp==&x)
        {
            head=head->next;
            return;
        }
        while(tmp->next!=&x)
            tmp=tmp->next;
        tmp->next=tmp->next->next;
    }
    void display()
    {
        Node<T>* tmp=head;
        while(tmp!=0)
        {
            std::cout<<tmp->key<<std::endl;
            tmp=tmp->next;
        }
    }
};


template<class T> class stack2
{
private:
    singlelist<T> s;
public:
    bool empty() {return s.empty();}
    void push(T x)
    {
        Node<T>* p=new Node<T>(x);
        s.insert(*p);
    }
    T pop()
    {
        T tmp=s.head->key;
        Node<T>* p=s.head;
        s.delete1(*s.head);
        delete p;
        return tmp;
    }
    void display()
    {
        s.display();
    }
};
#endif // STACK2_H_INCLUDED
