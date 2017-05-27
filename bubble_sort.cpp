#include<iostream>
#include<cctype>

using std::cout;
using std::endl;

const int N=10000;

void bubble_sort(int*,int,int);

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    bubble_sort(a,0,N-1);
    int n=0;
    for(size_t i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if(++n%10==0)
            cout<<endl;
    }
    return 0;
}

void bubble_sort(int *a,int p,int r)
{
    for(size_t i=p;i!=r+1;++i)
        for(size_t j=r;j!=i;--j)
        if(a[j]<a[j-1])
    {
        int key=a[j-1];
        a[j-1]=a[j];
        a[j]=key;
    }
}
