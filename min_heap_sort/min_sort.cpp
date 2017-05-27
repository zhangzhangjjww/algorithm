#include"min_sort.h"

int parent(int i)
{
    if(i==1)
        return 0;
    else
        return (i+1)/2.0-1.5;
}
int left(int i)
{
    return 2*(i+1)-1;
}
int right(int i)
{
    return 2*(i+1);
}

void min_heapify(int* a,int sz,int i)
{
    int minist;
    int l=left(i);
    int r=right(i);
    if(l<sz&&a[l]<a[i])
        minist=l;
    else
        minist=i;
    if(r<sz&&a[r]<a[minist])
        minist=r;
    if(minist!=i)
    {
        int tmp=a[i];
        a[i]=a[minist];
        a[minist]=tmp;
        min_heapify(a,sz,minist);
    }
}

void build_min_heap(int* a,int n)
{
    for(int i=n/2-1.5;i!=-1;--i)
        min_heapify(a,n,i);
}

void heap_sort(int*a,int n)
{
    build_min_heap(a,n);
    int sz=n;
    for(int i=n-1;i!=0;--i)
    {
        int tmp=a[0];
        a[0]=a[i];
        a[i]=tmp;
        --sz;
        min_heapify(a,sz,0);
    }
}
