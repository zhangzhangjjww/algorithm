#include"queue.h"
#include"Queue.cpp"
#include<iostream>

using std::cout;
using std::endl;

int main()
{
    const int N=10;
    Queue<int> q(N);
    q.enqueue(4);
    q.enqueue(1);q.enqueue(3);
    q.display();
    cout<<q.dequeue()<<endl;
    q.enqueue(8);
    cout<<q.dequeue()<<endl;
    cout<<q.search(8)<<" "<<q.search(10)<<endl;
    return 0;
}
