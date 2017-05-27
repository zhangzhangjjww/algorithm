#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int random();
int biased_random();

int main()
{
    srand(time(0));
    for(int i=0;i!=10;++i)
        cout<<random()<<endl;
    return 0;
}

int biased_random()
{
    double p=0.3;
    double chance;
    chance=(rand()%11)/10.0;
    if(chance<p)
        return 1;
    else
        return 0;
}

int random()
{
    int x,y;
    do
    {
        x=biased_random();
        y=biased_random();
    }while(x==y);
    return x;
}
