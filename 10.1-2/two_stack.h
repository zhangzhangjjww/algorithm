#ifndef TWO_STACK_H_INCLUDED
#define TWO_STACK_H_INCLUDED

template<class T> class two_stack
{
private:
    int sz;
    T* p;
    int top1;
    int top2;
public:
    two_stack(int n);
    ~two_stack();
    bool empty1();
    bool empty2();
    void push1(T x);
    void push2(T x);
    T pop1();
    T pop2();
    void display1();
    void display2();
    int search1(T k);
    int search2(T k);
};


#endif // TWO_STACK_H_INCLUDED
