#include"Stack.h"
#include<stdexcept>
#include<iostream>

template <class T> Stack<T>::Stack(int n):p(0),sz(n),top(-1)
{
    p=new T[n];
    for(int i=0;i!=n;++i)
        p[i]=0;
}

template<class T> Stack<T>::~Stack()
{
    delete [] p;
}

template<class T> bool Stack<T>::empty()
{
    if(top==-1)
    return true;
    else
        return false;
}

template<class T> void Stack<T>::push(T x)
{
    if(top==sz-1) {
        std::overflow_error("out of range");return;}
    else {
    ++top;
    p[top]=x; }
}

template<class T> T Stack<T>::pop()
{
    if(empty())
        std::overflow_error("out of range");
    else
    {
        --top;
        return p[top+1];
    }
}

template<class T> int Stack<T>::search(T k)
{
    int i;
    for(i=0;i!=top+1;++i)
        if(p[i]==k)
        return i;
    if(i==top+1)
        return -1;
}

template<class T> void Stack<T>::display()
{
    for(int i=0;i!=top+1;++i)
        std::cout<<p[i]<<std::endl;
}
