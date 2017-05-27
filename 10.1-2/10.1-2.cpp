#include<iostream>
#include"two_stack.h"
#include"two_stack.cpp"

using std::cout;
using std::endl;

int main()
{
    const int N=10;
    two_stack<int> ts(N);
    ts.push1(2);
    ts.push1(3);
    ts.push1(4);
    ts.push2(8);
    ts.push2(22);
    ts.display1();
    ts.display2();
    cout<<ts.pop1()<<" "<<ts.pop2()<<endl;
    cout<<ts.search1(2)<<" "<<ts.search2(22)<<endl;
    return 0;
}
