#include"Young_matrix.h"
#include<iostream>

int main()
{
    int a[]={2,3,4,5,6,8,9,12,14};
    Young_matrix y(a,9,4,4);
    int b[9];
    for(int i=0;i!=9;++i)
        b[i]=0;
    Young_sort(y,b,9);
    for(int i=0;i!=9;++i)
        std::cout<<b[i]<<std::endl;
    return 0;
}
