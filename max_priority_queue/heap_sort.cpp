#include"heap_sort.h"
#include<iostream>

void max_heapify(Pointer &a,int sz,int i)
{
    int l=left(i);
    int r=right(i);
    int largest;
    if(l<sz&&a[l]>a[i])
        largest=l;
    else
        largest=i;
    if(r<sz&&a[r]>a[largest])
        largest=r;
    if(largest!=i)
    {
        int tmp=a[largest];
        a[largest]=a[i];
        a[i]=tmp;
        max_heapify(a,sz,largest);
    }
}

void build_max_heap(Pointer &a)
{
    int i=a.vol()/2.0-1.5;
    for(;i!=-1;--i)
        max_heapify(a,a.vol(),i);
}

void heap_sort(Pointer &a)
{
    build_max_heap(a);
    int sz=a.vol();
    for(int i=a.vol()-1;i!=0;--i)
    {
        int tmp=a[i];
        a[i]=a[0];
        a[0]=tmp;
        --sz;
        max_heapify(a,sz,0);
    }

}

int parent(int i)
{
    if(i==1)
        return 0;
    else
        return (i)/2.0-0.5;
}
int left(int i)
{
    return 2*(i+1)-1;
}
int right(int i)
{
    return 2*(i+1);
}
