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
    for (int i=2;i!=N;i++)//所以我们用last数组找到MAX子序列最后一个元素下标后，利用数组b回溯整个MAX子序列。
    {
        int low=1,high=L-1;

        //if(a[i]>a[last[L==0?0:high]])
       // {//如果当前元素比last中所有元素都大则最长递增子序列的长度加一，其尾元素为当前元素nums[i]
       //     last[L++]=i;
      //      b[i]=last[high];//>=0?high:0];
       // }
        if(a[i]>a[last[L==1?1:high]])
        {//如果当前元素比last中所有元素都大则最长递增子序列的长度加一，其尾元素为当前元素nums[i]
            last[L++]=i;
            b[i]=last[high];
        }
        else
        {//否则使用二分法在last中查找到大于等于当前元素nums[i]的最小元素
            while(low<=high)
            {
                int middle=(high+low)/2;
                if(a[i]>a[last[middle]])
                    low=middle+1;
                else
                    high=middle-1;
            }
            //更新last中的元素值和b中的下标值。
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
