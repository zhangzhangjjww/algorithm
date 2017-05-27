#include<iostream>

using namespace std;

const int K=4;const int N=16;

void rev(int* a1,int* a2);
void rev2(int* a1,int* a2);
void bit_set(int * b,int n);
int exponent(int base,int pow);
int bit_reverse(int n);
int bit_reversed_increment(int n);

int main()
{
    int a[N],b[N],c[N];
    for(int i=0;i!=N;++i)
    {
        a[i]=i;
        b[i]=0;
        c[i]=0;
    }
    rev(a,b);
    rev2(a,c);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;
    return 0;
}

void bit_set(int* b,int n)
{
    int i=0;int m;
    while(n>0)
    {
        b[i]=n%2;
        n=n/2;
        ++i;
    }
}

void rev(int* a1,int* a2)
{
    int b[K];
    for(int i=0;i!=N;++i)
    {
        for(int j=0;j!=K;++j)
            b[j]=0;
        bit_set(b,a1[i]);
      //  for(int j=0;j!=K;++j)
     //       cout<<b[j];
     //   cout<<endl;
        int t=0;
        for(int j=0;j!=K;++j)
            t+=exponent(2,K-j-1)*b[j];
        a2[t]=a1[i];
    }
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
    sum*=base;
    return sum;
}

int bit_reverse(int n)
{
    n=((n&0x5)<<1)|((n&0xa)>>1);
    n=((n&0xc)>>2)|((n&0x3)<<2);
    return n;
}

int bit_reversed_increment(int n)
{

    n=bit_reverse(n)+1;
    return bit_reverse(n);
}

void rev2(int* a1,int* a2)
{
    int j=0;
    for(int i=0;i!=N;++i)
    {
        a2[i]=a1[j];
        j=bit_reversed_increment(j);
    }
}
