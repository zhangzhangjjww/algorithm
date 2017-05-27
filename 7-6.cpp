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
//�������ȷ������������ľ������ص�
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
//ģ�������������һ��������ֵ�ԣ����Զ���һ���ṹ��
struct node
{
    int a;
    int b;
};
//���������ṹ��
void swap(node& a,node& b)
{
    node temp=a;
    a=b;
    b=temp;
}
//���ֳ����ε�partition�������������С����Ԫ�����ұ��Ǵ�����Ԫ���м��ǵ�����Ԫ��
//������[l,r]��ĳ����Ϊ��׼���ֳ�[l,i]<[i+1,j-1]<[j,r]��������
node partition(node a[],int l,int r)
{
    //ѡ���һ��Ԫ��Ϊ��Ԫ��retΪ���滮�ֵ�Ľṹ��
    node x=a[r],ret;
    int i=l-1;//����С����
    int j=r+1;//���ٴ�����
    int k=l;//������������
    while(k<j && k<=r)
    {
        if(a[k].b<x.a)   //���С����Ԫ��������ǰ��
        {
            ++i;
            swap(a[i],a[k]);
            ++k;
        }
        else if(a[k].a>x.a) ////������ڣ�����������
        {
            j--;
            swap(a[j],a[k]);//���ﲻ��k++����Ϊ����������Ԫ��Ҳ���ܴ�����Ԫ
        }
        else
        {//�����������ص���������ȣ�ȡ�����ص��Ĳ�����Ϊ��׼����������֣�һ��ʼ��׼����Ƚϴ󣬻��ֵ����棬��׼���佥����С
            //���ֵ����Ľ������[i,j]����i�������С���䣬j�ĺ���Ǵ����䣬��[i,j]��ʣ�������ص��Ĳ��֣�����ȵĲ���
            //�������ǿ�������ı��֣�������ÿ����partitionһ�Σ�����ȷ��һ����㣬ʹ����ߵ���С����㣬�ұߵ����������
            //�����ÿ����partitionһ�Σ�����ȷ��һ������ȡ����䣬ʹ����ߵĶ�С�ڣ�ƫ�������ϣ�������䣬�ұߴ����������
            //���ſ���ȷ��һ��׼ȷ���У���ģ�����������ȷ��һ�����ܵ���������
            x.a=max(a[k].a,x.a);
            x.b=min(a[k].b,x.b); //�����ȣ�������������Ҫ��ȡ������
            ++k;
        }
    }
    ret.a=i;
    ret.b=j;
    return ret;//ret�ݴ�����
}

void Fuzzy_sort(node a[],int l,int r)
{
    if(l<r)
    {
        node mid=partition(a,l,r);//mid����ָ��[i,j]
        //�м��ص����ֲ�����ֻ������ͷ����
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
        if(c[i]>a[i].b)//��������Ϊ��i������ȵ�i+1������󣬼�i.a>(i+1).b
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
    cout<<"�����������n:";
    cin>>n;
    cout<<"�����������"<<n<<"�����������յ�a,b:"<<endl;
    for(int i=0;i<n;i++)//������Ч�����
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
    cout<<"ģ������Ľ�����£�"<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i].a<<" "<<a[i].b<<endl;
    cout<<"���ܴ��ڵ��������£�"<<endl;
    if(print_possible_sort(a,n))
    {
        cout<<endl<<"�ɹ��ҵ�һ���������������С�"<<endl;
    }
    else
    {
        cout<<"�㷨ʧ�ܣ�"<<endl;
    }
    return 0;
} */
