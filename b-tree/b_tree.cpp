#include<iostream>
#include"b_tree.h"
#include<queue>

using std::queue;


#define DEBUG 1

template<class T> B_Tree<T>::B_Tree():root(0),node_number(0)
{
	b_tree_create();
}

template<class T> void B_Tree<T>::b_tree_create()
{
	Node<T>* x=allocate_node();
	x->isaleaf=true;
	x->size=0;
	disk_write(x);
	root=x;
}

template<class T> Node<T>* B_Tree<T>::allocate_node()
{
	Node<T>* x=new Node<T>;
	++node_number;

#ifdef DEBUG
        std::cout << "allocate a new node" <<std::endl;
#endif
	return x;
}

template<class T> void B_Tree<T>::disk_write(Node<T>* x)
{
#ifdef DEBUG
	std::cout<<"disk write"<<std::endl;
#endif
}

template<class T> void B_Tree<T>::disk_read(Node<T>* x)
{
#ifdef DEBUG
	std::cout<<"disk read"<<std::endl;
#endif
}


template<class T> void B_Tree<T>::view_statistics()
{
	std::cout << "-----------------------------Statistics-----------------------------" <<std::endl;
    std::cout << "BUILD " << node_number << " nodes" <<std::endl;
    std::cout << "-----------------------------Statistics-----------------------------" <<std::endl;
}

template<class T> void B_Tree<T>::recursive_clear(Node<T>* x)
{
	if(x!=nullptr)
	{
		if(!x->isaleaf)
		{
			for(int i=0;i!=x->size+1;++i)
				recursive_clear(x->child[i]);
		}
		delete x;
	}
}

template<class T> B_Tree<T>::~B_Tree()
{
	recursive_clear(root);
	root=0;
}

template<class T> void B_Tree<T>::print_tree(Node<T>* x)
{
	queue<Node<T>*> myqueue;
	myqueue.push(x);
	int depth=0;
	while(!myqueue.empty())
	{
		std::cout<<"depth:"<<depth<<std::endl;
		++depth;
		queue<Node<T>*> nextlevel;
		while(!myqueue.empty())
		{

			Node<T>* tmp=myqueue.front();
			myqueue.pop();
			std::cout<<"[";
			for(int i=0;i!=tmp->size;++i)
				std::cout<<tmp->key[i]<<" ";
			std::cout<<"]";
			if(!tmp->isaleaf)
			{
				for(int j=0;j!=tmp->size+1;++j)
					nextlevel.push(tmp->child[j]);
			}
		}
		std::cout<<std::endl;
		myqueue=nextlevel;
	}
}

template<class T> T B_Tree<T>::b_tree_maximum(Node<T>* x)
{
	if(x==nullptr)
	{
		std::cerr<<"The tree is empty"<<std::endl;
		return -1;
	}
	while(!x->isaleaf)
	{
		x=x->child[x->size];
		disk_read(x);
	}
	return x->key[x->size-1];
}

template<class T> T B_Tree<T>::b_tree_minimum(Node<T>* x)
{
	if(x==nullptr)
	{
		std::cerr<<"The tree is empty"<<std::endl;
		return -1;
	}
	while(!x->isaleaf)
	{
		x=x->child[0];
		disk_read(x);
	}
	return x->key[0];
}

template<class T> T B_Tree<T>::b_tree_predecessor(Node<T>* x,int i)
{
}
