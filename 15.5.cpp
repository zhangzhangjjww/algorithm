#include<iostream>
#include<cstdlib>
#include<limits>

const int N=7;

using namespace std;

void optimal_bst(double* p,double* q,int n,double** e,double** w,double** root);
void show_solution(double** root,int i,int j);

int main()
{
    //double p[N+1]={0,0.15,0.1,0.05,0.1,0.2};
    //double q[N+1]={0.05,0.1,0.05,0.05,0.05,0.1};
    double p[N+1]={0,0.04,0.06,0.08,0.02,0.1,0.12,0.14};
    double q[N+1]={0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
    double** e=new double*[N+2];
    double** w=new double*[N+2];
    double** root=new double*[N+1];
    for(int i=0;i!=N+2;++i)
    {
        e[i]=new double[N+1];
        w[i]=new double[N+1];
    }
    for(int i=0;i!=N+1;++i)
        root[i]=new double[N+1];
    for(int i=0;i!=N+2;++i)
    {
        for(int j=0;j!=N+1;++j)
        {
            e[i][j]=0;
            w[i][j]=0;
        }
    }
    for(int i=0;i!=N+1;++i)
    {
        for(int j=0;j!=N+1;++j)
        {
            root[i][j]=0;
        }
    }
    optimal_bst(p,q,N+1,e,w,root);
    show_solution(root,1,N);
    cout<<endl;
   /* for(int i=1;i!=N+2;++i)
        for(int j=0;j!=N+1;++j)
        cout<<i<<" "<<j<<" "<<e[i][j]<<endl;*/
    for(int i=0;i!=N+2;++i)
    {
        delete [] e[i];
        delete [] w[i];
    }
    for(int i=0;i!=N+1;++i)
        delete [] root[i];
    delete [] e;delete [] w;delete [] root;
    return 0;
}

void optimal_bst(double* p,double* q,int n,double** e,double** w,double** root)
{
    for(int i=1;i!=n+1;++i)
    {
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for(int l=1;l!=n+1;++l)
    {
        for(int i=1;i!=n-l+1;++i)
        {
            int j=i+l-1;
            e[i][j]=numeric_limits<double>::max();
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int k=i;k!=j+1;++k)
            {
                //cout<<i<<" "<<j<<" "<<k<<endl;
                double tmp=e[i][k-1]+e[k+1][j]+w[i][j];
                if(tmp+0.001<e[i][j])
                {
                    e[i][j]=tmp;
                    root[i][j]=k;
                   // cout<<i<<" "<<j<<" "<<k<<" "<<e[i][j]<<endl;
                }
            }
        }
    }
}

void show_solution(double** root,int i,int j)
{
    if(i<=j)
    {
        cout<<root[i][j]<<endl;
        cout<<"left child of "<<root[i][j]<<" : ";
        if(i==root[i][j])
            cout<<"q["<<i-1<<"] ";
        else
            show_solution(root,i,root[i][j]-1);
        cout<<"right child of "<<root[i][j]<<" : ";
        if(j==root[i][j])
            cout<<"q["<<j<<"] "<<endl;
        else
            show_solution(root,root[i][j]+1,j);
    }
}
