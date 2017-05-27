#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

int random_select(int* a,int p,int r,int i);
int partition(int* a,int p,int r);
int random_partition(int* a,int p,int r);
int exponent(int base,int pow);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    int k;
    cout<<"Please enter the rank between 1 to "<<N<<endl;
    cin>>k;
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<"The rank "<<k<<" number is "<<random_select(a,0,N-1,k)<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int partition(int* a,int p,int r)
{
    int key=a[r];
    int i=p-1;
    for(int j=p;j!=r+1;++j)
    {
        if(a[j]<key)
        {
            ++i;
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    }
    int tmp2=a[i+1];
    a[i+1]=a[r];
    a[r]=tmp2;
    return i+1;
}

int random_partition(int* a,int p,int r)
{
    int sz=r-p+1;
    int re=rand()%sz+p;
    int tmp=a[r];
    a[r]=a[re];
    a[re]=tmp;
    return partition(a,p,r);
}

int random_select(int* a,int p,int r,int i)
{
    if(p==r)
        return a[p];
    int q=random_partition(a,p,r);
    int k=q-p+1;
    if(k==i)
        return a[q];
    else
        if(k<i)
        return random_select(a,q+1,r,i-k);
    else
        return random_select(a,p,q-1,i);
}
