#include"Young_matrix.h"
#include<limits>
#include<iostream>
#include<stdexcept>
void Young_matrix::destroy()
{
    for(int i=0;i!=row;++i)
        delete [] p[i];
    delete [] p;
}

Young_matrix::Young_matrix(int* a,int n,int r,int l):p(0),row(r),line(l)
{
    p=new int*[row];
    for(int i=0;i!=row;++i)
        p[i]=new int[line];
    int sum=0;
    for(int i=0;i!=row;++i)
        for(int j=0;j!=line;++j)
        {
            if(sum<n)
                p[i][j]=a[sum];
            else
                p[i][j]=(std::numeric_limits<int>::max)();
            ++sum;
        }
    pos.pr()=(n)/row;
    pos.pl()=(n)%row;
}

Young_matrix::Young_matrix(const Young_matrix& m):p(0),row(m.row),line(m.line)
{
    p=new int*[row];
    for(int i=0;i!=row;++i)
        p[i]=new int[line];
    for(int i=0;i!=row;++i)
        for(int j=0;j!=line;++j)
          p[i][j]=m.p[i][j];
    pos.pr()=m.pos.pr();pos.pl()=m.pos.pl();
}

Young_matrix& Young_matrix::operator=(const Young_matrix& m)
{
    destroy();
    row=m.row;
    line=m.line;
    pos=m.pos;
    p=new int*[row];
    for(int i=0;i!=row;++i)
        p[i]=new int[line];
    for(int i=0;i!=row;++i)
        for(int j=0;j!=line;++j)
        p[i][j]=m.p[i][j];
    return *this;
}

int Young_matrix::Young_extract_min()
{
    int key=p[0][0];
   // p[row-1][line-1]=p[0][0];
    p[0][0]=p[row-1][line-1];
    p[row-1][line-1]=(std::numeric_limits<int>::max)();
    Position pp(0,0);
    Young_min_heapify(pp);
    int sum=pos.pr()*row+pos.pl()-1;
    pos.pr()=sum/row;
    pos.pl()=sum%row;
    return key;
}

void Young_matrix::Young_min_heapify(Position i)
{
    Position ppp=i;
    if(i.pr()+1<row&&(p[i.pr()][i.pl()]<=p[i.pr()+1][i.pl()]))
        ppp=i;
    else
        ppp=Position(i.pr()+1,i.pl());
    if(i.pl()+1<line&&p[i.pr()][i.pl()+1]<p[ppp.pr()][ppp.pl()])
        ppp=Position(i.pr(),i.pl()+1);
    if(i!=ppp)
    {
        int tmp=p[i.pr()][i.pl()];
        p[i.pr()][i.pl()]=p[ppp.pr()][ppp.pl()];
        p[ppp.pr()][ppp.pl()]=tmp;
        Young_min_heapify(ppp);
    }
}

void Young_matrix::insert_ele(int x)
{
    if(pos.pr()*row+pos.pl()==(row-1)*(line-1))
        std::overflow_error("out of range");
    Young_increase_key(pos,x);
    int sum=pos.pr()*row+pos.pl()+1;
    pos.pr()=sum/row;
    pos.pl()=sum%row;
}

void Young_matrix::Young_increase_key(Position ppp,int key)
{
    p[ppp.pr()][ppp.pl()]=key;
    Position re;
    if(ppp.pr()-1>-1&&p[ppp.pr()-1][ppp.pl()]<p[ppp.pr()][ppp.pl()])
        re=ppp;
    else
        re=Position(ppp.pr()-1,ppp.pl());
    if(ppp.pl()-1>-1&&p[ppp.pr()][ppp.pl()-1]>p[ppp.pr()][ppp.pl()])
        re=Position(ppp.pr(),ppp.pl()-1);
    if(re!=ppp)
    {
        int tmp=p[re.pr()][re.pl()];
        p[re.pr()][re.pl()]=p[ppp.pr()][ppp.pl()];
        p[ppp.pr()][ppp.pl()]=tmp;
        Young_increase_key(re,key);
    }
}

bool Young_matrix::find_ele(int key)
{
    Position re(0,line);
    while(re.pr()<row&&re.pl()>0)
    {
        if(key==p[re.pr()][re.pl()])
            return true;
        if(key<p[re.pr()][re.pl()])
            re.pl()--;
        else
            re.pr()++;
    }
    //if((re.pr()==row)||(re.pl()==0))
        return false;
}

void Young_matrix::display()
{
    //int sum=0;
    //std::cout<<pos.pr()<<" "<<pos.pl()<<std::endl;
    for(int i=0;i!=row;++i) {
        for(int j=0;j!=line;++j)
    {
            std::cout<<p[i][j]<<" ";
    }
    std::cout<<std::endl;}
}

void Young_sort(Young_matrix y,int* a,int n)
{
    int sum=0;int key=y.pos.pr()*y.row+y.pos.pl();
    while(sum<key&&sum<n)
    {
        a[sum]=y.Young_extract_min();
        sum++;
    }
}
