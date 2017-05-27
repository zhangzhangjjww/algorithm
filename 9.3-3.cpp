#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

int exponent(int base,int pow);
int partition(int* a,int p,int r,int mid);
int select(int* a,int p,int r,int rank);
void quick_sort(int* a,int p,int r);
void insert_sort(int* a,int p,int r);

int main()
{
    srand(time(0));
    const int N=20;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<endl;
    quick_sort(a,0,N-1);
    for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int partition(int* a,int p,int r,int mid)
{
    int re;
    for(int i=p;i!=r+1;++i)
        if(a[i]==mid)
        re=i;
    int tmp=a[re];
    a[re]=a[r];
    a[r]=tmp;
    int i=p-1;
    for(int j=p;j!=r+1;++j)
        if(a[j]<a[r])
        {
            ++i;
            int tmp2=a[i];
            a[i]=a[j];
            a[j]=tmp2;
        }
    int tmp3=a[i+1];
    a[i+1]=a[r];
    a[r]=tmp3;
    return i+1;
}

int select(int* a,int p,int r,int rank)
{
    int n=r-p+1;
    int a1=n/5;
    int b=n%5;
    int re;
    if(n==1)
        return a[p];
    if(b!=0)
    {
        int** p1=new int*[a1+1];
        for(int i=0;i!=a1;++i)
            p1[i]=new int[5];
        p1[a1]=new int[b];
        for(int i=0;i!=a1;++i)
            for(int j=0;j!=5;++j)
            p1[i][j]=a[i*5+j+p];
        for(int j=0;j!=b;++j)
            p1[a1][j]=a[r-b+j+1];
        for(int i=0;i!=a1;++i)
            insert_sort(p1[i],0,4);
        insert_sort(p1[a1],0,b-1);
        int* p2=new int[a1+1];
        for(int i=0;i!=a1;++i)
            p2[i]=p1[i][2];
        p2[a1]=p1[a1][b/2];
        re=select(p2,0,a1,(a1+1)/2);
        for(int i=0;i!=a1;++i)
            delete [] p1[i];
        delete [] p1;delete [] p2;
    }
    else
    {
        int** p1=new int*[a1];
        for(int i=0;i!=a1;++i)
            p1[i]=new int[5];
        for(int i=0;i!=a1;++i)
            for(int j=0;j!=5;++j)
            p1[i][j]=a[i*5+j+p];
        for(int i=0;i!=a1;++i)
            insert_sort(p1[i],0,4);
        int* p2=new int[a1];
        for(int i=0;i!=a1;++i)
            p2[i]=p1[i][2];
        re=select(p2,0,a1-1,a1/2);
        for(int i=0;i!=a1;++i)
            delete [] p1[i];
        delete [] p1;delete [] p2;
    }
    int x=partition(a,p,r,re);
    int k=x-p+1;
    if(k==rank)
        return a[x];
    else
        if(k<rank)
        return select(a,x+1,r,rank-k);
    else
        return select(a,p,x-1,rank);
}

void insert_sort(int* a,int p,int r)
{
    if(p<r)
    {
        for(int i=p+1;i!=r+1;++i)
        {
            int key=a[i];
            int j=i-1;
            while(j>p-1&&a[j]>key)
            {
                a[j+1]=a[j];
                --j;
            }
            a[j+1]=key;
        }
    }
}

void quick_sort(int* a,int p,int r)
{
    if(p<r)
    {
        int n=r-p+1;
        int k=n/2;
        int x=select(a,p,r,k);
        int q=partition(a,p,r,x);
        quick_sort(a,p,q-1);
        quick_sort(a,q+1,r);
    }
}
