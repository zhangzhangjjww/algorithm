#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

void insert_sort(int* a,int p,int r);

class ls
{
private:
    int* poi;
    int sz;
    void destroy() {delete [] poi;}
public:
    ls(int s=1):poi(0),sz(s)
    {
        poi=new int[sz];
        for(int i=0;i!=sz;++i)
            poi[i]=0;
    }
    ls(const ls& l):poi(0),sz(l.sz)
    {
        poi=new int[sz];
        for(int i=0;i!=sz;++i)
            poi[i]=l.poi[i];
    }
    ~ls() {destroy();}
    ls& operator=(const ls& l)
    {
        destroy();
        poi=new int[l.sz];
        sz=l.sz;
        for(int i=0;i!=sz;++i)
            poi[i]=l.poi[i];
        return *this;
    }
    void push(int v)
    {
        int* p=new int[sz];
        for(int i=0;i!=sz;++i)
            p[i]=poi[i];
        destroy();
        sz++;
        poi=new int[sz];
        for(int i=0;i!=sz-1;++i)
            poi[i]=p[i];
        delete [] p;
        poi[sz-1]=v;
    }
    void display()
    {
        for(int i=1;i!=sz;++i)
            cout<<poi[i]<<endl;
    }
    void sort()
    {
        insert_sort(poi,0,sz-1);
    }
};
int exponent(int base,int pow);
int select(int* a,int p,int r,int rank);
void insert_sort(int* a,int p,int r);
int partition(int* a,int p,int r,int x);
void kkk(int* a,int p,int r,int k,ls& b);

int main()
{
    srand(time(0));
    const int N=20;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    cout<<"Please enter the rank:"<<endl;
    int k;
    cin>>k;
    ls re;
    for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<endl;
    kkk(a,0,N-1,k,re);
    re.sort();
    re.display();
    cout<<endl;
    insert_sort(a,0,N-1);
     for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<endl;
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

void kkk(int* a,int p,int r,int k,ls& b)
{
    static int K=k;
    int n=r-p+1;
    if(k==1) {
    return;}
    else
    {
        int i=(k)/2;
        int q=i*n/k;
        int x=select(a,p,r,q);
        int q2=partition(a,p,r,x);
        b.push(x);
        kkk(a,p,q2,i,b);
        if(k!=2)
        kkk(a,q2+1,r,(k+1)/2,b);
    }
}
