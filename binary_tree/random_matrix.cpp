#ifndef RANDOM_MATRIX_H_INCLUDED
#define RANDOM_MATRIX_H_INCLUDED

#include"binary_tree.h"
#include<cstdlib>
#include<limits>


//int exponent(int base,int pow);
template<class T> void random_matrix(Node<T>* a,int p,int r);
template<class T> void merge_sort(Node<T>* a,int* b,int p,int r);
template<class T> void merge_all(Node<T>* a,int* b,int p,int q,int r);

/*int exponent(int base,int pow)
{
    int sum=1;
    for(int i=0;i!=pow;++i)
        sum*=base;
    return sum;
}*/

template<class T> void random_matrix(Node<T>* a,int p,int r)
{
    int n=r-p+1;
    int* b=new int[n];
    for(int i=0;i!=n;++i)
        b[i]=rand()%(n*n*n);
    merge_sort(a,b,p,r);
    delete [] b;
}

template<class T> void merge_sort(Node<T>* a,int* b,int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        merge_sort(a,b,p,q);
        merge_sort(a,b,q+1,r);
        merge_all(a,b,p,q,r);
    }
}

template<class T> void merge_all(Node<T>* a,int* b,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int* L=new int[n1+1];
    int* R=new int[n2+1];
    Node<T>* L1=new Node<T>[n1+1];
    Node<T>* R1=new Node<T>[n2+1];
    for(int i=0;i!=n1;++i)
    {
        L[i]=b[i+p];
        L1[i]=a[i+p];
    }
    for(int i=0;i!=n2;++i)
    {
        R[i]=b[i+q+1];
        R1[i]=a[i+q+1];
    }
    L[n1]=std::numeric_limits<int>::max();
    R[n2]=std::numeric_limits<int>::max();
    int m=0,n=0;
    for(int k=p;k!=r+1;++k)
    {
        if(L[m]<R[n])
        {
            a[k]=L1[m];
            ++m;
        }
        else
        {
            a[k]=R1[n];
            ++n;
        }
    }
    delete [] L;delete [] R;
    delete [] L1;delete [] R1;
}



#endif // RANDOM_MATRIX_H_INCLUDED
