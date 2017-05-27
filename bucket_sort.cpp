#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<iterator>

using std::cout;
using std::endl;
using std::vector;

void bucket_sort(double* a,int n);
void insert_sort(vector<double>::iterator a1,vector<double>::iterator b1);//��׼����������������ʽ���ݣ���ʹ�õ�����

const int N=10;

int main()
{
    srand(time(0));
    double a[N];
    for(int i=0;i!=N;++i)
    {
        double tmp=rand()%100;
        a[i]=tmp/100.0;
    }
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    vector<double> b(N);
    for(int i=0;i!=N;++i)
        b[i]=N-i;
    cout<<endl;
    bucket_sort(a,N);
    for(int i=0;i!=N;++i)
        cout<<a[i]<<endl;
    return 0;
}

void bucket_sort(double* a,int n)
{
    vector<double>* p=new vector<double>[n];
    for(int i=0;i!=n;++i)
    {
        int j=n*a[i]/1;
        p[j].push_back(a[i]);
    }
    for(int i=0;i!=n;++i)
        if(!p[i].empty()) //�����ж������������
        insert_sort(p[i].begin(),p[i].end());
    vector<double> tmp;
    for(int i=0;i!=n;++i)
    {
        if(p[i].empty())
            continue;
        else
        {
            for(vector<double>::size_type j=0;j!=p[i].size();++j)
                tmp.push_back(p[i][j]);
        }
    }
    delete [] p;
    for(int i=0;i!=n;++i)
        a[i]=tmp[i];
}

void insert_sort(vector<double>::iterator a,vector<double>::iterator b)
{
    for(vector<double>::iterator i=a+1;i!=b;++i)//���Ϊ�գ��˴�Խ�����
    {
        double key=*i;
        vector<double>::iterator j=i-1;
        while(j!=a)
        {
            if(*j>key)
            {
                *(j+1)=*j;
                --j;
            }
            else
                break;
        }
        *(j+1)=key;
        if(*(j+1)<*a) //���ڵ���������ȡ��ֵ��������ԭ���Ĳ���������ȶ�����һ��
        {
            double tmp=*a;
            *a=*(j+1);
            *(j+1)=tmp;
        }

    }
}
