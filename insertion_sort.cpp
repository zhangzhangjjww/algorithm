#include<iostream>
#include<cctype>

const int N=10000;

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    for(size_t i=1;i!=N;++i)
    {
        int key=a[i];
        int j=i-1;
        while(j>-1&&a[j]>key)
        {
            a[j+1]=a[j];
            --j;
        }
        a[j+1]=key;
    }
    int n=0;
    for(size_t i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        ++n;
        if(n%10==0)
            cout<<endl;
    }
    return 0;
}
