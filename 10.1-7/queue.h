#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<class T> //数组为n，存放元素数为n-1
class Queue
{
private:
    T* p;
    int head;
    int tail;
    int sz;
public:
    Queue(int n);
    ~Queue();
    bool empty();
    void enqueue(T x);
    T dequeue();
    int search(T k);
    void display();
    void display2();
};

#endif // QUEUE_H_INCLUDED
