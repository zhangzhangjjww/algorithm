#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define  N 11

int lcs_increase(int* a,int* last,int* b);
void show_solution(int* s,int* a,int ll);



int main()
{
    srand(time(0));
    int a[N];
    for(int i=1;i!=N;++i)
        a[i]= rand()%1000+1;
    int last[N]={0},b[N]={0};
    int L=lcs_increase(a,last,b);
    for(int i=1;i!=N;++i)
        cout<<a[i]<<endl;cout<<endl;
    for(int i=1;i!=N;++i)
        cout<<last[i]<<" "<<b[i]<<endl;
    show_solution(b,a,last[L-1]);
    cout<<endl;
    //cout<<L<<endl;
    return 0;
}

int lcs_increase(int* a,int* last,int* b)
{
    int L=1;last[1]=1;b[1]=1;last[0]=1;b[0]=1;
    for (int i=2;i!=N;i++)//����������last�����ҵ�MAX���������һ��Ԫ���±����������b��������MAX�����С�
    {
        int low=1,high=L-1;

        //if(a[i]>a[last[L==0?0:high]])
       // {//�����ǰԪ�ر�last������Ԫ�ض���������������еĳ��ȼ�һ����βԪ��Ϊ��ǰԪ��nums[i]
       //     last[L++]=i;
      //      b[i]=last[high];//>=0?high:0];
       // }
        if(a[i]>a[last[L==1?1:high]])
        {//�����ǰԪ�ر�last������Ԫ�ض���������������еĳ��ȼ�һ����βԪ��Ϊ��ǰԪ��nums[i]
            last[L++]=i;
            b[i]=last[high];
        }
        else
        {//����ʹ�ö��ַ���last�в��ҵ����ڵ��ڵ�ǰԪ��nums[i]����СԪ��
            while(low<=high)
            {
                int middle=(high+low)/2;
                if(a[i]>a[last[middle]])
                    low=middle+1;
                else
                    high=middle-1;
            }
            //����last�е�Ԫ��ֵ��b�е��±�ֵ��
            last[low]=i;
            b[i]=last[low==1 ? 1 : low-1];
        }
    }
    return L;
}

void show_solution(int* s,int* a,int ll)
{
    if(s[ll]!=ll)
       show_solution(s,a,s[ll]);
    if(ll==1&&a[1]<a[2])
      cout<<a[ll]<<" ";
    if(ll!=1)
        cout<<a[ll]<<" ";
}
