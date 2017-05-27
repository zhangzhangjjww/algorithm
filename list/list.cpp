#include<iostream>
#include"List.h"


int main()
{
    List<int> l;
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
