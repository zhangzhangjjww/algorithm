#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int random_search(int* a,int n,int v);
int deterministic_search(int* a,int n,int v);
int scramble_search(int* a,int n,int v);
void random_in_place(int* a,int n);
bool check(int * a,int n,int vol);
bool check1(int *a,int n);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=i*i*2-i;
    for(size_t i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<endl;
    int value;
    cin>>value;
    int re;
    //re=random_search(a,N,value);
   //re=deterministic_search(a,N,value);
    re=scramble_search(a,N,value);
    return 0;
}

int random_search(int* a,int n,int v)
{
    int c[n];
    for(size_t i=0;i!=n;++i)
        c[i]=0;
    int sz=rand()%n;
    while(check(c,sz,n))
    {
        if(a[sz]==v)
        {
            cout<<"We find "<<v<<" in position "<<sz<<endl;
            return sz;
        }
        sz=rand()%n;
    }
    if(check1(c,n))
    {
        cout<<"We can't find "<<v<<endl;
        return n;
    }
}

bool check(int * a,int n,int vol)
{
    if(!check1(a,vol)) {
        ++a[n];
        return true;}
    else
        return false;
}
bool check1(int * a,int n)
{
    int i;
    for(i=0;i!=n;++i)
        if(a[i]==0)
        return false;
    if(i==n)
        return true;
}

int deterministic_search(int* a,int n,int v)
{
    int i;
    for(i=0;i!=n;++i)
        if(a[i]==v)
    {
        cout<<"We find "<<v<<" in position "<<i<<endl;
        return i;
    }
    if(i==n)
    {
        cout<<"We can't find "<<v<<endl;
        return n;
    }
}

int scramble_search(int* a,int n,int v)
{
    random_in_place(a,n);
    return deterministic_search(a,n,v);
}

void random_in_place(int * a,int n)
{
    for(int i=0;i!=n;++i)
    {
        int sz=rand()%(n-i)+i;
        int tmp=a[sz];
        a[sz]=a[i];
        a[i]=tmp;
    }
}
