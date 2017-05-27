#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

struct result
{
    int max;
    int min;
};

result find_max_and_min(int* a,int n);
int exponent(int base,int pow);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(int i=0;i!=N;++i)
       a[i]=rand()%exponent(10,2);
    result re=find_max_and_min(a,N);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    cout<<"max: "<<re.max<<'\t'<<"min: "<<re.min<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

result find_max_and_min(int* a,int n)
{
    result re;
    if(n%2==1)
    {
        re.max=a[0];
        re.min=a[0];
        int sz=(n-1)/2;
        result* p=new result[sz];
        for(int i=0;i!=sz;++i)
        {
            if(a[2*i+1]<a[2*(i+1)])
            {
                p[i].max=a[2*(i+1)];
                p[i].min=a[2*i+1];
            }
            else
            {
                p[i].max=a[2*i+1];
                p[i].min=a[2*(i+1)];
            }
        }
        for(int i=0;i!=sz;++i)
        {
            if(p[i].max>re.max)
                re.max=p[i].max;
            if(p[i].min<re.min)
                re.min=p[i].min;
        }
        delete [] p;
    }
    else
    {
        int sz=n/2;
        result* p=new result[sz];
        for(int i=0;i!=sz;++i)
        {
            if(a[2*i]<a[2*i+1])
            {
                p[i].max=a[2*i+1];
                p[i].min=a[2*i];
            }
            else
            {
                p[i].max=a[2*i];
                p[i].min=a[2*i+1];
            }
        }
        re.max=p[0].max;re.min=p[0].min;
        for(int i=1;i!=sz;++i)
        {
            if(p[i].max>re.max)
                re.max=p[i].max;
            if(p[i].min<re.min)
                re.min=p[i].min;
        }
        delete [] p;
    }
    return re;
};
