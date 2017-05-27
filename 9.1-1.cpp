#include<set>
#include<iostream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdexcept>

using std::cout;
using std::endl;
using std::set;

struct element
{
    int value;
    int pos;
    set<int> position;
};

void find_min_sec(int* a,int n);
element find_min(element* a,int n);
int exponent(int base,int pow);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,2);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    find_min_sec(a,N);
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

void find_min_sec(int* a,int n)
{
    element* p=new element[n];
    for(int i=0;i!=n;++i) {
        p[i].value=a[i];p[i].pos=i;}
    element min=find_min(p,n);
    int sec=exponent(n,2);
    for(set<int>::iterator i=min.position.begin();i!=min.position.end();++i)
        if(a[*i]<sec)
        sec=a[*i];
    cout<<"Second min: "<<sec<<endl;
    delete [] p;
}

element find_min(element* a,int n)
{
    if(n<=0)
        throw std::overflow_error("out fo range");
    if(n==1)
    {
        cout<<"min: "<<a[0].value<<endl;
        return a[0];
    }
    else
    {
        if(n%2==0)
        {
            int j=0;
            for(int i=0;i!=n;i=i+2,++j)
            {
                if(a[i].value<a[i+1].value)
                {
                    a[i].position.insert(a[i+1].pos);
                    a[j]=a[i];
                }
                else
                {
                    a[i+1].position.insert(a[i].pos);
                    a[j]=a[i+1];
                }
            }
            int sz=n/2;
            return find_min(a,sz);
        }
        else
        {
            int j=0;
            for(int i=0;i!=n-1;i=i+2,++j)
            {
                if(a[i].value<a[i+1].value)
                {
                    a[i].position.insert(a[i+1].pos);
                    a[j]=a[i];
                }
                else
                {
                    a[i+1].position.insert(a[i].pos);
                    a[j]=a[i+1];
                }
            }
            a[j]=a[n-1];
            int sz=(n-1)/2+1;
            return find_min(a,sz);
        }
    }
}
