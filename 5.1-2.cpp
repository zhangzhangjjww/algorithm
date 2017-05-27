#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int random(int a,int b);
int random();

int main()
{
    srand(time(0));
    int a,b;
    cout<<"Enter two number:"<<endl;
    cin>>a>>b;
    for(int i=0;i!=10;++i)
        cout<<i+1<<" "<<random(a,b)<<endl;
    return 0;
}

int random()
{
    return rand()%2;
}

int random(int a,int b)
{
    int c=(a+b)/2;int re;
    if(a==b)
        return re=a;
    else
    {
        if(random())
            re=random(c,b);
        else
            re=random(a,c);
        return re;
    }
}
