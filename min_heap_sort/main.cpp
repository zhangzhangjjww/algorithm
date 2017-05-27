#include<iostream>
#include"min_sort.h"

using std::cout;
using std::endl;

int main()
{
    int a[]={5,13,2,25,7,17,20,8,4};
    const int N=9;
    //build_max_heap(a,N);
    heap_sort(a,N);
    for(size_t i=0;i!=N;++i)
        cout<<a[i]<<endl;
    return 0;
}
