#include<iostream>
#include<cctype>

int const N=1000;

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    for(size_t i=0;i!=N-1;++i)
    {
        int mi=a[i+1];size_t pos=i+1;
        for(size_t j=i+1;j!=N;++j)
        {
            if(mi>a[j])
            {
                mi=a[j];
                pos=j;
            }
        }
        if(a[pos]<a[i]){
        a[pos]=a[i];
        a[i]=mi;}
    }
    if(a[N-1]<a[N-2])
    {
        int k=a[N-1];
        a[N-1]=a[N-2];
        a[N-2]=k;
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
