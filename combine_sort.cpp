#include<iostream>
#include<limits>
#include<cctype>
#include<math.h>
using std::cin;
using std::cout;
using std::endl;

const int N=10000;
const int K=log10(N)/log10(2);

void merge_sort(int*,int,int);
void merge(int*,int,int,int);
void insert_sort(int*,int,int);

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    merge_sort(a,0,N-1);
    //insert_sort(a,0,N-1);
    int n=0;
    for(size_t i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        ++n;
        if(n%10==0)
            cout<<endl;
    }
}

void merge_sort(int *a,int p,int r)
{
    int q;
    if((r-p+1)>K)
    {
        q=(p+r)/2;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
    else
        insert_sort(a,p,r);
}

void merge(int *a,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int *L=new int[n1+1];
    int *R=new int[n2+1];
    for(size_t i=0;i!=n1;++i)
        L[i]=a[p+i];
    for(size_t i=0;i!=n2;++i)
        R[i]=a[q+1+i];
    L[n1]=(std::numeric_limits<int>::max)();
    R[n2]=(std::numeric_limits<int>::max)();
    int i=0,j=0;
    for(size_t k=p;k!=r+1;++k)
    {
        if(L[i]<R[j])
        {
            a[k]=L[i];
            ++i;
        }
        else
        {
            a[k]=R[j];
            ++j;
        }
    }
    delete [] L;
    delete [] R;
}

void insert_sort(int *a,int p,int r)
{
    for(size_t i=p+1;i!=r+1;++i)
    {
        int key=a[i];
        int j=i-1;
            while(j>(p-1)&&a[j]>key)
            {
                a[j+1]=a[j];
                --j;
            }
        a[j+1]=key;

    }

}
