#include<iostream>
#include<cctype>

using std::cin;
using std::cout;
using std::endl;
const int N=5;

int Horner_rule(int*,int,int,int);

int main()
{
  int a[N];
  for(size_t i=0;i!=N;++i)
        a[i]=i;
  int base=2;
  int re=Horner_rule(a,0,N-1,base);
  cout<<re<<endl;
  return 0;
}

int Horner_rule(int *a,int p,int r,int base)
{
    int re=0;
    for(int i=r;i!=-1;--i)
        re=re*base+a[i];
    return re;
}
