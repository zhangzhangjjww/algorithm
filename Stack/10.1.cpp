#include<iostream>
#include"Stack.h"
#include"Stack.cpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    const int N=10;
    Stack<int> s(N);
    s.push(4);
    s.push(1);
    s.push(3);
    s.display();
    cout<<s.pop()<<endl;
    s.push(8);
    cout<<s.pop()<<endl;
    if(!s.empty())
        cout<<s.search(1)<<" "<<s.search(10)<<endl;
    return 0;
}


