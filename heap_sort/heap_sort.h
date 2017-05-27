#ifndef HEAP_SORT_H_INCLUDED
#define HEAP_SORT_H_INCLUDED

int parent(int i);
int left(int i);
int right(int i);
void max_heapify(int* a,int n,int i);
void build_max_heap(int* a,int n);
void heap_sort(int* a,int n);
#endif // HEAP_SORT_H_INCLUDED
