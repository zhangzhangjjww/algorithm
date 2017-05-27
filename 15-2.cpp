#include<iostream>
#include<limits>
#include<string>
#include<vector>

using namespace std;

void lcs_palondrome(string s,int** re,int** so);
void show_solution(string s,int** so,int i,int j);


int main()
{
    string s;
    cout<<"Please enter s string:";
    cin>>s;
    s="0"+s;
    int** result=new int*[s.size()];
    int** solution=new int*[s.size()];
    for(int i=0;i!=s.size();++i)
    {
        result[i]=new int[s.size()];
        solution[i]=new int[s.size()];
    }
    for(int i=0;i!=s.size();++i)
    {
        for(int j=0;j!=s.size();++j)
        {
            result[i][j]=0;
            solution[i][j]=0;
        }
    }
    lcs_palondrome(s,result,solution);
   /* for(int i=1;i!=s.size();++i)
    {
        for(int j=1;j!=s.size();++j)
            //cout<<i<<" "<<j<<" "<<result[i][j]<<endl;
            cout<<result[i][j]<<" ";
        cout<<endl;
    }*/
    show_solution(s,solution,1,s.size()-1);
    cout<<endl;
    return 0;
}

void lcs_palondrome(string s,int** re,int** so)
{
    for(int i=1;i!=s.size();++i) {
        re[i][i]=1;
        so[i][i]=1;}
    for(int j=2;j!=s.size();++j)
    {
        int q;
        for(int i=j-1;i!=0;--i)
        {
            if(s[i]==s[j])
            {
                re[i][j]=re[i+1][j-1]+1;
                so[i][j]=1;
            }
            else
            {
                if(re[i][j-1]>=re[i+1][j])
                {
                    re[i][j]=re[i][j-1];
                    so[i][j]=2;
                }
                else
                {
                    re[i][j]=re[i+1][j];
                    so[i][j]=3;
                }
            }
        }
    }
}

void show_solution(string s,int** so,int i,int j)
{
    vector<char> sss1,sss2;
    while(so[i][j]!=0)
    {
        if(so[i][j]==1)
        {
            if(i==j&&s[i-1]==s[i+1])
                sss1.push_back(s[i]);
            if(i!=j)
                sss1.push_back(s[i]);
            if(i!=j)
                sss2.push_back(s[j]);
            i++;j--;
        }
        else
        {
            if(so[i][j]==2)
            {
                --j;
            }
            else
            {
                ++i;
            }
        }
    }
    for(int k=sss2.size()-1;k!=-1;--k)
        sss1.push_back(sss2[k]);
    for(int k=0;k!=sss1.size();++k)
        cout<<sss1[k];
    cout<<endl;
}
