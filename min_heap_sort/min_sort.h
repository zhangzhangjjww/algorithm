#ifndef MIN_SORT_H_INCLUDED
#define MIN_SORT_H_INCLUDED
int parent(int i);
int left(int i);
int right(int i);
void min_heapify(int* a,int sz,int i);
void build_min_heap(int* a,int n);
void heap_sort(int* a,int n);


#endif // MIN_SORT_H_INCLUDED
