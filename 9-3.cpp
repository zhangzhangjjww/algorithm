#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

int partition(int* a,int p,int r,int mid);
int select(int* a,int p,int q,int k);
int exponent(int base,int pow);
void insert_sort(int* a,int p,int r);

int main()
{
    srand(time(0));
    const int N=20;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    int k;
    cout<<"Please enter the rank 1 to "<<N<<endl;
    cin>>k;
    for(int i=0,j=1;i!=N;++i,++j)
    {
        cout<<a[i]<<" ";
        if(j%4==0)
            cout<<endl;
    }
    cout<<"The rank "<<k<<" number is "<<select(a,0,N-1,k)<<endl;
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
    int j=p-1;
    for(int i=p;i!=r+1;++i)
        if(a[i]<a[r])
        {
            ++j;
            int tmp2=a[i];
            a[i]=a[j];
            a[j]=tmp2;
        }
    int tmp3=a[r];
    a[r]=a[j+1];
    a[j+1]=tmp3;
    return j+1;
}

void insert_sort(int* a,int p,int r)
{
    if(p<r)
    {
        for(int i=p+1;i!=r+1;++i)
        {
            int key=a[i];
            int j=i-1;
            while(j!=-1&&a[j]>key)
            {
                a[j+1]=a[j];
                --j;
            }
            a[j+1]=key;
        }
    }
}
int select(int* a,int p,int r,int k)
{
    int n=r-p+1;
    if(n==1)
        return a[p];
    int a1=n/5;
    int b=n%5;
    int re;
    if(b!=0)
    {
        int** p1=new int*[a1+1];
        for(int i=0;i!=a1;++i)
            p1[i]=new int[5];
        p1[a1]=new int[b];
        for(int i=0;i!=a1;++i)
            for(int j=0;j!=5;++j)
            p1[i][j]=a[i*5+j+p];
        for(int i=0;i!=b;++i)
            p1[a1][i]=a[r-b+i+1];
        for(int i=0;i!=a1;++i)
            insert_sort(p1[i],0,4);
        insert_sort(p1[a1],0,b-1);
        int* p2=new int [a1+1];
        for(int i=0;i!=a1;++i)
            p2[i]=p1[i][2];
        p2[a1]=p1[a1][b/2];
        re=select(p2,0,a1,(a1+1)/2);
        for(int i=0;i!=a1+1;++i)
            delete [] p1[i];
        delete [] p1;delete [] p2;
    }
    else
    {
        int** p1=new int*[a1];
        for(int i=0;i!=a1;++i)
            p1[i]=new int [5];
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
    int rank=partition(a,p,r,re);
    int rank1=rank-p+1;
    if(rank1==k)
        return a[rank];
    else if(k<rank1)
        return select(a,p,rank-1,k);
        else
        return select(a,rank+1,r,k-rank1);
}
