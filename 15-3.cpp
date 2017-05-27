#include<iostream>
#include<limits>
#include<fstream>
#include<cmath>

using namespace std;

const int N=8;

struct data
{
    double x;
    double y;
};

void euclidean_tsp(data* p,double** re,int** s);
double distance(data i,data j);
void show_solution(int** s,data* p);

int main()
{
    data p[N];
    ifstream is;
    is.open("15-3.txt");
    for(int i=1;i!=N;++i)
    {
        is>>p[i].x>>p[i].y;
    }
    for(int i=1;i!=N;++i)
    {
        cout<<p[i].x<<p[i].y;
    }cout<<endl;
    double** result=new double*[N];
    int** solution=new int*[N];
    for(int i=0;i!=N;++i)
    {
        result[i]=new double[N];
        solution[i]=new int[N];
    }
    for(int i=0;i!=N;++i)
    {
        for(int j=0;j!=N;++j)
        {
            result[i][j]=numeric_limits<double>::max();
            solution[i][j]=0;
        }
    }
    euclidean_tsp(p,result,solution);
    for(int i=1;i!=N;++i)
        for(int j=i;j!=N;++j)
        cout<<i<<" "<<j<<" "<<solution[i][j]<<" "<<result[i][j]<<endl;
    show_solution(solution,p);
    is.close();
    for(int i=0;i!=N;++i)
    {
        delete [] result[i];
        delete [] solution[i];
    }
    delete [] result;delete [] solution;
    return 0;
}

double distance(data i,data j)
{
    return sqrt((i.x-j.x)*(i.x-j.x)+(i.y-j.y)*(i.y-j.y));
}

void euclidean_tsp(data* p,double** re,int** s)
{
    re[1][2]=distance(p[1],p[2]);
    for(int j=3;j!=N;++j)
    {
        for(int i=1;i!=j-1;++i)
        {
            re[i][j]=re[i][j-1]+distance(p[j-1],p[j]);
            s[i][j]=j-1;
        }
        double tmp;
        for(int k=1;k!=j-1;++k)
        {
            tmp=re[k][j-1]+distance(p[k],p[j]);
            if(tmp<re[j-1][j])
            {
                re[j-1][j]=tmp;
                s[j-1][j]=k;
            }
        }
    }
    re[N-1][N-1]=re[N-2][N-1]+distance(p[N-2],p[N-1]);
}

void show2(int** s,int i,int j)
{
    if(i<j)
    {
        int k=s[i][j];
        cout<<k<<" ";
        if(k>1)
            show2(s,i,k);
    }
    else
    {
        int k=s[j][i];
        if(k>1)
        {
            show2(s,k,j);
            cout<<k<<" ";
        }
    }
}
void show_solution(int** s,data* p)
{
    cout<<N-1<<" "<<N-2<<" ";
    int r=s[N-2][N-1];
    show2(s,r,N-2);
    cout<<r<<endl;
}
