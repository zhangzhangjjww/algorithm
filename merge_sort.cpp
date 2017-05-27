#include<iostream>
#include<cctype>
#include<limits>
const int N=10000;

using std::cout;
using std::endl;
void merge_sort(int*,int,int);
void merge(int*,int,int,int);

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=N-i;
    merge_sort(a,0,N-1);
    int n=0;
    for(size_t i=0;i!=N;++i)
    {
        cout<<a[i]<<" ";
        ++n;
        if(n%10==0)
            cou t<<endl;
    }
    return 0;
}

void merge_sort(int *a,int p,int r)
{
    int q;
    if(p<r)
    {
        q=(p+r)/2;
        //cout<<q<<endl;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
}

void merge(int *a,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int *L=new int[n1];
    int *R=new int[n2];
    for(size_t i=0;i!=n1;++i)
        L[i]=a[p+i];
    for(size_t i=0;i!=n2;++i)
        R[i]=a[q+i+1];
   // L[n1]=(std::numeric_limits<int>::max)();
    //R[n2]=(std::numeric_limits<int>::max)();
    int k;
    int i=0,j=0;
    for(k=p;k!=r+1;++k)
    {
        if(i>=n1)
        {
            for(;j!=n2;++j,++k)
                a[k]=R[j];
            break;
        }
        if(j>=n2)
        {
            for(;i!=n1;++i,++k)
                a[k]=L[i];
            break;
        }
        if(L[i]<=R[j])
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
