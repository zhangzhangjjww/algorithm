#include"max_pri_queue.h"
#include"heap_sort.h"
#include<stdexcept>
#include<iostream>
int heap_maximum(Pointer& a)
{
    return a[0];
}

int heap_extract_max(Pointer& a)
{
    if(a.vol()<1)
        std::overflow_error("out of range");
    int max=a[0];
    a.desz();
    max_heapify(a,a.vol(),0);
    return max;
}
void heap_increase_key(Pointer& a,int i,int key)
{
    if(key<a[i])
        std::overflow_error("out of range");
    a[i]=key;
    while(i>0&&a[parent(i)]<a[i])
    {
        int tmp=a[i];
        a[i]=a[parent(i)];
        a[parent(i)]=tmp;
        i=parent(i);
    }
}
void max_heap_insert(Pointer& a,int key)
{
    a.addsz();
    heap_increase_key(a,a.vol()-1,key);
}

void heap_delete(Pointer& a,int i)
{
    int key=a[i];
    a.dele(i);
    if(a[i]==key)
        return;
    if(a[i]<key)
        max_heapify(a,a.vol(),i);
    if(a[i]>key)
        heap_increase_key(a,i,a[i]);

}
