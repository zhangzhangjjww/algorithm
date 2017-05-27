#include<iostream>
#include"list2.h"


int main()
{
    List2<int> l;
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);
    l.display();
    std::cout<<std::endl;
    l.delete1(l.search(n2));
    l.display();
    return 0;
}
