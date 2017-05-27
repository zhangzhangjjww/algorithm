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

void count_sort(int* a,int n,int k) //采用原址排序，额外分配空间3*k+1，一个数组保留位置，另一个数组保留等于某值元素的个数，从最后一位开始，判断a[i]是否在位置上，不在则交换，该值对应数组减一
//表示已有一个已排序，以此类推可得结果，第三个数组专门用来处理存在重复元素的情况
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
            while((p3[a[i]]-1)!=i) //第三个数组的作用可判断重复元素，否则会陷入死循环，出错
            {
                int tmp=a[i];
                a[i]=a[p2[tmp]-1];
                a[p2[tmp]-1]=tmp;
                --p1[tmp];
                --p2[tmp];
                //if(!test(p1,k+1)) return;//测试是否所有元素都已排位，如果成立，则返回。
            }
            --p1[a[i]];
            --p2[a[i]];
            --p3[a[i]];
            //if(!test(p1,k+1)) return;  //这个判断好像并不需要
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
