#ifndef STACK2_H_INCLUDED
#define STACK2_H_INCLUDED

#include"queue.h"

template<class T>
class stack2
{
private:
    int sz;
    Queue<T> q1;
    Queue<T> q2;
public:
    stack2(int n):sz(n),q1(n),q2(n) {}
    ~stack2()  {};
    bool empty()
    {
        if(q1.empty()&&q2.empty())
            return true;
        else
            return false;
    }
    void push(T x)
    {
        if(q1.empty())
        {
            q1.enqueue(x);
            while(!q2.empty())
                q1.enqueue(q2.dequeue());
        }
        else
        {
            q2.enqueue(x);
            while(!q1.empty())
                q2.enqueue(q1.dequeue());
        }
    }
    T pop()
    {
        if(q1.empty())
            return q2.dequeue();
        else
            return q1.dequeue();
    }
    void display()
    {
        if(q1.empty())
            q2.display2();
        else
            q1.display2();
    }
};

#endif // STACK2_H_INCLUDED
