#ifndef MAX_PRI_QUEUE_H_INCLUDED
#define MAX_PRI_QUEUE_H_INCLUDED
#include<limits>
#include<iostream>
class Pointer
{
private:
    int* p;
    int sz;
public:
    Pointer(int s):p(0),sz(s) {p=new int[sz];for(int i=0;i!=sz;++i) p[i]=0;}
    Pointer(int* a,int n):p(0),sz(n)
    {
        p=new int[sz];
        for(int i=0;i!=n;++i)
            p[i]=a[i];
    }
    Pointer& operator=(Pointer& pp)
    {
        delete [] p;
        sz=pp.sz;
        p=new int[sz];
        for(int i=0;i!=sz;++i)
            p[i]=pp.p[i];
        return *this;
    }
    ~Pointer() {delete [] p;}
    void addsz()
    {
        int *p1=new int[sz+1];
        for(int i=0;i!=sz;++i)
            p1[i]=p[i];
        sz++;
        p1[sz]=(std::numeric_limits<int>::min)();
        delete [] p;
        p=p1;
    }
    void desz()
    {
        int *p1=new int[sz-1];
        for(int i=1;i!=sz-1;++i)
            p1[i]=p[i];
        p1[0]=p[sz-1];
        sz=sz-1;
        delete [] p;
        p=p1;
    }
    int& operator[](int i)
    {
        return p[i];
    }
    int vol() {return sz;}
    void display()
    {
        for(int i=0;i!=sz;++i)
            std::cout<<p[i]<<std::endl;
    }
    void dele(int i)
    {
        int* p1=new int[sz-1];
        for(int j=0;j!=i;++j)
            p1[j]=p[j];
        p1[i]=p[sz-1];
        for(int j=i+1;j!=sz-1;++j)
            p1[j]=p[j];
        sz--;
        delete [] p;
        p=p1;
    }
};

int heap_maximum(Pointer &a);
int heap_extract_max(Pointer &a);
void max_heap_insert(Pointer &a,int x);
void increase_key(Pointer &a,int x,int k);
void heap_delete(Pointer& a,int i);


#endif // MAX_PRI_QUEUE_H_INCLUDED
