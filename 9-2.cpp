#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

struct data
{
    int value;
    double weight;
};

int exponent(int base,int pow);
int sort_find(data* a,int p,int r);
int weighted_median(data* a,int p,int r);
void heaplify(data* a,int n,int i);
void build_max_heap(data* a,int n);
void heap_sort(data* a,int p,int r);
int parent(int i);
int left(int i);
int right(int i);

int main()
{
    srand(time(0));
    const int N=10;
    data a[N];
    int we=100;
    for(int i=0;i!=N;++i)
    {
        a[i].value=rand()%exponent(N,2);
        int tmp=rand()%(we/2);
        a[i].weight=tmp/100.0;
        we=we-tmp;
        if(i==N-1)
        {
            double sum=0;
            for(int j=0;j!=N-1;++j)
                sum+=a[j].weight;
            a[i].weight=1.0-sum;
        }
    }
    for(int i=0;i!=N;++i)
        cout<<a[i].value<<" "<<a[i].weight<<endl;
    cout<<endl;
    int mid=weighted_median(a,0,N-1);
    heap_sort(a,0,N-1);
    //int mid=sort_find(a,0,N-1);
    cout<<"Mid: "<<mid<<endl;
    for(int i=0;i!=N;++i)
        cout<<a[i].value<<" "<<a[i].weight<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int parent(int i)
{
    if(i==2)
        return 0;
    return (i+1)/2-1;
}

int left(int i)
{
    return 2*i+1;
}

int right(int i)
{
    return 2*(i+1);
}

void heaplify(data* a,int n,int i)
{
    int r=right(i);
    int l=left(i);
    int pos;
    if(l<n&&a[l].value>a[i].value)
        pos=l;
    else
        pos=i;
    if(r<n&&a[r].value>a[pos].value)
        pos=r;
    if(i!=pos)
    {
        data tmp=a[i];
        a[i]=a[pos];
        a[pos]=tmp;
        heaplify(a,n,pos);
    }
}

void build_max_heap(data* a,int n)
{
    for(int i=n/2;i!=-1;--i)
        heaplify(a,n,i);
}

void heap_sort(data* a,int p,int r)
{
    if(p<r)
    {
        int n=r-p+1;
        build_max_heap(a,n);
        int sz=n;
        for(int i=r;i!=p;--i)
        {
            data tmp=a[p];
            a[p]=a[i];
            a[i]=tmp;
            --sz;
            heaplify(a,sz,p);
        }
    }
}

int sort_find(data* a,int p,int r)
{
    heap_sort(a,p,r);
    double sum=0;
    int i=p;
    while(sum<0.5)
    {
        sum+=a[i].weight;
        ++i;
    }
    return a[i-1].value;
}

void insert_sort(data* a,int p,int r);
int select(data* a,int p,int r,int rank);
int partition(data* a,int p,int r,int x);

int weighted_median(data* a,int p,int r)
{
    int n=r-p+1;
    if(n==1)
        return a[p].value;
    if(n==2)
        if(a[p].weight>=a[r].weight)
        return a[p].value;
    else
        return a[r].value;
    else
    {
        int x=select(a,p,r,n/2);
        int k=partition(a,p,r,x);
        double wl=0,wr=0;
        for(int i=p;i!=k;++i)
            wl+=a[i].weight;
        for(int i=k+1;i!=r+1;++i)
            wr+=a[i].weight;
        if(wl<0.5&&wr<0.5)
            return a[k].value;
        else
            if(wl>0.5)
            {
                a[k].weight+=wr;
                return weighted_median(a,p,k);
            }
            else
            {
                a[k].weight+=wl;
                return weighted_median(a,k,r);
            }
    }
}

int select(data* a,int p,int r,int rank)
{
    int n=r-p+1;
    if(n==1)
        return a[p].value;
    int a1=n/5;
    int b=n%5;
    int re;
    if(b!=0)
    {
        data** p1=new data*[a1+1];
        for(int i=0;i!=a1;++i)
            p1[i]=new data[5];
        p1[a1]=new data[b];
        for(int i=0;i!=a1;++i)
            for(int j=0;j!=5;++j)
            p1[i][j]=a[i*5+j+p];
        for(int j=0;j!=b;++j)
            p1[a1][j]=a[r-b+j+1];
        for(int i=0;i!=a1;++i)
            insert_sort(p1[i],0,4);
        insert_sort(p1[a1],0,b-1);
        data* p2=new data[a1+1];
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
        data** p1=new data*[a1];
        for(int i=0;i!=a1;++i)
            p1[i]=new data[5];
        for(int i=0;i!=a1;++i)
            for(int j=0;j!=5;++j)
            p1[i][j]=a[i*5+j+p];
        for(int i=0;i!=a1;++i)
            insert_sort(p1[i],0,4);
        data* p2=new data[a1];
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
        return a[x].value;
    else
        if(k<rank)
        return select(a,x+1,r,rank-k);
    else
        return select(a,p,x-1,rank);
}

void insert_sort(data* a,int p,int r)
{
    if(p<r)
    {
        for(int i=p;i!=r+1;++i)
        {
            int key=a[i].value;double key2=a[i].weight;
            int j=i-1;
            while(j>p-1&&a[j].value>key)
            {
                a[j+1]=a[j];
                --j;
            }
            a[j+1].value=key;
            a[j+1].weight=key2;
        }
    }
}

int partition(data* a,int p,int r,int x)
{
    int re;
    for(int i=p;i!=r+1;++i)
        if(a[i].value==x)
        re=i;
    data tmp=a[re];
    a[re]=a[r];
    a[r]=tmp;
    int i=p-1;
    for(int j=p;j!=r+1;++j)
        if(a[j].value<a[r].value)
        {
            ++i;
            data tmp2=a[i];
            a[i]=a[j];
            a[j]=tmp2;
        }
    data tmp3=a[r];
    a[r]=a[i+1];
    a[i+1]=tmp3;
    return i+1;
}
