#include<iostream>
//#include<cctype>
#include<cstdlib>
#include<ctime>
const int N=1000;

using std::cin;
using std::cout;
using std::endl;

int main()
{
    srand(std::time(0));
    int a[N],b[N],c[N+1];
    for(size_t i=0;i!=N;++i)
    {
        if(rand()%2==0)
            a[i]=0;
        else
            a[i]=1;
    }
    for(size_t i=0;i!=N;++i)
    {
        if(rand()%2==0)
            b[i]=0;
        else
            b[i]=1;
    }
    int k=0;
    for(size_t i=0;i!=N;++i)
    {
        int re=a[i]+b[i]+k;
        if(re>1)
            k=1;
        else
            k=0;
        c[i]=re%2;
    }
    c[N]=k;
    for(size_t i=0;i!=N;++i)
    {
        cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;
    }
    cout<<c[N]<<endl;
    return 0;
}
