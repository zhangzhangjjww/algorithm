#include<iostream>
#include<cctype>
#include<limits>

using std::cin;
using std::cout;
using std::endl;

int count_inversion(int*,int,int);
int count_inversion_merge(int*,int,int,int);

const int N=100;

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    int re=count_inversion(a,0,N-1);
    cout<<re<<endl;
    return 0;
}

int count_inversion(int *a,int p,int r)
{
    int q;int re=0;
    if(p<r)
    {
        q=(p+r)/2;
        re+=count_inversion(a,p,q);
        re+=count_inversion(a,q+1,r);
        re+=count_inversion_merge(a,p,q,r);
    }
    return re;
}

int count_inversion_merge(int *a,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int re=0;
    bool counted=false;
    int *L=new int[n1+1];
    int *R=new int[n2+1];
    for(size_t i=0;i!=n1;++i)
        L[i]=a[p+i];
    for(size_t i=0;i!=n2;++i)
        R[i]=a[q+i+1];
    L[n1]=(std::numeric_limits<int>::max)();
    R[n2]=(std::numeric_limits<int>::max)();
    int i=0,j=0;
    for(int k=p;k!=r+1;++k) {
        if(counted==false&&R[j]<L[i])
        {
            re+=n1-i+1;
            counted=false;
        }
        if(L[i]<R[j])
        {
            a[k]=L[i];
            ++i;
        }
        else
        {
            a[k]=R[j];
            ++j;
            counted=false;
        }
    }
    delete [] L;
    delete [] R;
    return re;
}
