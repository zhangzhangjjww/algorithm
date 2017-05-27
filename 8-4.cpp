#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>

using std::cout;
using std::endl;

void random_position(int* a,int n);
void regular_jug_sort(int* a,int* b,int n);
int exponent(int base,int pow);
void merge_sort(int* a,int p,int r,int* b);
void merge(int* a,int p,int q,int r,int* b);
void match_jug(int* a,int* b,int p,int r);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N],b[N];
    for(int i=0;i!=N;++i)
    {
        a[i]=i;
        b[i]=a[i];
    }
    random_position(b,N);
    //regular_jug_sort(a,b,N);
    match_jug(a,b,0,N-1);
    return 0;
}

void random_position(int* a,int n)
{
    int* p=new int[n];
    for(int i=0;i!=n;++i)
        p[i]=rand()%exponent(n,3);
    merge_sort(a,0,n-1,p);
    delete [] p;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

void merge_sort(int* a,int p,int r,int* b)
{
    if(p<r)
    {
        int q=(p+r)/2;
        merge_sort(a,p,q,b);
        merge_sort(a,q+1,r,b);
        merge(a,p,q,r,b);
    }
}

void merge(int* a,int p,int q,int r,int* b)
{
    int n1=q-p+1;
    int n2=r-q;
    int* L=new int[n1+1];
    int* R=new int[n2+1];
    int* L1=new int[n1+1];
    int* R1=new int[n2+1];
    for(int i=0;i!=n1;++i) {
        L[i]=b[i+p];L1[i]=a[i+p]; }
    for(int i=0;i!=n2;++i) {
        R[i]=b[q+1+i];R1[i]=a[q+i+1]; }
    L[n1]=std::numeric_limits<int>::max();
    L1[n1]=std::numeric_limits<int>::max();
    R[n2]=std::numeric_limits<int>::max();
    R1[n2]=std::numeric_limits<int>::max();
    int i=0,j=0;
    for(int k=p;k!=r+1;++k)
    {
        if(L[i]<R[j])
        {
            b[k]=L[i];
            a[k]=L1[i];
            ++i;
        }
        else
        {
            b[k]=R[j];
            a[k]=R1[j];
            ++j;
        }
    }
    delete [] L;delete [] L1;
    delete [] R;delete [] R1;
}

void regular_jug_sort(int* a,int* b,int n)
{
    for(int i=0;i!=n;++i)
        for(int j=0;j!=n;++j)
        if(a[i]==b[j])
        cout<<a[i]<<" "<<b[j]<<endl;
}

void match_jug(int* a,int* b,int p,int r)
{
    int n=r-p+1;
    if(n==0)
        return;
    if(n==1) {
        cout<<a[p]<<" "<<b[p]<<endl;return; }
    else
    {
        int re=rand()%n+p;
        int i=p-1;
        for(int j=p;j!=r+1;++j)
        {
            if(b[j]<a[re])
            {
                ++i;
                int tmp=b[i];
                b[i]=b[j];
                b[j]=tmp;
            }
        }
        int k=r+1;
        for(int j=r;j!=i;--j)
        {
            if(b[j]>a[re])
            {
                --k;
                int tmp=b[k];
                b[k]=b[j];
                b[j]=tmp;
            }
        }
        int i1=p-1;
        for(int j=p;j!=r+1;++j)
        {
            if(a[j]<b[i+1])
            {
                ++i1;
                int tmp=b[i1];
                b[i1]=b[j];
                b[j]=tmp;
            }
        }
        int k1=r+1;
        for(int j=r;j!=i1;--j)
        {
            if(a[j]>b[i+1])
            {
                --k1;
                int tmp=b[k1];
                b[k1]=b[j];
                b[j]=tmp;
            }
        }
        cout<<a[re]<<" "<<b[i+1]<<endl;
        match_jug(a,b,p,i);
        match_jug(a,b,i+2,r);
    }

}
