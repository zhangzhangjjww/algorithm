#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

template<class T> class Deque
{
private:
    T* p;
    int head;
    int tail;
    int sz;
public:
    Deque(int n);
    ~Deque();
    bool empty();
    bool full();
    void display();
    void endeque_front(T x);
    void endeque_end(T x);
    T dedeque_front();
    T dedeque_end();
};


#endif // DEQUE_H_INCLUDED
