#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

void cout_sort(int* a,int* b,int n,int k);
int coun t_number(int* pp,int n,int k,int a,int b);


int main()
{
    srand(time(0));
    const int N=10;
    int K=100;
    int a[N],b[N];
    for(int i=0;i!=N;++i)
    {
        a[i]=rand()%K;
        b[i]=0;
    }
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<endl;
    cout_sort(a,b,N,K);
    for(int i=0;i!=N;++i)
        cout<<b[i]<<endl;
    cout<<"in 10 t0 50 have "<<count_number(a,N,K,10,50)<<" numbers"<<endl;
    return 0;
}

void cout_sort(int* a,int* b,int n,int k)
{
    int* c=new int[k];
    for(int i=0;i!=k;++i)
        c[i]=0;
    for(int j=0;j!=n;++j)
        c[a[j]]=c[a[j]]+1;
    for(int i=1;i!=k;++i)
        c[i]=c[i]+c[i-1];
    for(int j=n-1;j!=-1;--j)
    {
        b[c[a[j]]-1]=a[j];
        c[a[j]]=c[a[j]]-1;
    }
    for(int i=0;i!=n;++i)
        a[i]=b[i];
    delete [] c;
}

int count_number(int* pp,int n,int k,int a,int b)
{
    int* p=new int[k+1];
    for(int i=0;i!=k+1;++i)
        p[i]=0;
    for(int i=0;i!=n;++i)
        p[pp[i]]=p[pp[i]]+1;
    int sum=0;
    for(int i=a;i!=b+1;++i)
        sum=sum+p[i];
    return sum;

}
