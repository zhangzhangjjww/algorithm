#include<iostream>
#include<ctime>
#include<cstdlib>

using std::cout;
using std::endl;

int two_array_median(int* x,int* y,int n);
int find_median(int* a,int* b,int n,int low,int high);
void insert_sort(int* a,int p,int r);
int exponent(int base,int pow);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];int b[N];
    for(int i=0;i!=N;++i)
    {
        a[i]=rand()%exponent(N,2);
        b[i]=rand()%exponent(N,2);
    }
    insert_sort(a,0,N-1);
    insert_sort(b,0,N-1);
    int mid=two_array_median(a,b,N);
    cout<<"a:\n";
    for(int i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        if((i+1)%3==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"b:\n";
    for(int i=0;i!=N;++i)
    {
        cout<<b[i]<<" ";
        if((i+1)%3==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"Mid: "<<mid<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
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

int two_array_median(int* x,int* y,int n)
{
    int mid=find_median(x,y,n,0,n-1);
    if(mid==-1)
        mid=find_median(y,x,n,0,n-1);
    return mid;
}

int find_median(int* a,int* b,int n,int low,int high)
{
    if(low>high)
        return -1;
    else
    {
        int k=(low+high)/2;
        if(k==n&&a[n-1]<=b[0])
            return a[n-1];
        else
            if(k<n&&b[n-k-1]<=a[k]&&a[k]<=b[n-k])
            return a[k];
        else
            if(a[k]>b[n-k])
            return find_median(a,b,n,low,k-1);
        else
            return find_median(a,b,n,k+1,high);
    }
}
