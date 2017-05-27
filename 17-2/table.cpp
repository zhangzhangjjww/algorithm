#include<iostream>
#include"table.h"



template<class T> data table_search(Table<T>& t,T key)
 {
     int i=t.position;int j=-1;data result;
     while(i>=0&&j==-1)
     {
         j=binary_search(t.volume[i].p,0,t.volume[i].number-1,key);
         --i;
     }
     if(j==-1)
     {
         result.p1=0;result.p2=0;
     }
     else
     {
         result.p1=i+1;result.p2=j;
     }
     return result;
 }

template<class T> void table_insert(Table<T>& t,T key)
{
    Table<T> tmp;
    tmp.volume[0].p[0]=key;
    int i=0;
    if(!t.volume[0].isfull())
    {
        t.volume[0].p[0]=key;
        ++t.n;
        ++t.volume[0].number;
        return;
    }
    else
    {
        while(t.volume[i].isfull())
       {
            merge_sort(tmp.volume[i].p,t.volume[i].p,0,exponent(2,i)-1,tmp.volume[i+1].p);
            t.volume[i].set();
            ++i;
       }
       if(i>t.position)
           ++t.position;
       for(int j=0;j!=exponent(2,i);++j)
           t.volume[i].p[j]=tmp.volume[i].p[j];
       ++t.n;
       t.volume[i].number=t.volume[i].sz;
       return;
    }

}

template<class T> void table_output(Table<T>& t)
{
    for(int i=t.position;i!=-1;--i)
    {
        if(!t.volume[i].isempty())
        {
            for(int j=0;j!=t.volume[i].number;++j)
                std::cout<<t.volume[i].p[j]<<" ";
            std::cout<<std::endl;
        }
    }
}

template<class T> void table_delete(Table<T>& t,T key)
{
    int i=0;
    while(i<=t.position)
    {
        if(t.volume[i].isfull())
            break;
        ++i;
    }
    T y=t.volume[i].p[0];
    data result=table_search(t,key);
    if(result.p1==i)
    {
        //int j=binary_search(t.volume[i].p,0,t.volume[i].number,key);
        for(int k=result.p2;k!=t.volume[i].number-1;++k)
            t.volume[i].p[k]=t.volume[i].p[k+1];
        --t.volume[i].number;
    }
    else
    {
        t.volume[result.p1].p[result.p2]=y;
        sort1(t.volume[result.p1].p,0,t.volume[result.p1].number);
        for(int k=0;k!=t.volume[i].number-1;++k)
            t.volume[i].p[k]=t.volume[i].p[k+1];
        --t.volume[i].number;
    }
    int j=0;
    while(j<t.volume[i].number)
    {
        for(int k=0;k!=t.volume[j].sz;++k)
            t.volume[j].p[k]=t.volume[i].p[j+k];
        t.volume[j].number=t.volume[j].sz;
        j=j+exponent(2,j);
    }
    t.volume[i].set();
}
