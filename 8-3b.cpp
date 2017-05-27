#include<cstring>
#include<iostream>

using std::endl;
using std::cout;
using std::cin;
void count_sort(char a[][20],int n,char b[][20]);
bool test(char a[][20],int n);
int main()
{
    char p[10][20],p1[10][20];
    for(int i=0;i!=10;++i)
        cin>>p[i];
    for(int i=0;i!=10;++i)
        for(int j=0;j!=10;++j)
        p1[i][j]=p[i][j];
    count_sort(p,10,p1);
    for(int i=0;i!=10;++i)
        cout<<p[i]<<endl;
    return 0;
}

void count_sort(char a[][20],int n,char b[][20])
{
    if(test(b,n)) {
    char* tmp=new char[n];//用于抽取第一个元素
    for(int i=0;i!=n;++i)
        if(strlen(b[i])!=0)
            tmp[i]=b[i][0];
        else
            tmp[i]='\0';
    int c[54];//排序计数，此处只考虑了26个大小写字母外加一个空字符
    for(int i=0;i!=54;++i)
        c[i]=0;
    for(int i=0;i!=n;++i)
    {
        if('a'<=tmp[i]&&tmp[i]<='z')
            c[tmp[i]-'a'+27]++;
        if('A'<=tmp[i]&&tmp[i]<='Z')
            c[tmp[i]-'A'+1]++;
        if(tmp[i]=='\0')
            c[0]++;
    }
    for(int i=1;i!=54;++i)
        c[i]=c[i]+c[i-1];
    char p[10][20];
    for(int i=0;i!=10;++i)
        for(int j=0;j!=20;++j)
        p[i][j]=a[i][j];
    for(int i=n-1;i!=-1;--i)
    {
        int key=tmp[i];
        if(tmp[i]<='z'&&tmp[i]>='a')
            key=tmp[i]-'a'+27;
        if(tmp[i]<='Z'&&tmp[i]>='A')
            key=tmp[i]-'A'+1;
        if(tmp[i]=='\0')
            key=0;
        for(int j=0;j!=20;++j)
        p[c[key]-1][j]=a[i][j];
        --c[key];
    }
    for(int i=0;i!=n;++i)
        for(int j=0;j!=20;++j)
        a[i][j]=p[i][j];
    char next[10][20];
    for(int i=0;i!=10;++i)
        for(int j=0;j!=20;++j)
        next[i][j]='\0';
    for(int i=0;i!=10;++i)
        for(int j=0;j!=20-1;++j)
        next[i][j]=a[i][j+1];
    delete [] tmp;
    count_sort(a,n,next);
    }
}

bool test(char c[][20],int n)
{
    for(int i=0;i!=n;++i)
        if(c[i][0]!='\0')
        return true;
    else
        return false;
}
