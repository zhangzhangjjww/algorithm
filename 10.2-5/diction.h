#ifndef DICTION_H_INCLUDED
#define DICTION_H_INCLUDED

#include<iostream>
#include<string>

template<class T> class diction
{
private:
    std::string table;
    T content;
public:
    diction(std::string s="",T c=0):table(s),content(c) {}
    ~diction() {}
    T& second() {return content;}
    std::string& first() {return table;}
    bool operator==(const diction& d)
    {
        if(table==d.table)
            return true;
        else
            return false;
    }
    bool operator!=(const diction& d)
    {
        if(table!=d.table)
            return true;
        else
            return false;
    }
    friend std::istream& operator>>(std::istream& is,diction<T>& d)
    {
        std::cout<<"Enter the table:";
        is>>d.table;
        std::cout<<"Enter the content:";
        is>>d.content;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os,diction<T>& d)
    {
        os<<"table: "<<d.table<<'\t'<<"content: "<<d.content;
        return os;
    }
};

template<class T> struct Node
{
    Node* next;
    diction<T> key;
    Node(diction<T> n):next(0),key(n) {}
    Node():next(0),key() {}
    Node(std::string& s):next(0),key(s,0) {}
};

template<class T> struct singlelist
{
    Node<T>* nil;
    singlelist():nil(0) {nil=&nil1;nil->next=nil;}
    bool empty()
    {
        if(nil->next==nil)
            return true;
        else
            return false;
    }
    void insert(Node<T>& x)
    {
        if(empty())
        {
            nil->next=&x;
            x.next=nil;
        }
        else
        {
            x.next=nil->next;
            nil->next=&x;
        }
    }
    void delete1(Node<T>& x)
    {
        if(nil==&x)
            return;
        Node<T>* tmp=nil->next;
        while(tmp->next!=&x)
            tmp=tmp->next;
        tmp->next=x.next;
        Node<T>* p=&x;
        delete p;
    }
    Node<T>& search(Node<T>& x)
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil&&x.key!=tmp->key)
            tmp=tmp->next;
        return *tmp;
    }
    Node<T>& search1(std::string s)
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil&&s!=tmp->key.first())
            tmp=tmp->next;
        return *tmp;
    }
    T& operator[](std::string s)
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil&&s!=tmp->key.first())
            tmp=tmp->next;
        if(tmp==nil)
        {
            Node<T>* p=new Node<T>(s);
            insert(*p);
            return p->key.second();
        }
        else
        {
            return tmp->key.second();
        }
    }
    void display()
    {
        Node<T>* tmp=nil->next;
        while(tmp!=nil)
        {
            std::cout<<tmp->key<<std::endl;
            tmp=tmp->next;
        }
    }
    //T&
private:
    Node<T> nil1;
};

#endif // DICTION_H_INCLUDED
