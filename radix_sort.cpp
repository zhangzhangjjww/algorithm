#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

void get_position(int* a,int n,int* b,int pos,int k);
void count_sort(int* a,int n,int* b,int k);
void radix_sort(int* a,int n,int k,int d);
int exponent(int base,int pow);

const int N=10;
const int K=9;
const int D=3;

int main()
{
    srand(time(0));
    int a[N],b[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(K+1,D);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<endl;
    for(int i=0;i!=N;++i)
        b[i]=N-1-i;
    radix_sort(a,N,K,D);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    return 0;
}

void get_position(int* a,int n,int* b,int pos,int k)
{
    for(int i=0;i!=n;++i)
    {
        int tmp=a[i]/exponent(k+1,pos);
        b[i]=(a[i]-tmp*exponent(k+1,pos))/exponent(k+1,pos-1);
    }
}

void count_sort(int* a,int n,int* b,int k)
{
    int* p=new int[k+1];
    int* p2=new int[n];
    for(int i=0;i!=n;++i)
        p2[i]=0;
    for(int i=0;i!=k+1;++i)
        p[i]=0;
    for(int i=0;i!=n;++i)
        p[b[i]]=p[b[i]]+1;
    for(int i=1;i!=k+1;++i)
        p[i]=p[i]+p[i-1];
    for(int i=n-1;i!=-1;--i)
    {
        p2[p[b[i]]-1]=a[i];
        p[b[i]]=p[b[i]]-1;
    }
    for(int i=0;i!=n;++i)
        a[i]=p2[i];
    delete [] p;delete[] p2;
}

void radix_sort(int* a,int n,int k,int d)
{
    for(int i=1;i!=d+1;++i)
    {
        int* b=new int[n];
        for(int i=0;i!=n;++i)
            b[i]=0;
        get_position(a,n,b,i,k);
        count_sort(a,n,b,k);
        delete [] b;
    }
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum=sum*base;
    return sum;
}
