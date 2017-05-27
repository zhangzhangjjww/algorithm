#include<iostream>

using std::cin;
using std::cout;
using std::endl;

const int N=3*6+1;

struct list1
{
    int a[N];
    int head;
    int free;
    list1()
    {
        for(int i=0;i!=N;++i)
            a[i]=-1;
        head=0;free=0;
    }
    bool empty()
    {
        if(head==free)
            return true;
        else
            return false;
    }
    void insert(int x)
    {
        if(free==N-1)
        {
            cout<<"full!\n";
            return;
        }
        if(empty())
            a[head+1]=N;
        else
            {
                int tmp2=free+1;
                int j=free+3;
                int free1;
                for(;j!=N-1;++j)
                    if(a[j]==-1)
                    {
                        free1=j;
                        break;
                    }
                if(j==N-1) free1=N-1;
                a[tmp2]=free1-3;
            }
        a[free]=x;
        int tmp=free+2;
        int i=free+3;
        for(;i!=N-1;++i)
            if(a[i]==-1)
            {
                free=i;
                break;
            }
        if(i==N-1) free=N-1;
        a[tmp]=free;
    }
    void delete1(int x)
    {
        if(empty())
        {
            cout<<"empty"<<endl;
            return;
        }
        int tmp=free-1;
        a[a[x+1]+2]=a[x+2];
        a[a[x+2]+1]=a[x+1];
        if(head==x)
            head=a[x+2];
        a[x]=-1;
        a[x+1]=-1;
        a[x+2]=-1;
        free=x;
        a[tmp]=free;
    }
    int search(int x)
    {
        int tmp=head;
        while(tmp!=free&&a[tmp]!=x)
            tmp=a[tmp+2];
        return tmp;
    }
    void display()
    {
        for(int i=head;i!=free;)
        {
            cout<<a[i]<<endl;
            if(i==N-1)
                i=0;
            else
                i=a[i+2];
        }
    }
};

int main()
{
    list1 q;
    q.insert(2);
    q.insert(2);
    q.insert(3);
    q.delete1(0);
    q.insert(4);
    q.insert(5);
    q.delete1(3);
    q.insert(6);
    q.insert(7);
    q.display();
    return 0;
}
