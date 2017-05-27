#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>

using std::cout;
using std::endl;

struct sample//��¼λ�ã�����_k_merge���г�ȡ
{
    int value;
    int position;
} ;

void k_sort(int* a,int n,int k);
void build_max_heap(int* a,int n);
void build_min_heap(sample* a,int n);
void heaplify(int* a,int i,int n);
void heaplify_min(sample* a,int i,int n);//��С�ѻ�
void heap_sort(int* a,int n);
int parent(int i);
int left(int i);
int right(int i);
int exponent(int base,int pow);
void k_merge(int* a,int n,int k);

int main()
{
    srand(time(0));
    const int N=10;
    int a[N];
    for(int i=0;i!=N;++i)
        a[i]=rand()%exponent(N,3);

    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;cout<<endl;
    //build_max_heap(a,N);
    //heap_sort(a,N);
    k_sort(a,N,3);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;cout<<endl;
    k_merge(a,N,3);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;cout<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int parent(int i)
{
    if(i==1)
        return 0;
    return (i+1)/2.0-1.5;
}

int left(int i)
{
    return 2*(i+1)-1;
}

int right(int i)
{
    return 2*(i+1);
}

void heaplify(int* a,int i,int n)
{
    int l=left(i);
    int r=right(i);
    int pos;
    if(l<n&&a[l]>a[i])
    {
        pos=l;}
    else
        pos=i;
    if(r<n&&a[r]>a[pos])
    {
        pos=r;
    }
    if(pos!=i) {
        int tmp=a[i];
        a[i]=a[pos];
        a[pos]=tmp;
        heaplify(a,pos,n);}
}

void build_max_heap(int* a,int n)
{
    for(int i=n/2;i!=-1;--i)
        heaplify(a,i,n);
}

void heaplify_min(sample* a,int i,int n)
{
    int l=left(i);
    int r=right(i);
    int pos;
    if(l<n&&a[l].value<a[i].value)
        pos=l;
    else
        pos=i;
    if(r<n&&a[r].value<a[pos].value)
        pos=r;
    if(i!=pos)
    {
        sample tmp=a[i];
        a[i]=a[pos];
        a[pos]=tmp;
        heaplify_min(a,pos,n);
    }
}

void build_min_heap(sample* a,int n)
{
    for(int i=n/2;i!=-1;--i)
        heaplify_min(a,i,n);
}

void heap_sort(int* a,int n)
{
    int sz=n;
    build_max_heap(a,n);
    for(int i=n-1;i!=0;--i)
    {
        --sz;
        int tmp=a[i];
        a[i]=a[0];
        a[0]=tmp;
        heaplify(a,0,sz);
    }
}

void k_sort(int* a,int n,int k) //���k����
{
    int num=n/k;
    int** p=new int*[k];
    for(int i=0;i!=k;++i)
        p[i]=new int[num];
    for(int i=0;i!=k;++i)
        for(int j=0;j!=num;++j)
        p[i][j]=a[i+k*j];
    for(int i=0;i!=k;++i)
        heap_sort(p[i],num);
    for(int i=0;i!=k;++i)
        for(int j=0;j!=num;++j)
        a[i+k*j]=p[i][j];
    int now=(k)*num; //��n/k��������ʱ�����ڶ����Ԫ�أ�����Ԫ�ز���������ʱ�����������ٴν���������������������θ�ֵ
    while(now<n)
    {
        if((now-k>=0)&&a[now]<a[now-k])
        {
            int tmp=a[now];
            a[now]=a[now-k];
            a[now-k]=tmp;
            for(int i=0;i!=k;++i)
               for(int j=0;j!=num;++j)
                  p[i][j]=a[i+k*j];
            int c=now%num;
            heap_sort(p[c],num);
        }
        ++now;
    }
    for(int i=0;i!=k;++i)
        for(int j=0;j!=num;++j)
        a[i+k*j]=p[i][j];
    for(int i=0;i!=k;++i)
        delete [] p[i];
    delete [] p;
}

void k_merge(int* a,int n,int k) //��һ��k�����������ȫ����,�ȳ�ȡk����������Сֵ��������С�ѣ���ȡ��СԪ�أ��������鲻Ϊ�գ���ȡ�������е���һ��Ԫ��
//���������Ѿ�Ϊ�գ�����Сֵλ�ڶ��У������е�һ��Ԫ����Ϊ���ֵ��Ȼ��ά���ѣ��õ���Сֵ���Դ�����
{
    sample* p=new sample[n];
    for(int i=0;i!=n;++i) {
        p[i].value=a[i];
        p[i].position=i; }
    sample* p2=new sample[k];
    for(int i=0;i!=k;++i) {
        p2[i].value=a[i];
        p2[i].position=i; }
    build_min_heap(p2,k);
    for(int i=0;i!=n;++i)
    {
        a[i]=p2[0].value;
        int pos=p2[0].position+k;
        if(pos<n) {
        p2[0]=p[pos];}
        else
        {
            p2[0].value=std::numeric_limits<int>::max();

        }
        heaplify_min(p2,0,k);
    }
    delete [] p;delete [] p2;
}
