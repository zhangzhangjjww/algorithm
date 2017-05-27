#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

template<class T> struct Node
{
  T data;
  int key;
  bool visited;
  Node<T>* parent;
  Node<T>* left;
  Node<T>* right;
  Node<T>* succ;
  Node(T d,int k):data(d),key(k),visited(false),parent(0),left(0),right(0),succ(0) {}
};


template<class T> class tree
{
public:
    Node<T>* root;
    tree():root(0) {}
    void tree_insert(Node<T>* n);
    void recurse_tree_insert(Node<T>* x,Node<T>* z);
    Node<T>* tree_search(Node<T>* p,int k);
    Node<T>* iterative_tree_search(Node<T>* p,int k);
    void tree_delete1(Node<T>* x);//ѡ����
    void tree_delete2(Node<T>* x);//ѡ��ǰ��
    void tree_delete(Node<T>* x);//����12.3-6������ƽ��ɾ������
    Node<T>* tree_maximum(Node<T>* x);
    Node<T>* tree_minimum(Node<T>* x);
    Node<T>* tree_successor(Node<T>* x);
    Node<T>* tree_predecessor(Node<T>* x);
    void inorder_tree_walk(Node<T>* x);
    void no_recurse_using_stack_inorder_tree_walk();
    void no_recurse_no_stack_inorder_tree_walk();
private:
    void transplant(Node<T>* u,Node<T>* v);
    Node<T>* use_succ_find_parent(Node<T>* x);//ֻ��Ϊ�������д�������ã���Ϊ�ڳ�ʼ��ʱû�ж�succָ�븳ֵ
    Node<T>* find_parent(Node<T>* z,Node<T>* x);
};

#endif // TREE_H_INCLUDED
