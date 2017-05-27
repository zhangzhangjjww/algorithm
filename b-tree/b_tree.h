#ifndef B_TREE_H_INCLUDED
#define B_TREE_H_INCLUDED

const int TT=3;

template<class T> struct Node
{
	bool isaleaf;
	int size;
	T key[2*TT+1];
	Node* child[2*TT];
	Node():isaleaf(true),size(0) {}
};

template<class T> class B_Tree
{
private:
	int node_number;
	Node<T>* allocate_node();
	void disk_write(Node<T>* x);
	void disk_read(Node<T>* x);
public:
	Node<T>* root;
    B_Tree();
	void b_tree_create();
	void view_statistics();
	void recursive_clear(Node<T>* x);
	~B_Tree();
	void print_tree(Node<T>* x);
	Node<T>* b_tree_search(Node<T>* x,T &k);
	void b_tree_insert(T k);
	void b_tree_split_child(Node<T>* x,int i);
	void b_tree_insert_nonfull(Node<T>* x,T k);
	bool b_tree_delete(T k);
	void recursive_remove(Node<T>* x,T key);
	void merge_child(Node<T>* x,int i);
	void b_tree_delete_node(Node<T>* x);
	T b_tree_maximum(Node<T>* x);
	T b_tree_minimum(Node<T>* x);
	T b_tree_predecessor(Node<T>* x,int i);
	T b_tree_successor(Node<T>* x,int i);
};



#endif // B_TREE_H_INCLUDED
