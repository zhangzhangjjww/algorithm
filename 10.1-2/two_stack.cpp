#include<iostream>
#include<stdexcept>
#include"two_stack.h"

template<class T> two_stack<T>::two_stack(int n):p(0),sz(n),top1(-1),top2(n)
{
    p=new T[n];
}

template<class T> two_stack<T>::~two_stack()
{
    delete [] p;
}

template<class T> bool two_stack<T>::empty1()
{
    if(top1==-1)
        return true;
    else
        return false;
}

template<class T> bool two_stack<T>::empty2()
{
    if(top2==sz)
        return true;
    else
        return false;
}

template<class T> void two_stack<T>::push1(T x)
{
    if(!empty1()&&(top1==top2-2))
        std::overflow_error("out of range");
    else
    {
        ++top1;
        p[top1]=x;
    }
}

template<class T> void two_stack<T>::push2(T x)
{
    if(!empty2()&&(top1==top2-2))
        std::overflow_error("out of range");
    else
    {
        --top2;
        p[top2]=x;
    }
}

template<class T> T two_stack<T>::pop1()
{
    if(empty1())
        std::overflow_error("out of range");
    else
    {
        --top1;
        return p[top1+1];
    }
}

template<class T> T two_stack<T>::pop2()
{
    if(empty2())
        std::overflow_error("out of range");
    else
    {
        ++top2;
        return p[top2-1];
    }
}

template<class T> void two_stack<T>::display1()
{
    if(empty1())
        std::overflow_error("out of range");
    for(int i=0;i!=top1+1;++i)
        std::cout<<p[i]<<std::endl;
}

template<class T> void two_stack<T>::display2()
{
    if(empty2())
        std::overflow_error("out of range");
    for(int i=sz-1;i!=top2-1;--i)
        std::cout<<p[i]<<std::endl;
}

template<class T> int two_stack<T>::search1(T k)
{
    int i;
    for(i=0;i!=top1+1;++i)
        if(p[i]==k)
        return i;
    if(i==top1+1)
        return -1;
}

template<class T> int two_stack<T>::search2(T k)
{
    int i;
    for(i=sz-1;i!=top2-1;--i)
        if(p[i]==k)
        return i;
    if(i==top2-1)
        return sz;
}
