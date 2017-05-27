#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

int random_hire_assistant(int* a,int n);
void permute_by_sorting(int* a,int n);
void random_in_place(int* a,int n);
void merge_sort(int* a,int p,int r,int* cc);
void merge_sub(int* a,int p,int q,int r,int *cc);
int random();

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=i*i+5;
    for(size_t i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<endl<<endl;
    cout<<"Total "<<random_hire_assistant(a,N)<<" hire"<<endl;;
    return 0;
}

int random_hire_assistant(int*a,int n)
{
    //permute_by_sorting(a,n);
    random_in_place(a,n);
    for(int i=0;i!=n;++i)
        cout<<a[i]<<endl;
    int best=0;int cnt=0;
    for(int i=0;i!=n;++i)
        if(a[i]>best) {
        best=a[i];
        cout<<"We would hire "<<a[i]<<endl;
        cnt++; }
    return cnt;
}

void permute_by_sorting(int* a,int n)
{
    int p[n];int re=n*n*n;
    for(size_t i=0;i!=n;++i)
        p[i]=rand()%re+1;
    for(size_t i=0;i!=n;++i)
        cout<<p[i]<<endl;
        cout<<endl;
    merge_sort(a,0,n-1,p);
    for(size_t i=0;i!=n;++i)
        cout<<p[i]<<endl;
        cout<<endl;

}

void merge_sort(int* a,int p,int r,int* cc)
{
    int q=(p+r)/2;
    if(p<r)
    {
        merge_sort(a,p,q,cc);
        merge_sort(a,q+1,r,cc);
        merge_sub(a,p,q,r,cc);
    }
}

void merge_sub(int* a,int p,int q,int r,int* cc)
{
    int n1=q-p+1;int n2=r-q;
    int* L=new int[n1+1];int* R=new int[n2+1];
    int* L1=new int[n1+1];int* R1=new int[n2+1];
    for(int i=0;i!=n1;++i)
       {L[i]=a[i+p];L1[i]=cc[p+i];}
    for(int i=0;i!=n2;++i) {
        R[i]=a[i+q+1];R1[i]=cc[i+q+1];}
    L[n1]=(numeric_limits<int>::max)();
    R[n2]=(numeric_limits<int>::max)();
    L1[n1]=(numeric_limits<int>::max)();
    R1[n2]=(numeric_limits<int>::max)();
    int i=0,j=0;
    for(int k=p;k!=r+1;++k)
    {
        if(L1[i]<R1[j])
        {
            cc[k]=L1[i];
            a[k]=L[i];
            ++i;
        }
        else
            if(L1[i]<R1[j])
        {
            cc[k]=R1[j];
            a[k]=R[j];
            ++j;
        }
        else
        {
            if(random())
                {
            cc[k]=L1[i];
            a[k]=L[i];
            ++i;
             }
        else
            {
            cc[k]=R1[j];
            a[k]=R[j];
            ++j;
            }
        }
    }
    delete [] L;delete [] L1;delete [] R;delete [] R1;
}
int   random()
{
    return rand()%2;
}
void random_in_place(int* a,int n)
{
    for(int i=0;i!=n;++i)
    {
        int sz=rand()%(n-i);
        int ex=a[i];
        a[i]=a[sz];
        a[sz]=ex;
    }
}
