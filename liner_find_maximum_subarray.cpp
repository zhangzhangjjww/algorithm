#include<iostream>
#include<cctype>
#include<limits>

using namespace std;

const int N=100;

struct answer
{
    size_t l;
    size_t h;
    int re;
};

answer liner_find_maximum_subarray(size_t low,size_t high,int *a);
int main()
{
    int a[N]={-1,-2,-3,-4,-5,-6,7,8,-9};
    answer an=liner_find_maximum_subarray(0,N,a);
    for(size_t i=an.l;i!=an.h+1;++i)
        cout<<a[i]<<" ";
    cout<<an.re<<endl;
    return 0;
}

answer liner_find_maximum_subarray(size_t low,size_t high,int *a)
{
    answer real;
    size_t key1=low,key2=low;
    int sum=a[low];
    for(size_t i=low+1;i!=high;++i)
    {
        int ress=a[i];int j=i;
        if(ress>sum)
        {
            sum=ress;key1=j;key2=j;
        }
        while(--j>-1)
        {
            ress+=a[j];
            if(ress>sum)
            {
                sum=ress;key1=j;key2=i;
            }
        }
    }
    real.re=sum;real.l=key1;real.h=key2;
    return real;
}
