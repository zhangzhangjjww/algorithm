#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;
using std::cin;

struct data
{
    int diff;
    int value;
};

void insert_sort(int* a,int p,int r);
void insert_sort(data* a,int p,int r);
int select(int* a,int p,int r,int rank);
int partition(int* a,int p,int r,int x);
void find_k_mid_number(int* a,int p,int r,int k,int* b);
int exponent(int base,int pow);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    int k;
    cout<<"Enter a number:";
    cin>>k;
    for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<endl;
    int* p=new int[k];
    for(int i=0;i!=k;++i)
        p[i]=0;
    cout<<endl;
    find_k_mid_number(a,0,N-1,k,p);
    insert_sort(a,0,N-1);
    for(int i=0;i!=N;++i)
     {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<k<<" number in mid:"<<endl;
    for(int i=0;i!=k;++i)
        cout<<p[i]<<endl;
    delete [] p;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int select(int* a,int p,int r,int rank)
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

int partition(int* a,int p,int r,int x)
{
    int re;
    for(int i=p;i!=r+1;++i)
        if(a[i]==x)
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
    int tmp3=a[r];
    a[r]=a[i+1];
    a[i+1]=tmp3;
    return i+1;
}


void insert_sort(int* a,int p,int r)
{
    if(p<r)
    {
        for(int i=p;i!=r+1;++i)
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

void insert_sort(data* a,int p,int r)
{
    if(p<r)
    {
        for(int i=p;i!=r+1;++i)
        {
            int key=a[i].diff;int key2=a[i].value;
            int j=i-1;
            while(j>p-1&&a[j].diff>key)
            {
                a[j+1]=a[j];
                --j;
            }
            a[j+1].diff=key;
            a[j+1].value=key2;
        }
    }
}

void find_k_mid_number(int* a,int p,int r,int k,int* b) //对于存在重复元素存在一些问题
{
    if(p<r)
    {
        int n=r-p+1;
        int count=1;
        int mid=select(a,p,r,n/2);
        data* p1=new data[n];
        for(int i=0;i!=n;++i)
        {
            if(a[i+p]-mid>0)
                p1[i].diff=a[i+p]-mid;
            else if(a[i+p]-mid<0)
                p1[i].diff=mid-a[i+p];
                else if(cout!=0&&a[i+p]==mid) {
                    p1[i].diff=exponent(n,2);--count;}
                    else
                        p1[i].diff=0;
            p1[i].value=a[i+p];
        }
        insert_sort(p1,0,n-1);
        for(int i=0;i!=k;++i)
            b[i]=p1[i].value;
        delete [] p1;
    }
}
