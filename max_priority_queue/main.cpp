#include"heap_sort.h"
#include"max_pri_queue.h"
#include<iostream>
using std::cout;
using std::endl;
int main()
{
    int a[]={45,13,39,5,12,38,37,4,0,6,2,31};
    int const N=12;
    Pointer p(a,N);
   //p.dele(3);
    //heap_sort(p);
   //out<<heap_extract_max(p)<<endl;;
   //max_heap_insert(p,10);
   heap_delete(p,4);
    p.display();
    return 0;
}
