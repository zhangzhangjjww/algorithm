#include<iostream>
#include<limits>
#include<fstream>

using namespace std;

struct matrix_coefficient
{
    int row;
    int line;
};

const int N=7;

int matrix_multiply_bottom_to_up(matrix_coefficient* p,int n,int** tar,int** s);
int matrix_multiply_memo(matrix_coefficient* p,int n,int** tar,int** s);
int matrix_multiply_memo2(matrix_coefficient* p,int i,int j,int** tar,int** s);
void show_solution(int** s,int i,int j);

int main()
{
    matrix_coefficient data[N];
    ifstream is;
    is.open("15.2.txt");
    for(int i=1;i!=N;++i)
    {
        is>>data[i].row>>data[i].line;
    }
    int n=6;
    int** target=new int*[N];
    int** solution=new int*[N];
    for(int i=0;i!=N;++i)
    {
        target[i]=new int[N];
        solution[i]=new int[N];
    }
    for(int i=0;i!=N;++i)
        for(int j=0;j!=N;++j)
        {
            target[i][j]=numeric_limits<int>::max();
            solution[i][j]=0;
        }
    //matrix_multiply_bottom_to_up(data,n,target,solution);
    matrix_multiply_memo(data,n,target,solution);
    for(int i=1;i!=N;++i)
        for(int j=i+1;j!=N;++j)
        {
            cout<<target[i][j]<<" ";
            cout<<"Solution: ";
            show_solution(solution,i,j);
            cout<<endl;
        }
        //cout<<endl;}
   for(int i=0;i!=N;++i)
   {
       delete [] target[i];
       delete [] solution[i];
   }
   delete [] target;delete [] solution;
   // for(int i=1;i!=N;++i)
     //   cout<<data[i].row<<" "<<data[i].line<<endl;
    is.close();
    return 0;
}

int matrix_multiply_memo(matrix_coefficient* p,int n,int** tar,int** s)
{
    for(int i=0;i!=N;++i)
    {
        tar[i][i]=0;
        s[i][i]=1;
    }
    return matrix_multiply_memo2(p,1,n,tar,s);
}

int matrix_multiply_memo2(matrix_coefficient* p,int i,int j,int** tar,int** s)
{
   if(tar[i][j]<numeric_limits<int>::max())
        return tar[i][j];
   else
   {
       int q;
       for(int k=i;k!=j;++k)
       {
           q=matrix_multiply_memo2(p,i,k,tar,s)+matrix_multiply_memo2(p,k+1,j,tar,s)+p[i].row*p[k].line*p[j].line;
           if(q<tar[i][j])
           {
               tar[i][j]=q;
               s[i][j]=k;
           }
       }
       return tar[i][j];
   }
}

int matrix_multiply_bottom_to_up(matrix_coefficient* p,int n,int** tar,int** s)
{
    if(n<=0)
        return 0;
    else
    {
        for(int i=1;i!=N;++i)
        {
            s[i][i]=i;
            tar[i][i]=0;
        }
        for(int l=2;l!=n+1;++l)
        {
            for(int i=1;i!=n+2-l;++i)
            {
                int j=l-1+i;
                int q;
                for(int k=i;k!=j;++k)
                {
                    q=tar[i][k]+tar[k+1][j]+p[i].row*p[k].line*p[j].line;
                    if(q<tar[i][j])
                    {
                        tar[i][j]=q;
                        s[i][j]=k;
                    }
                }
            }
        }
    }
}

void show_solution(int** s,int i,int j)
{
    if(i<j)
    {
        cout<<s[i][j]<<" ";
        show_solution(s,i,s[i][j]);
        show_solution(s,s[i][j]+1,j);
    }
}
