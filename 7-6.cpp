#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

struct node
{
    int begin;
    int end;
};
//程序的正确性依赖于区间的尽量不重叠
void swap(node* a,int i,int j);
node partition(node* a,int p,int r);
int random(int a,int b);
node random_partition(node* a,int p,int r);
void quick_sort(node* a,int p,int r);

int main()
{
    srand(time(0));
    const int N=10;
    node a[N];
    for(int i=0;i!=N;++i)
        cin>>a[i].begin>>a[i].end;
    quick_sort(a,0,N-1);
    for(int i=0;i!=N;++i)
        cout<<a[i].begin<<endl;
    return 0;
}

void swap(node* a,int i,int j)
{
    node tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
}

int random(int a,int b)
{
    return rand()%(b-a+1)+a;
}

node partition(node* a,int p,int r)
{
        int i=p-1,j=r+1,k=p;
        node key=a[r];
        while(k<j&&k<=r)
        {
            if(a[k].end<key.begin)
            {
                ++i;
                swap(a,i,k);
                ++k;
            }
            else
                if(a[k].begin>key.begin)
                {
                    --j;
                    swap(a,k,j);
                }
                else
                {
                    key.begin=a[k].begin>key.begin?a[k].begin:key.begin;
                    key.end=a[k].end<key.end?a[k].end:key.end;
                    ++k;
                }
        }
        node re;
        re.begin=i;re.end=j;
       // cout<<re.begin<<" "<<re.end<<endl;
        return re;
}


node random_partition(node* a,int p,int r)
{
    int i=random(p,r);
    swap(a,i,r);
    return partition(a,p,r);
}

void quick_sort(node* a,int p,int r)
{
    if(p<r)
    {
        node q=partition(a,p,r);
        quick_sort(a,p,q.begin);
        quick_sort(a,q.end,r);
    }
}

/*
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
//模糊排序的输入是一个区间数值对，所以定义一个结构体
struct node
{
    int a;
    int b;
};
//交换两个结构体
void swap(node& a,node& b)
{
    node temp=a;
    a=b;
    b=temp;
}
//划分成三段的partition函数，最左边是小于主元，最右边是大于主元，中间是等于主元的
//将区间[l,r]以某区间为基准，分成[l,i]<[i+1,j-1]<[j,r]三个区间
node partition(node a[],int l,int r)
{
    //选最后一个元素为主元，ret为保存划分点的结构体
    node x=a[r],ret;
    int i=l-1;//跟踪小区间
    int j=r+1;//跟踪大区间
    int k=l;//遍历整个数组
    while(k<j && k<=r)
    {
        if(a[k].b<x.a)   //如果小于主元，交换到前面
        {
            ++i;
            swap(a[i],a[k]);
            ++k;
        }
        else if(a[k].a>x.a) ////如果大于，交换到后面
        {
            j--;
            swap(a[j],a[k]);//这里不能k++，因为交换过来的元素也可能大于主元
        }
        else
        {//两个区间有重叠，视作相等，取它们重叠的部分作为基准区间继续划分，一开始基准区间比较大，划分到后面，基准区间渐渐变小
            //划分到最后的结果就是[i,j]，则i的左边是小区间，j的后边是大区间，而[i,j]是剩余区间重叠的部分，即相等的部分
            //本质上是快速排序的变种，快排是每调用partition一次，可以确定一个枢点，使其左边的数小于枢点，右边的数大于枢点
            //而这个每调用partition一次，可以确定一个“相等”区间，使其左边的都小于（偏序意义上）枢点区间，右边大于枢点区间
            //快排可以确定一个准确序列，而模糊化排序可以确定一个可能的区间排序
            x.a=max(a[k].a,x.a);
            x.b=min(a[k].b,x.b); //如果相等，不交换，但是要提取公因子
            ++k;
        }
    }
    ret.a=i;
    ret.b=j;
    return ret;//ret暂存作用
}

void Fuzzy_sort(node a[],int l,int r)
{
    if(l<r)
    {
        node mid=partition(a,l,r);//mid保存分割点[i,j]
        //中间重叠部分不处理，只处理两头部分
        Fuzzy_sort(a,l,mid.a);
        Fuzzy_sort(a,mid.b,r);
    }
}
bool print_possible_sort(node a[],int n)
{
    int* c=new int[n];
    c[0]=a[0].a;
    cout<<c[0]<<' ';
    for(int i=1;i<n;i++)
    {
        c[i]=max(a[i].a,c[i-1]);
        if(c[i]>a[i].b)//出错的情况为第i个区间比第i+1个区间大，即i.a>(i+1).b
        {
            cout<<"error!"<<endl;
            return false;
        }
        cout<<c[i]<<' ';
    }
    delete []c;
    return true;
}
int main()
{
    srand((unsigned)time(0));
    node a[10000];
    int n=0;
    cout<<"输入区间个数n:";
    cin>>n;
    cout<<"下面随机输入"<<n<<"个区间的起点终点a,b:"<<endl;
    for(int i=0;i<n;i++)//产生有效区间对
    {
        a[i].a=rand()%1000;
        a[i].b=rand()%1000;
        if(a[i].a>a[i].b)
        {
            swap(a[i].b,a[i].a);
        }
        cout<<a[i].a<<" "<<a[i].b<<endl;
    }
    Fuzzy_sort(a,0,n-1);
    cout<<"模糊排序的结果如下："<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i].a<<" "<<a[i].b<<endl;
    cout<<"可能存在的排列如下："<<endl;
    if(print_possible_sort(a,n))
    {
        cout<<endl<<"成功找到一个满足条件的排列。"<<endl;
    }
    else
    {
        cout<<"算法失败！"<<endl;
    }
    return 0;
} */
