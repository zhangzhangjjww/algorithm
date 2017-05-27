#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<stdexcept>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

int exponent(int base,int pow);
int random(int &n);
int count(int n);
void diff_sort(vector<int>::iterator be,vector<int>::iterator en,int n);
void radix_sort(vector<int>::iterator be,vector<int>::iterator en,int d);
void count_sort(vector<int>::iterator be,vector<int>::iterator en,int d);
int get_number_in_position(int num,int d);

int main()
{
    srand(time(0));
    vector<int> v;int n;
    cout<<"Enter the total number digits:";
    cin>>n;
    int tmp=n;
    if(n<=0)
        std::logic_error("must be a positive number");
    while(n!=0) {
        v.push_back(random(n));}
    for(vector<int>::size_type i=0;i!=v.size();++i)
        cout<<v[i]<<endl;
    cout<<endl;
    diff_sort(v.begin(),v.end(),tmp);
    for(vector<int>::size_type i=0;i!=v.size();++i)
        cout<<v[i]<<endl;
    return 0;
}

int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}

int random(int & n)
{
    int base=10;
    int pow;
    next2:pow=rand()%3+1;
    if(pow>n)
        goto next2;
    int a=exponent(base,pow);
    int result;
    next:result=rand()%a;
    if(result==0)
        goto next;
    int cou=count(result);
    n=n-cou;
    return result;
}

int count(int n)
{
    int re=0;
    while(n)
    {
        n=n/10;
        ++re;
    }
    return re;
}

void diff_sort(vector<int>::iterator be,vector<int>::iterator en,int n)
{
    vector<int>* p=new vector<int>[n];
    for(vector<int>::iterator i=be;i!=en;++i)
        p[count(*i)-1].push_back(*i);
    for(int i=0;i!=n;++i)
        if(!p[i].empty())
          radix_sort(p[i].begin(),p[i].end(),i+1);
    vector<int> v;
    for(int i=0;i!=n;++i)
        if(!p[i].empty())
        {
            for(vector<int>::size_type j=0;j!=p[i].size();++j)
                v.push_back(p[i][j]);
        }
    vector<int>::iterator j=v.begin();
    for(vector<int>::iterator i=be;i!=en;++i,++j)
        *i=*j;
}

void radix_sort(vector<int>::iterator be,vector<int>::iterator en,int d)
{
    for(int i=1;i!=d+1;++i)
        count_sort(be,en,i);
}

void count_sort(vector<int>::iterator be,vector<int>::iterator en,int d)
{
    int n=en-be;
    int* p=new int[n]; //用于保存从vector抽取的第d位的数
    vector<int>::iterator j=be;
    for(int i=0;i!=n;++i,++j)
        p[i]=get_number_in_position(*j,d);
    int* p2=new int[10];//基于十进制排序，用于获得位置
    for(int i=0;i!=10;++i)
        p2[i]=0;
    for(int i=0;i!=n;++i)
        p2[p[i]]=p2[p[i]]+1;
    for(int i=1;i!=10;++i)
        p2[i]=p2[i]+p2[i-1];
    int* p3=new int[n];//用于存放排序过的元素
    j=en-1;
    for(int i=n-1;i!=-1;--i,--j)
    {
        p3[p2[p[i]]-1]=*j;
        p2[p[i]]--;
    }
    j=be;
    for(int i=0;i!=n;++i,++j)
        *j=p3[i];
    delete [] p;delete [] p2;delete [] p3;
}

int get_number_in_position(int n,int d)
{
    int base=10;
    int re=n/exponent(base,d);
    re=n-re*exponent(base,d);
    re=re/exponent(base,d-1);
    return re;
}
