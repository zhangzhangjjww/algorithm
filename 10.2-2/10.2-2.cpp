#include<iostream>
#include"stack2.h"

int main()
{
    /*singlelist<int> s;
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    s.insert(n1);
    s.insert(n2);
    s.insert(n3);
    s.display();
    s.delete1(s.search(n2));
    s.display();*/
    stack2<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.display();
    std::cout<<std::endl;
    std::cout<<s.pop()<<std::endl;
    s.push(4);
    s.display();
    return 0;
}
