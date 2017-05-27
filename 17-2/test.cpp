#include<iostream>
#include"table.h"
#include"table.cpp"
//#include"function.cpp"

using namespace std;


 template<class> int binary_search(int* a,int start,int end,int key);
 template<class T> void table_insert(Table<T>& t,T key);



int main()
{
    Table<int> t;
    for(int i=0;i!=12;++i)
        table_insert(t,i);
    table_output(t);
    cout<<table_search(t,8).p1<<" "<<table_search(t,8).p2<<endl;
    table_delete(t,4);
    table_output(t);
   // cout<<binary_search(a,0,9,8)<<endl;
    int a[10];
   /* for(int i=0;i!=5;++i)
        a[i]=2*i;
    for(int i=5;i!=10;++i)
        a[i]=2*(i-5)+1;
    sort1(a,0,9);
    for(int i=0;i!=10;++i)
        cout<<a[i]<<endl;*/
    return 0;
}
