#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

template<class T> struct Node
{
    T data;
    int key;
    Node* parent;
    Node* left;
    Node* right;
    bool visited;
    Node(T d,int k):data(d),key(k),parent(0),left(0),right(0),visited(false) {}
    Node():data(0),key(0),parent(0),left(0),right(0),visited(false) {}
    Node(const Node<T>& n):data(n.data),key(n.k),parent(0),left(0),right(0),visited(false)
    {
        *parent=*n.parent;
        *left=*n.left;
        *right=*n.right;
    }
    Node<T>& operator=(const Node<T>& n)
    {
        data=n.data;
        key=n.key;
        visited=n.visited;
        return *this;
    }
};

template<class T> class b_search_tree
{
public:
    Node<T>* root;
    b_search_tree():root(0) {}
    b_search_tree(Node<T>* a,int p,int r);
    void tree_insert(Node<T>* n);
    void recurse_tree_insert(Node<T>* x,Node<T>* z);
    void inorder_tree_walk(Node<T>* p);
    void no_recurse_using_stack_inorder_tree_walk();
    void no_recurse_no_stack_inorder_tree_walk();
    Node<T>* tree_search(Node<T>* p,int k);
    Node<T>* iterative_tree_search(Node<T>* p,int k);
    Node<T>* tree_minimum(Node<T>* p);
    Node<T>* tree_maximum(Node<T>* p);
    Node<T>* tree_successor(Node<T>* p);
    Node<T>* tree_predecessor(Node<T>* p);
    void transplant(Node<T>* u,Node<T>* v);
    void tree_delete(Node<T>* z);
};


#endif // BINARY_TREE_H_INCLUDED
