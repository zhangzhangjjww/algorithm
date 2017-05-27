#include<iostream>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::endl;

const int N=10;
const int K=100;

void count_sort(int* a,int n,int k);
bool test(int* a,int n);

int main()
{
    srand(time(0));
    int a[N];//={6,0,2,0,1,3,4,6,1,3,2};
    for(int i=0;i!=N;++i)
       a[i]=rand()%100;
    count_sort(a,N,K);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    return 0;
}

void count_sort(int* a,int n,int k) //����ԭַ���򣬶������ռ�3*k+1��һ�����鱣��λ�ã���һ�����鱣������ĳֵԪ�صĸ����������һλ��ʼ���ж�a[i]�Ƿ���λ���ϣ������򽻻�����ֵ��Ӧ�����һ
//��ʾ����һ���������Դ����ƿɵý��������������ר��������������ظ�Ԫ�ص����
{
    int* p1=new int[k+1];
    int* p2=new int[k+1];
    int* p3=new int[k+1];
    for(int i=0;i!=k+1;++i)
    {
        p1[i]=0;
        p2[i]=0;
    }
    for(int i=0;i!=n;++i)
        p1[a[i]]=p1[a[i]]+1;
    p2[0]=p1[0];
    for(int i=1;i!=k+1;++i)
        p2[i]=p1[i]+p2[i-1];
    for(int i=0;i!=k+1;++i)
        p3[i]=p2[i];
    for(int i=n-1;i!=-1;--i)
    {
        if(p1[a[i]]!=0)//
        {
            while((p3[a[i]]-1)!=i) //��������������ÿ��ж��ظ�Ԫ�أ������������ѭ��������
            {
                int tmp=a[i];
                a[i]=a[p2[tmp]-1];
                a[p2[tmp]-1]=tmp;
                --p1[tmp];
                --p2[tmp];
                //if(!test(p1,k+1)) return;//�����Ƿ�����Ԫ�ض�����λ������������򷵻ء�
            }
            --p1[a[i]];
            --p2[a[i]];
            --p3[a[i]];
            //if(!test(p1,k+1)) return;  //����жϺ��񲢲���Ҫ
        }
        else
            continue;
    }
    delete [] p1;delete [] p2;
    return;
}

bool test(int* a,int n)
{
    for(int i=0;i!=n;++i)
        if(a[i]!=0)
        return true;
    return false;
}
