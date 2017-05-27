#ifndef INTREVAL_TREE_H_INCLUDED
#define INTREVAL_TREE_H_INCLUDED

enum r_or_b {red,black};

struct interval
{
    int low;
    int high;
    interval(int l,int h):low(l),high(h) {}
};

template<class T> struct Interval_Node
{
   T data;
   int max;
   interval key;
   r_or_b color;
   Interval_Node* parent;
   Interval_Node* left;
   Interval_Node* right;
   Interval_Node(T d=0,int l=0,int h=0): data(d),key(l,h),color(red),max(h),parent(0),right(0),left(0) {}
};

template<class T> class Interval_Tree
{
   private:
       Interval_Node<T>* nil;
       Interval_Node<T> nil_value;
       void Interval_Tree_set_nil();
       void Interval_Tree_right_rotate(Interval_Node<T>* z);
       void Interval_Tree_left_rotate(Interval_Node<T>* z);
       void Interval_Tree_insert_fixup(Interval_Node<T>* z);
       void Interval_Tree_delete_fixup(Interval_Node<T>* z);
       void Interval_Tree_transplant(Interval_Node<T>* u,Interval_Node<T>* v);
       void Interval_Tree_delete_max_fixup(Interval_Node<T>* z);
   public:
       Interval_Node<T>* root;
       Interval_Tree():root(0),nil(0),nil_value(0,0,0) {nil=&nil_value;Interval_Tree_set_nil();root=nil;}
       ~Interval_Tree() {}
       Interval_Node<T>* Interval_Tree_search(Interval_Node<T>* z,interval k);
       Interval_Node<T>* Interval_Tree_maximum(Interval_Node<T>* z);
       Interval_Node<T>* Interval_Tree_minimum(Interval_Node<T>* z);
       Interval_Node<T>* Interval_Tree_successor(Interval_Node<T>* z);
       Interval_Node<T>* Interval_Tree_predecessor(Interval_Node<T>* z);
       void Interval_Tree_walk_in_order(Interval_Node<T>* z);
       void Interval_Tree_insert(Interval_Node<T>* z);
       void Interval_Tree_delete(Interval_Node<T>* z);
       Interval_Node<T>* Interval_Tree_overlaps(interval& i);
       Interval_Node<T>* Interval_Tree_min_overlaps(Interval_Node<T>* z,interval& i);
       void Interval_Tree_all_overlaps(Interval_Node<T>* z,interval& i);
};



#endif // INTREVAL_TREE_H_INCLUDED
