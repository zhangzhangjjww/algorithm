#include<iostream>

using std::cin;
using std::cout;
using std::endl;

const int N=10;

template<class T> class list2
{
  private:
        T key[N];
        T next[N];
        T prev[N];
        int head;
        int free;
  public:
    list2()
    {
        for(int i=0;i!=N;++i)
        {
            key[i]=-1;
            prev[i]=-1;
            next[i]=i+1;
        }
        next[N-1]=-1;
        head=0;free=0;
    }
    ~list2() {}
    bool empty()
    {
        if(head==free)
            return true;
        else
            return false;
    }
    void insert(T x)
    {
        if(free==N)
        {
            cout<<"full!"<<endl;
            return;
        }
        else
        {
            key[free]=x;
            if(!empty())
            next[prev[free]]=free;
            int tmp=free;
            free=next[free];
            prev[free]=tmp;
            next[tmp]=-1;
        }
    }
    void delete1(int x)
    {
        if(empty())
        {
            cout<<"empty!"<<endl;
            return;
        }
        //int tmp=prev[free];
        if(x==head)
        {
            head=next[x];
            prev[head]=-1;
        }
        next[prev[x]]=next[x];
        prev[next[x]]=prev[x];
        next[x]=free;
        prev[x]=prev[free];
        free=x;
    }
    void display()
    {
        for(int i=head;i!=-1;)
        {
            cout<<key[i]<<endl;
            i=next[i];
        }
    }
    void display2()
    {
        for(int i=0;i!=N;++i)
            cout<<prev[i]<<" "<<key[i]<<" "<<next[i]<<endl;
    }
};

int main()
{
    list2<int> ls;
    ls.insert(4);
    ls.insert(5);
    ls.insert(6);
    ls.delete1(1);
   // ls.display2();
    ls.insert(1);
    ls.insert(2);
    ls.display();
    return 0;
}
