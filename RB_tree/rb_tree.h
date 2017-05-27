#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED

enum r_or_b {red,black};

template<class T> struct RB_Node
{
    int key;
    T data;
    RB_Node* parent;
    RB_Node* left;
    RB_Node* right;
    r_or_b color;
    RB_Node(int k=0,T d=0):key(k),data(d),parent(0),left(0),right(0),color(red) {}
};


template<class T> class RB_Tree
{
private:
    RB_Node<T>* nil;
    RB_Node<T> nil_value;
    void rb_tree_transplant(RB_Node<T>* u,RB_Node<T>* v);
    void rb_tree_insert_fixup(RB_Node<T>* z);
    void rb_tree_delete_fixup(RB_Node<T>* z);
    void rb_tree_set_value(RB_Node<T>* z);
public:
    RB_Node<T>* rb_root;
    RB_Tree():rb_root(0),nil(0),nil_value(0,0) {nil=&nil_value;rb_tree_set_value(nil);rb_root=nil;}
    void walk_in_order(RB_Node<T>* z);
    void rb_tree_insert(RB_Node<T>* z);
    //void rb_tree_insert_without_parent(RB_Node<T>* z);
    void rb_tree_delete(RB_Node<T>* z);
    RB_Node<T>* rb_tree_search(RB_Node<T>* z,int k);
    RB_Node<T>* rb_tree_maximum(RB_Node<T>* z);
    RB_Node<T>* rb_tree_minimum(RB_Node<T>* z);
    RB_Node<T>* rb_tree_successor(RB_Node<T>* z);
    RB_Node<T>* rb_tree_decessor(RB_Node<T>* z);
    void left_rotate(RB_Node<T>* z);
    void right_rotate(RB_Node<T>* z);
};

#endif // RB_TREE_H_INCLUDED
