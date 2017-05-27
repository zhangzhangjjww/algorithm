#ifndef PIROR_QUEUE_H_INCLUDED
#define PIROR_QUEUE_H_INCLUDED
#include<vector>
#include<iostream>
#include<limits>

using namespace std;

template<class T> struct Piror_Queue
{
    vector<T> vol;
    int queue_size;
    Piror_Queue():queue_size(0) {}
    void heapilfy(int s)
    {
        int left=2*s+1;
        int right=2*(s+1);
        int minist;
        if(left<queue_size&&vol[left]<vol[s]) {
            minist=left;
        }
        else {
            minist=s;
        }
        if(right<queue_size&&vol[right]<vol[minist]) {
            minist=right;
        }
        if(minist!=s) {
            T tmp=vol[s];
            vol[s]=vol[minist];
            vol[minist]=tmp;
            heapilfy(minist);
        }
    }
    T queue_min()
    {
        return vol[0];
    }
    T queue_extract_min()
    {
        if(queue_size<1) {
            cout<<"wrong!"<<endl;
            T tmp;
            return tmp;
        }
        T minist=vol[0];
        vol[0]=vol[queue_size-1];
        --queue_size;
        heapilfy(0);
        return minist;
    }
    void queue_insert(T key)
    {
        ++queue_size;
        vol.push_back(key);
        decrease_key(queue_size-1,key);
    }
    void decrease_key(int s,T key)
    {
        //vol[s]=key;
        while(s>0&&vol[parent(s)]>vol[s]) {
            T tmp=vol[s];
            vol[s]=vol[parent(s)];
            vol[parent(s)]=tmp;
            s=parent(s);
        }
    }
    int parent(int s)
    {
        if(s%2==0) {
            return s/2-1;
        }
        else {
            return (s-1)/2;
        }
    }
    void print()
    {
        for(int i=0;i!=queue_size;++i) {
            cout<<vol[i]<<endl;
        }
    }
    bool is_empty()
    {
        return queue_size==0;
    }
    int queue_vol()
    {
        return queue_size;
    }
};


#endif // PIROR_QUEUE_H_INCLUDED
