#include<iostream>
#include<limits>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

const int N=11;

void merge_sort(int* a,int p,int r);
void merge(int* a,int p,int q,int r);
void lcs_length(int* a,int* b,int s1,int s2,int** re,int** s);
void show_solution(int** s,int i,int j,int* a,int* b);

int main()
{
    srand(time(0));
    int a[N];int b[N];
    for(int i=1;i!=N;++i)
    {
        a[i]=rand()%100;
        b[i]=a[i];
    }
    merge_sort(b,1,N-1);
    int** result=new int*[N];
    int** solution=new int*[N];
    for(int i=0;i!=N;++i)
    {
        result[i]=new int[N];
        solution[i]=new int[N];
    }
    for(int i=0;i!=N;++i)
    {
        for(int j=0;j!=N;++j)
        {
            result[i][j]=0;
            solution[i][j]=0;
        }
    }
    for(int i=1;i!=N;++i)
        cout<<a[i]<<" "<<b[i]<<endl;
    lcs_length(a,b,N-1,N-1,result,solution);
    /*for(int i=1;i!=N;++i)
    {
        for(int j=1;j!=N;++j)
        {
            cout<<result[i][j]<<" ";
            cout<<"Solution: ";
            show_solution(solution,i,j,a,b);
            cout<<endl;
        }
    }*/
    cout<<"Results: ";
    show_solution(solution,N-1,N-1,a,b);
    cout<<endl;
    for(int i=0;i!=N;++i)
    {
        delete [] result[i];
        delete [] solution[i];
    }
    delete [] solution;delete [] result;
    return 0;
}

void merge_sort(int* a,int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
}

void merge(int* a,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int* L=new int[n1+1];
    int* R=new int[n2+1];
    for(int i=0;i!=n1;++i)
        L[i]=a[p+i];
    for(int i=0;i!=n2;++i)
        R[i]=a[q+1+i];
    L[n1]=numeric_limits<int>::max();
    R[n2]=numeric_limits<int>::max();
    int i=0,j=0;
    for(int k=p;k!=r+1;++k)
    {
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
    delete [] L;delete [] R;
}

void lcs_length(int* a,int* b,int i,int j,int** re,int** s)
{
    for(int l=1;l!=i+1;++l)
    {
        for(int k=1;k!=j+1;++k)
        {
            if(a[l]==b[k])
            {
                re[l][k]=re[l-1][k-1]+1;
                s[l][k]=0;
            }
            else
            {
                if(re[l][k-1]>=re[l-1][k])
                {
                    re[l][k]=re[l][k-1];
                    s[l][k]=-1;
                }
                else
                {
                    re[l][k]=re[l-1][k];
                    s[l][k]=1;
                }
            }
        }
    }
}

void show_solution(int** s,int i,int j,int* a,int* b)
{
    if(i==0||j==0)
        return;
    else
    {
        if(s[i][j]==0)
        {
            cout<<a[i]<<" ";
            show_solution(s,i-1,j-1,a,b);
        }
        else
        {
            if(s[i][j]==-1)
                show_solution(s,i,j-1,a,b);
            else
                show_solution(s,i-1,j,a,b);
        }
    }
}
