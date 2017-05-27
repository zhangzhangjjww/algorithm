#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

struct node
{
    int fir;
    int sec;
};

void quick_sort(int* a,int p,int r);
void quick_sort2(int* a,int p,int r);//采用Hoare_partition划分
void quick_sort3(int* a,int p,int r);//对于数组中存在相同元素时的快排，将数组分为3个部分，大于等于小于
void tail_recursive_quick_sort(int* a,int p,int r);
int partition(int*a,int p,int r);
node partition2(int* a,int p,int r);//for the same elements
int random(int a,int b);
int random_partition(int* a,int p,int r);
node random_partition2(int* a,int p,int r);//数组中存在相同的元素,没做出来
int random_partition3(int* a,int p,int r); //随机3个数取中位数作为主元
int middle(int x1,int x2,int x3);
int Hoare_partition(int* a,int p,int r);
bool test(int* a,int p,node no,int r); //测试两个子数组是否元素互不相同

int main()
{
    srand(time(0));
    int a[]={13,19,9,5,8,8,8,8,21,2,6,11};
    tail_recursive_quick_sort(a,0,11);
    for(int i=0;i!=12;++i)
        cout<<a[i]<<endl;
    return 0;
}

void quick_sort(int* a,int p,int r)
{
    if(p<r)
    {
        int q=random_partition3(a,p,r);
        quick_sort(a,p,q-1);
        quick_sort(a,q+1,r);
    }
}

void tail_recursive_quick_sort(int* a,int p,int r)
{
    while(p<r)
    {
        int q=random_partition(a,p,r);
        tail_recursive_quick_sort(a,p,q-1);
        p=q+1;
    }
}

void quick_sort2(int* a,int p,int r)
{
    if(p<r)
    {
        int q=Hoare_partition(a,p,r);
        quick_sort(a,p,q);
        quick_sort(a,q+1,r);
    }
}

void quick_sort3(int* a,int p,int r)
{
    if(p<r)
    {
        next:node no=partition2(a,p,r);
        quick_sort3(a,p,no.fir-1);
        quick_sort3(a,no.sec+1,r);
    }
}

int partition(int* a,int p,int r)
{
    int key=a[r];
    int i=p-1;int j=p;
    for(;j!=r;++j)
    {
        if(a[j]<=key)
        {
            ++i;
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    }
    int tmp2=a[i+1];
    a[i+1]=a[r];
    a[r]=tmp2;
    return i+1;
}

node partition2(int* a,int p,int r)
{
    node no;
    int i=p-1,key=a[r];
    for(int j=p;j!=r;++j)
        if(a[j]<key)
        {
            ++i;
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    int tmp2=a[i+1];
    a[i+1]=a[r];
    a[r]=tmp2;
    no.fir=i+1;int pos=++i;
    int k=r+1;
    for(int j=pos+1;j!=r+1;++j)
        if(a[j]>key)
        {
            --k;
            int tmp3=a[j];
            a[j]=a[k];
            a[k]=tmp3;
        }
    no.sec=k-1;
    return no;
}

int random(int a,int b)
{
    return rand()%(b-a+1)+a;
}

int random_partition(int * a,int p,int r)
{
    int i=random(p,r);
    int tmp=a[r];
    a[r]=a[i];
    a[i]=tmp;
    return partition(a,p,r);
}

node random_partition2(int* a,int p,int r)
{
    int i=random(p,r);
    int tmp=a[i];
    a[i]=a[r];
    a[r]=tmp;
    return partition2(a,p,r);
}

int random_partition3(int* a,int p,int r)
{
    int x1=random(p,r),x2=random(p,r),x3=random(p,r);
    int key=middle(x1,x2,x3);
    int tmp=a[key];
    a[key]=a[r];
    a[r]=tmp;
    return partition(a,p,r);
}

int middle(int x1,int x2,int x3)
{
    if((x1<=x2&&x2<=x3)||(x3<=x2&x2<=x1))
        return x2;
    if((x2<=x1&&x1<=x3)||(x3<=x1&x1<=x2))
        return x1;
    if((x1<=x3&&x3<=x2)||(x2<=x3&x3<=x1))
        return x3;
}

int Hoare_partition(int* a,int p,int r)
{
    int x=a[p];
    int i=p-1,j=r+1;
    while(1)
    {
        do
            --j;
        while(a[j]>x);
        do
            ++i;
        while(a[i]<x);
        if(i<j)
        {
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
        else
            return j;
    }
}
