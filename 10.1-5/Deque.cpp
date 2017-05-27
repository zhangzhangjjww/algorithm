#include"Deque.h"
#include<iostream>
#include<stdexcept>

template<class T> Deque<T>::Deque(int n):p(0),sz(n),head(0),tail(0)
{
    p=new T[n];
}

template<class T> Deque<T>::~Deque()
{
    delete [] p;
}

template<class T> bool Deque<T>::empty()
{
    if(head==0&&tail==0)
        return true;
    else
        return false;
}

template<class T> bool Deque<T>::full()
{
    if(!empty()&&head==tail)
        return true;
    else
        return false;
}

template<class T> void Deque<T>::display()
{
    int j;
    if(head==sz-1)
        j=0;
    else
        j=head+1;
    for(int i=j;i!=tail;)
    {
        std::cout<<p[i]<<std::endl;
        if(i==sz-1)
            i=0;
        else
            ++i;
    }
}

template<class T> void Deque<T>::endeque_front(T x)
{
    if(full())
        std::overflow_error("out of range");
    else
    {
        if(empty())
        {
            ++tail;
        }
        p[head]=x;
        if(head==0)
            head=sz-1;
        else
            --head;
    }
}

template<class T> void Deque<T>::endeque_end(T x)
{
    if(full())
        std::overflow_error("out of range");
    else
    {
        if(empty())
            head=sz-1;
        p[tail]=x;
        if(tail==sz-1)
            tail=0;
        else
            ++tail;
    }
}

template<class T> T Deque<T>::dedeque_front()
{
    if(empty())
        std::overflow_error("out of range");
    else
    {
        if(head==sz-1)
            head=0;
        else
            ++head;
        return p[head];
    }
}

template<class T> T Deque<T>::dedeque_end()
{
    if(empty())
        std::overflow_error("out of range");
    else
    {
        if(tail==0)
            tail=sz-1;
        else
            --tail;
        return p[tail];
    }
}
