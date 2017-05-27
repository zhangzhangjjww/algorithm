#include<iostream>
#include<cctype>

const int N=10000;

using std::cin;
using std::cout;
using std::endl;

int line_search(int*,int,int);
int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    int v=1;
    int result=line_search(a,N,v);
    if(result==N)
        cout<<"Can't find "<<v<<endl;
    else
        cout<<"Find "<<v<<" in the "<<result<<" position"<<endl;
    return 0;
}

int line_search(int *p,int sz,int val)
{
    int *i;
    for(i=p;i!=p+sz;++i)
        if(*i==val)
        return i-p;
    if(i==p+sz)
        return sz;
}
