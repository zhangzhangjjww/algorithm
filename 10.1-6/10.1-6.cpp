#include<iostream>
#include"Stack.h"
#include"Stack.cpp"
#include"Queue2.h"

using std::cout;
using std::endl;

int main()
{
    const int N=10;
    Queue2<int> q(N);
    q.enqueue2(1);
    q.enqueue2(2);
    q.enqueue2(3);
    q.enqueue2(4);
    q.display();
    cout<<q.dequeue2()<<endl;
    cout<<endl;
    q.display();
    return 0;
}
