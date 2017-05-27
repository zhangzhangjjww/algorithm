#include<iostream>
#include<cctype>
#include<limits>

using namespace std;

struct answer
{
    size_t l;
    size_t h;
    int re;
};

const int N=100;

answer find_maximum_subarray(size_t low,size_t high,int *a);
answer find_max_crossing_subarray(size_t low,size_t mid,size_t high,int* a);

int main()
{
    int a[N]={-1,-2,-3,-4,-5,-6,7,8,-9};
    answer ans=find_maximum_subarray(0,N-1,a);
    for(size_t i=ans.l;i!=ans.h+1;++i)
        cout<<a[i]<<" ";
    cout<<ans.re<<endl;
    return 0;
}

answer find_maximum_subarray(size_t low,size_t high,int *a)
{
    answer real;
    if(low==high)
    {
        real.l=low;real.h=high;real.re=a[low];
        if(a[low]<0)
    {
        real.re=0;
        real.l=1;real.h=0;
    }
        return real;
    }
    else
    {
        int mid=(high+low)/2;
        answer left=find_maximum_subarray(low,mid,a);
        answer right=find_maximum_subarray(mid+1,high,a);
        answer crossing=find_max_crossing_subarray(low,mid,high,a);
        if((left.re>=right.re)&&(left.re>=crossing.re))
             real=left;
        else
            if((right.re>=left.re)&&(right.re>=crossing.re))
            real=right;
        else
             real=crossing;
        if(real.re<0)
    {
        real.re=0;
        real.l=1;real.h=0;
    }
    return real;
    }
}


answer find_max_crossing_subarray(size_t low,size_t mid,size_t high,int *a)
{
    answer real;
    int left_sum=(numeric_limits<int>::min)();int sum=0;
    for(int i=mid;i!=low-1;--i)
    {
        sum=sum+a[i];
        if(sum>left_sum)
        {
            left_sum=sum;
            real.l=i;
        }
    }
    int right_sum=(numeric_limits<int>::min)();sum=0;
    for(int j=mid+1;j!=high+1;++j)
    {
        sum=sum+a[j];
        if(sum>right_sum)
        {
            right_sum=sum;
            real.h=j;
        }
    }
    real.re=left_sum+right_sum;
    return real;
}
