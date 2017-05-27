#ifndef OS_TREE_H_INCLUDED
#define OS_TREE_H_INCLUDED

enum r_or_b {red,black};

template<class T> struct OS_Node
{
  T data;
  int key;
  r_or_b color;
  OS_Node* parent;
  OS_Node* left;
  OS_Node* right;
  int os_rank;
  OS_Node(int k=0,T d=0):key(k),data(d),color(red),parent(0),left(0),right(0),os_rank(1) {}
};

template<class T> class OS_Tree
{
  private:
      OS_Node<T> nil_value;
      OS_Node<T>* nil;
      void os_tree_insert_fixup(OS_Node<T>* z);
      void os_tree_delete_fixup(OS_Node<T>* z);
      void os_tree_transplant(OS_Node<T>* u,OS_Node<T>* v);
      void os_tree_left_rotate(OS_Node<T>* z);
      void os_tree_right_rotate(OS_Node<T>* z);
      void os_tree_set_nil();
      void os_tree_rank_fixup(OS_Node<T>* z);
  public:
      OS_Node<T>* root;
      OS_Tree():nil_value(0,0),nil(0),root(0) {nil=&nil_value;os_tree_set_nil();root=nil;}
      ~OS_Tree() {}
      OS_Node<T>* os_tree_search(OS_Node<T>* z,int k);
      OS_Node<T>* os_tree_maximum(OS_Node<T>* z);
      OS_Node<T>* os_tree_minimum(OS_Node<T>* z);
      OS_Node<T>* os_tree_successor(OS_Node<T>* z);
      OS_Node<T>* os_tree_predecessor(OS_Node<T>* z);
      int os_tree_rank(OS_Node<T>* z);
      int os_tree_recurse_rank(OS_Node<T>* x,OS_Node<T>* z);
      OS_Node<T>* os_tree_select(OS_Node<T>* z,int r);
      OS_Node<T>* os_tree_no_recurse_select(OS_Node<T>* z,int r);
      void os_tree_walk_in_order(OS_Node<T>* z);
      void os_tree_insert(OS_Node<T>* z);
      void os_tree_delete(OS_Node<T>* z);
      OS_Node<T>* os_tree_find_i_successor(OS_Node<T>* z,int i);//14.1-6

};

#endif // OS_TREE_H_INCLUDED
