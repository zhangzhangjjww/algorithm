#include<iostream>
#include<limits>

using namespace std;

const int N=11;

int simple_way_cut_rod(int* p,int n,int* tar);
int rod_cut_memo(int* p,int n,int *tar,int* s);
int rod_cut_bottom_to_up(int* p,int n,int* tar,int* solution);
void show_solution(int* s,int n);

int main()
{
    int price[N]={0,1,5,8,9,10,17,17,20,24,30};
    int n;
    cout<<"Please enter the length of the rod:\n";
    //cin>>n;
    n=10;
    int* target=new int[n+1];
    for(int i=0;i!=n+1;++i)
        target[i]=numeric_limits<int>::min();
    int* solution=new int[n+1];
    for(int i=0;i!=n+1;++i)
        solution[i]=0;
   // simple_way_cut_rod(price,n,target);
    rod_cut_memo(price,n,target,solution);
    //rod_cut_bottom_to_up(price,n,target,solution);
    for(int i=1;i!=n+1;++i) {
        cout<<i<<" "<<target[i]<<endl;
        show_solution(solution,i); }
    delete [] target;
    return 0;
}

int simple_way_cut_rod(int* p,int n,int* tar)
{
    if(n<=0)
        return 0;
    else
    {
        int q;
        for(int i=1;i!=n+1;++i)
        {
            q=p[i]+simple_way_cut_rod(p,n-i,tar);
            if(q>tar[n])
                tar[n]=q;
        }
        return tar[n];
    }
}

int rod_cut_memo(int* p,int n,int* tar,int* s)
{
    if(n<=0)
        return 0;
    else
    {
        if(tar[n]>numeric_limits<int>::min())
            return tar[n];
        else
        {
            int q;
            for(int i=1;i!=n+1;++i)
            {
                q=p[i]+rod_cut_memo(p,n-i,tar,s);
                if(q>tar[n]) {
                    tar[n]=q;
                    s[n]=i;}
            }
            return tar[n];
        }
    }
}

int rod_cut_bottom_to_up(int* p,int n,int* tar,int* s)
{
    tar[0]=0;
    int c=1;//考虑每次切割收取费用
    for(int j=1;j!=n+1;++j)
    {
        int q;
        for(int i=1;i!=j+1;++i)
        {
            //q=p[i]+tar[j-i];
            c=(j==i)?0:2;
            q=p[i]+tar[j-i]-c;
            if(q>tar[j])
            {
                tar[j]=q;
                s[j]=i;
            }
        }
    }
    return tar[n];
}

void show_solution(int* s,int n)
{
    cout<<"Solution:";
    while(n>0)
    {
        cout<<s[n]<<" ";
        n=n-s[n];
    }
    cout<<endl;
}
