#include<iostream>
#include<cctype>

using std::cout;
using std::endl;

const int N=10000;
int search(int*,int,int,int);

int main()
{
    int a[N];
    for(size_t i=0;i!=N;++i)
        a[i]=i;
    int v=N-1;
    int re=search(a,0,N,v);
    if(re==N)
        cout<<"Can't find "<<v<<endl;
    else
        cout<<"Find "<<v<<" in the "<<re<<" position"<<endl;
    return 0;
}

int search(int* a,int p,int r,int v)
{
    int q;int re;
    if(p<r)
    {
       q=(p+r)/2;
       if(a[q]==v)
        return q;
       else
        if(v>a[q])
        search(a,q+1,r,v);//p=q+1;
       else
        search(a,p,q-1,v);//r=q-1;
    }
    else
    return N;
}
