#include<cstdlib>

template<class T> int binary_search(T* a,int start,int end,T key)
{
    if(start<end)
    {
        int mid=(start+end)/2;
        if(key==a[mid])
            return mid;
        else
            if(key<a[mid])
              return binary_search(a,start,mid-1,key);
        else
            return binary_search(a,mid+1,end,key);
    }
    else
        if(start==end)
        {
            if(a[start]==key)
                return start;
            else
                return -1;
        }
        else
            return -1;
}

template<class T> void merge(T* a1,int start,int mid,int end)
{
    int n1=mid-start+1;
    int n2=end-mid;
    T* L=new T[n1];
    T* R=new T[n2];
    for(int i=0;i!=n1;++i)
        L[i]=a1[start+i];
    for(int i=0;i!=n2;++i)
        R[i]=a1[i+mid+1];
    int j=0;int k=0;
    for(int ii=start;ii!=end+1;++ii)
    {
        if(j>=n1)
        {
            for(;k!=n2;++k,++ii)
                a1[ii]=R[k];
            break;
        }
        if(k>=n2)
        {
            for(;j!=n1;++ii,++j)
                a1[ii]=L[j];
            break;
        }
        if(L[j]<=R[k])
        {
            a1[ii]=L[j];
            ++j;
        }
        else
        {
            a1[ii]=R[k];
            ++k;
        }
    }
    delete [] L;delete [] R;
}


template<class T> void sort1(T* a1,int start,int end)
{
    if(start<end)
    {
        int mid=(start+end)/2;
        sort1(a1,start,mid);
        sort1(a1,mid+1,end);
        merge(a1,start,mid,end);

    }
}

template<class T> void merge_sort(T* a1,T* a2,int start,int end,T* target)
{
    int i=2*(1+end-start);
    int j=0,k=0;
    for(int ii=0;ii!=i;++ii)
    {
        if(j<=end&&k<=end){
        if(a1[j]<=a2[k])
        {
            target[ii]=a1[j];
            ++j;
        }
        else
        {
            target[ii]=a2[k];
            ++k;
        }
        }
        else
        {
            if(j>end)
            {
                target[ii]=a2[k];
                ++k;
            }
            else
            {
                target[ii]=a1[j];
                ++j;
            }
        }
    }
}
