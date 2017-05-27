#include<iostream>

struct Set
{
    int x;
    int y;
    Set& operator=(const Set& s)
    {
        x=s.x;
        y=s.y;
        return *this;
    }
};

void cout_sort1(Set* a,Set* b,int k)
{
    int* c=new int[k+1];
    for(int i=0;i!=k+1;++i) {
        c[i]=0;
    }
    for(int j=0;j!=k+1;++j) {
        c[a[j].x]=c[a[j].x]+1;
    }
    for(int i=1;i!=k+1;++i) {
        c[i]=c[i]+c[i-1];
    }
    for(int i=k;i!=-1;--i) {
        b[c[a[i].x]]=a[i];
        c[a[i].x]--;
    }
}
