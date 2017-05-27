#include<iostream>
#include<string>
#include<limits>

using namespace std;

int lcs_length_bottom_to_up(string s1,string s2,int** re,int** s);
int lcs_length_bottom_to_up2(string s1,string s2,int** re,int** s);
int lcs_length_memo(string s1,string s2,int** re,int** s);
int lcs_length_memo2(string s1,string s2,int i,int j,int** re,int** s);
void show_solution(int** s,int i,int j,string s1,string s2);

int main()
{
    string s1("0ABCBDAB");
    string s2("0BDCABA");
    int** result=new int*[s1.size()];
    int** solution=new int*[s1.size()];
    for(int i=0;i!=s1.size();++i)
    {
        result[i]=new int[s2.size()];
        solution[i]=new int[s2.size()];
    }
    for(int i=0;i!=s1.size();++i)
        for(int j=0;j!=s2.size();++j)
        {
            result[i][j]=0;
            solution[i][j]=0;
        }
    lcs_length_bottom_to_up(s1,s2,result,solution);
    //lcs_length_memo(s1,s2,result,solution);
    lcs_length_bottom_to_up2(s1,s2,result,solution);
    for(int i=1;i!=s1.size();++i)
    {
        for(int j=1;j!=s2.size();++j)
        {
            cout<<result[i][j]<<" ";
            cout<<"Solution: ";
            show_solution(solution,i,j,s1,s2);
            cout<<endl;
        }
    }
    //cout<<result[1][s2.size()-1]<<" ";
    //cout<<"Solution: ";
    //show_solution(solution,s1.size()-1,s2.size()-1,s1,s2);
    //cout<<endl;
    for(int i=0;i!=s1.size();++i)
    {
        delete [] result[i];
        delete [] solution[i];
    }
    delete [] result; delete [] solution;
    return 0;
}

// 0 corner -1 left 1 up
int lcs_length_bottom_to_up(string s1,string s2,int** re,int** s)
{
    for(int i=1;i!=s1.size();++i)
    {
        int q;
        for(int j=1;j!=s2.size();++j)
        {
            if(s1[i]==s2[j])
            {
                re[i][j]=re[i-1][j-1]+1;
                s[i][j]=0;
            }
            else
            {
                if(re[i][j-1]>=re[i-1][j])
                {
                    re[i][j]=re[i][j-1];
                    s[i][j]=-1;
                }
                else
                {
                    re[i][j]=re[i-1][j];
                    s[i][j]=1;
                }
            }
        }
    }
    return 0;
}
//只使用两行而不会是整个re表
int lcs_length_bottom_to_up2(string s1,string s2,int** re,int** s)
{
    for(int i=1;i!=s1.size();++i)
    {
        int q;
        for(int j=1;j!=s2.size();++j)
        {
            if(s1[i]==s2[j])
            {
                re[i%2][j]=re[(i+1)%2][j-1]+1;
                s[i][j]=0;
            }
            else
            {
                if(re[i%2][j-1]>=re[(1+i)%2][j])
                {
                    re[i%2][j]=re[i%2][j-1];
                    s[i][j]=-1;
                }
                else
                {
                    re[i%2][j]=re[(i+1)%2][j];
                    s[i][j]=1;
                }
            }
        }
    }
    return 0;
}
//备忘法不能给出所有的公共子列
int lcs_length_memo(string s1,string s2,int** re,int**s)
{
    for(int i=0;i!=s1.size();++i)
    {
        for(int j=0;j!=s2.size();++j)
            re[i][j]=numeric_limits<int>::min();
    }
    for(int i=0;i!=s1.size();++i)
        re[i][0]=0;
    for(int j=0;j!=s2.size();++j)
        re[0][j]=0;
    return lcs_length_memo2(s1,s2,s1.size()-1,s2.size()-1,re,s);
}

int lcs_length_memo2(string s1,string s2,int i,int j,int** re,int** s)
{
    if(i==0||j==0)
        return re[i][j];
    if(re[i][j]>numeric_limits<int>::min())
        return re[i][j];
    else
    {
        if(s1[i]==s2[j])
        {
            re[i][j]=lcs_length_memo2(s1,s2,i-1,j-1,re,s)+1;
            s[i][j]=0;
            return re[i][j];
        }
        else
        {
            int tmp1=lcs_length_memo2(s1,s2,i,j-1,re,s);
            int tmp2=lcs_length_memo2(s1,s2,i-1,j,re,s);
            if(tmp1>=tmp2)
            {
                re[i][j]=tmp1;
                s[i][j]=-1;
            }
            else
            {
                re[i][j]=tmp2;
                s[i][j]=1;
            }
            return re[i][j];
        }
    }
}
void show_solution(int** s,int i,int j,string s1,string s2)
{
    if(i==0||j==0)
        return;
    if(s[i][j]==0){
        cout<<s1[i];
        show_solution(s,i-1,j-1,s1,s2);}
    else
    {
        if(s[i][j]==-1)
            show_solution(s,i,j-1,s1,s2);
        else
            show_solution(s,i-1,j,s1,s2);
    }
}
