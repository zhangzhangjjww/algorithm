#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include"function.cpp"

template<class T> int binary_search(T* a,int start,int end,T key);
template<class T> void merge_sort(T* a1,T* a2,int start,int end,T* target);
template<class T> void sort(T* a1,int start,int end);

const int K=8;

int exponent(int base,int pow);

 struct data //search返回的数据类型
 {
     int p1;
     int p2;
 };

template<class T> struct Array
{
    T* p;
    int sz;
    int number;
    Array():p(0),number(0),sz(0) {}
    bool isfull()
    {
        if(sz==number)
            return true;
        else
            return false;
    }
    bool isempty()
    {
        if(number==0)
            return true;
        else
            return false;
    }
    void set()
    {
        for(int i=0;i!=sz;++i)
            p[i]=0;
        number=0;
    }
};


template<class T> class Table;
template<class T> data table_search(Table<T>& t,T key);
template<class T> void table_insert(Table<T>& t,T key);
template<class T> void table_delete(Table<T>& t,T key);
template<class T> void table_output(Table<T>& t);

template<class T> class Table
{
private:
    Array<T> volume[K];
    int position;
    int n;
public:
    Table():position(0),n(0)
    {
        for(int i=0;i!=K;++i)
        {
            volume[i].p=new T[exponent(2,i)];
            volume[i].sz=exponent(2,i);
        }
    }
    ~Table()
    {
        for(int i=0;i!=K;++i)
        {
            delete [] volume[i].p;
            volume[i].p=0;
        }
    }
    friend data table_search<T>(Table<T>& t,T key);
    friend void table_insert<T>(Table<T>& t,T key);
    friend void table_delete<T>(Table<T>& t,T key);
    friend void table_output<T>(Table<T>& t);
};


#endif // TABLE_H_INCLUDED
