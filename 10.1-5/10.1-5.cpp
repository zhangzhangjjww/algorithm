#include<iostream>
#include"Deque.h"
#include"Deque.cpp"

using std::cout;
using std::endl;

int main()
{
    const int N=10;
    Deque<int> de(N);
    de.endeque_front(4);
    de.endeque_front(5);de.endeque_front(6);
    de.endeque_end(1);
    de.endeque_end(2);
    de.endeque_end(3);
    de.display();
    cout<<de.dedeque_front()<<" "<<de.dedeque_end()<<endl;
    return 0;
}
