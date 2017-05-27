#include<iostream>
#include<cctype>
#include<limits>
using namespace std;
struct answer
{
    size_t l;
    size_t h;
    int re;
};

answer naive_maximum_subarray(size_t low,size_t high,int *a);

const int N=9;

int main()
{
    int a[N]={-1,-2,-3,-4,-5,-6,-7,-8,-9};
    answer an=naive_maximum_subarray(0,N,a);
    for(size_t i=an.l;i!=an.h+1;++i)
        cout<<a[i]<<" ";
    cout<<an.re<<endl;
}

answer naive_maximum_subarray(size_t low,size_t high,int *a)
{
    int sum=(numeric_limits<int>::min)();int ress;
    size_t key1=0,key2=0;
    for(size_t i=low;i!=high;++i)
    {
        ress=a[i];
        if(ress>sum)
        {
            sum=ress;key1=i;key2=i;
        }
        for(size_t j=i+1;j!=high;++j)
        {
            ress+=a[j];
            if(ress>sum)
            {
                sum=ress;key1=i;key2=j;
            }
        }
    }
    answer an;
    an.l=key1;an.h=key2;an.re=sum;
    if(sum<0)
    {
        an.re=0;
        an.l=1;an.h=0;
    }
    return an;
}
