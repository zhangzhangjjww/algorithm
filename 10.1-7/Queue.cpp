#include"queue.h"
#include<iostream>
#include<stdexcept>

template<class T> Queue<T>::Queue(int n):p(0),sz(n),head(0),tail(0)
{
    p=new T[n];
    for(int i=0;i!=n-1;++i)
        p[i]=0;
}

template<class T> Queue<T>::~Queue()
{
    delete [] p;
}

template<class T> bool Queue<T>::empty()
{
    if(head==tail)
        return true;
    else
        return false;
}

template<class T> void Queue<T>::enqueue(T x)
{
    if(head==0&&tail==sz-2)
        std::overflow_error("out of range");
    if(tail+1==head)
        std::overflow_error("out of range");
    else
    {
        p[tail]=x;
        if(tail==sz-1)
            tail=0;
        else
            tail++;
    }
}

template<class T> T Queue<T>::dequeue()
{
    if(empty())
        std::overflow_error("out of range");
    else
    {
        T tmp=p[head];
        if(head==sz-1)
            head=0;
        else
            ++head;
        return tmp;
    }
}

template<class T> void Queue<T>::display()
{
    for(int i=head;i!=tail;)
    {
        std::cout<<p[i]<<std::endl;
        if(i==sz-1)
            i=0;
        else
            ++i;
    }
}


template<class T> void Queue<T>::display2()
{
    int tmp,tmp2;
    if(tail==0)
        tmp=sz-1;
    else
        tmp=tail-1;
    if(head==0)
        tmp2=sz-1;
    else
        tmp2=head-1;
    for(int i=tmp;i!=tmp2;)
    {
        std::cout<<p[i]<<std::endl;
        if(i==0)
            i=sz-1;
        else
            --i;
    }
}

template<class T> int Queue<T>::search(T k)
{
    int i;
    for(i=head;i!=tail;)
    {
        if(p[i]==k)
            return i;
        else
        {
            if(i==sz-1)
                i=0;
            else
                ++i;
        }
    }
    if(i==tail)
        return -1;
}
