#ifndef HEAP_SORT_H_INCLUDED
#define HEAP_SORT_H_INCLUDED
#include"max_pri_queue.h"

int parent(int i);
int left(int i);
int right(int i);
void max_heapify(Pointer &a,int sz,int i);
void build_max_heap(Pointer &a);
void heap_sort(Pointer &a);
#endif // HEAP_SORT_H_INCLUDED
