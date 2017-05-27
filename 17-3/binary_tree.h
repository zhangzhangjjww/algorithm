#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

const double alfa=0.5;

template<class T> struct Data
{
    T value;
    int key;
    Data(T v=0,int k=0):value(v),key(k) {}
    Data(Data& d):value(d.value),key(d.key) {}
};

template<class T> struct Node
{
    Data<T> data;
    int size;
    Node* parent;
    Node* left;
    Node* right;
    Node():size(1),parent(0),left(0),right(0) {}
};

template<class T> class Binary_Tree
{
private:
    Node<T>* allocate_node();
    void recursive_clear(Node<T>* x);
    void binary_tree_left_rotate(Node<T>* x);
    void binary_tree_right_rotate(Node<T>* x);
    void binary_tree_insert2(Node<T>* x,Node<T>* y);
    void binary_tree_transplant(Node<T>* x,Node<T>* y);
    void fix(Node<T>* x);
public:
    Node<T>* root;
    Binary_Tree();
    ~Binary_Tree();
    Node<T>* binary_tree_search(Node<T>* x,Data<T> d);
    bool isempty();
    void binary_tree_insert(Data<T> d);
    void binary_tree_insert_fixup(Node<T>* x);
    void binary_tree_delete(Data<T> d);
    Node<T>* binary_tree_maximum(Node<T>* x);
    Node<T>* binary_tree_minimum(Node<T>* x);
    Node<T>* binary_tree_predecessor(Node<T>* x);
    Node<T>* binary_tree_successor(Node<T>* x);
    void binary_tree_walk_in_order(Node<T>* x);
    void binary_tree_walk_in_order2(Node<T>* x);
};

#endif // BINARY_TREE_H_INCLUDED
