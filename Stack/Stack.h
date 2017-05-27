#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <class T>
class Stack
{
private:
    T* p;
    int sz;
    int top;
public:
    Stack(int n);
    ~Stack();
    bool empty();
    void push(T x);
    T pop();
    int search(T k);
    void display();
};

#endif // STACK_H_INCLUDED
