#ifndef QUEUE2_H_INCLUDED
#define QUEUE2_H_INCLUDED

#include"Stack.h"
//#include"Stack.cpp"

template<class T>
class Queue2
{
private:
    int sz;
    Stack<T> s1;
    Stack<T> s2;
public:
    Queue2(int n):s1(n),s2(n) {}
    ~Queue2() {}
    bool empty()
    {
        if(s1.empty()&&s2.empty())
            return true;
        else
            return false;
    }
    void enqueue2(T x)
    {
        while(!s2.empty())
        {
            s1.push(s2.pop());
        }
        s1.push(x);
    }
    T dequeue2()
    {
        while(!s1.empty())
            s2.push(s1.pop());
        return s2.pop();
    }
    void display()
    {
        if(s2.empty())
            s1.display1();
        else
            s2.display2();
    }
};


#endif // QUEUE2_H_INCLUDED
