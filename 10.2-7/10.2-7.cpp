#include"singlelist.h"

int main()
{
    singlelist<int> s;
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    s.insert(n1);
    s.insert(n2);
    s.insert(n3);
    s.display();
    s.reverse();
    std::cout<<std::endl;
    s.display();
    return 0;
}
