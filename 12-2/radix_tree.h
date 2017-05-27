#ifndef RADIX_TREE_H_INCLUDED
#define RADIX_TREE_H_INCLUDED
#include<string>
#include<iostream>

struct Node
{
    std::string data;
    Node* parent;
    Node* left;
    Node* right;
    Node(std::string s=""):data(s),parent(0),left(0),right(0) {}
};

class radix_tree
{
public:
    Node* root;
    Node():root(0) {root=new Node;}
    void insert_tree(std::string s)
    {
        int i=0;
        Node* p=root;Node* m;
        for(;i<s.size();++i)
        {
            if(s[i]='0')
            {
                if(p->left==0)
                {
                    m=new Node;
                    m->parent=p;
                    p->left=m;
                }
                else
                    m=p->left;
            }
            else
            {
                if(p->right=0)
                {
                    m=new Node;
                    m->parent=p;
                    p->right=m;
                }
                else
                    m=p->right;
            }
        if(i==s.size()-1)
            p->data=s;
        else
            p=m;
        }
    }
    void output(Node* p)
    {
        if(p!=0){
        if(p->data!="")
            std::cout<<p->data<<std::endl;
        output(p->left);
        output(p->right);}
    }
};
#endif // RADIX_TREE_H_INCLUDED
