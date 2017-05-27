#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void random_sample(int* a,int m,int *s,int n);

int main()
{
    srand(time(0));
    const int M=100,N=10;
    int a[M],s[N];
    for(size_t i=0;i!=M;++i)
        a[M]=i+1;
    for(size_t i=0;i!=N;++i)
        s[i]=0;
    random_sample(a,M,s,N);
    for(size_t i=0;i!=N;++i)
        cout<<s[i]<<endl;
    return 0;
}

int sub=0;
void random_sample(int* a,int n,int* s,int m)
{
    if(m==0)
        return;
    else
    {
        random_sample(a,n-1,s,m-1);
        int i=rand()%n+1;int j;
        for(j=0;j!=sub;++j) {
            if(s[j]==i) {
            s[sub]=n;sub++;break;}
        }
        if(j==sub) {
            s[sub]=i;sub++;}
    }
}
