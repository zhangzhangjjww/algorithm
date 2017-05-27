#include<iostream>
#include<vector>
#include<stack>
#include<limits>

using std::stack;
using std::vector;
using std::cout;
using std::endl;


template<class T> struct node
{
    node* left;
    node* right;
    node* parent;
    T key;
    node(T n):left(0),right(0),parent(0),key(n) {}
    node():left(0),right(0),parent(0),key(0) {}
};

template<class T> struct tree
{
    node<T>* root;
    node<T>* current;
    tree():root(0),current(0) {current=root;}
    ~tree() {delete root;}
    bool empty()
    {
        if(root==0)
            return true;
        else
            return false;
    }
    void insert(T x,node<T>* c,int left_or_right)
    {
        node<T>* p=new node<T>(x);
        if(empty())
        {
            root=p;
            current=root;
            return;
        }
        if(left_or_right==1)
            c->left=p;
        else
            c->right=p;
        p->parent=c;
        current=p->parent;
    }
    void delete1(node<T>* x)
    {
        if(x->left!=0)
            delete1(x->left);
        if(x->right!=0)
            delete1(x->right);
        delete x;
    }
    void display(node<T>* p=0)
    {
        if(!empty())
        {
            if(p==0)
                p=root;
            cout<<p->key<<endl;
            if(p->left!=0)
                display(p->left);
            if(p->right!=0)
                display(p->right);
        }
    }
};

template<class T> void Print(tree<int>* tr)
{
    node<T>* root1=tr->root;
    if(root1==0)
        return;
    stack<node<T> *> s;
    s.push(root1);
    while(!s.empty())
    {
        node<T>* a=s.top();//输出堆顶元素的关键字并弹出
        cout<<a->key<<endl;
        s.pop();
        if(a->left!=0)//再讲堆顶元素的左右孩子压入栈中
            s.push(a->left);
        if(a->right!=0)
            s.push(a->right);//输出时先输出右边孩子，若想改变顺序，则改变两个if判断条件的顺序
        //if(a->left!=0)//再讲堆顶元素的左右孩子压入栈中
         //   s.push(a->left);
    }
}

void BinaryRecursion(int n)
{
	int a;
	a = n % 2; // 取余
	n = n/2;  //右移一位 相当于除以2
	if(0 != n)
	{
		BinaryRecursion(n);
	}
	cout<<a;
}
int main()
{
    tree<int> tt;
    tt.insert(0,tt.current,0);
    tt.insert(1,tt.current,1);
    tt.insert(2,tt.current,0);
    tt.insert(3,tt.current->left,1);
    tt.insert(4,tt.current,0);
    tt.insert(5,tt.current->parent->right,1);
    tt.insert(6,tt.current,0);
   // tt.insert(7,current,0);
   // tt.insert(8,current,0);
  //  tt.insert(9,current,0);
    tt.display();
    Print<int>(&tt);
    BinaryRecursion(17612864);
    return 0;
}
