#include<iostream>
#include"Queue.cpp"
#include"queue.h"
#include"Stack2.h"

using std::cout;
using std::endl;

int  main()
{
    stack2<int> s(10);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.display();
    cout<<endl;
    cout<<s.pop()<<endl;
    s.display();
    return 0;
}
