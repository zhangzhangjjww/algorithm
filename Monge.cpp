#include<iostream>
#include<cctype>
#include<vector>

using namespace std;

class MongeItem
{
private:
    size_t index;
    int value;
public:
    MongeItem(size_t s=0,int v=0):index(s),value(v) {}
    size_t position() {return index;}
    int mo_value() {return value;}
};

class MongeItemlist
{
private:
    vector<MongeItem> mi;
    vector<MongeItem>::size_type sz;
public:
    MongeItemlist(vector<MongeItem>::size_type s) {sz=s;for(vector<MongeItem>::size_type i=0;i!=s;++i) mi.push_back(MongeItem(0,0));}
    ~MongeItemlist() {}
    MongeItemlist(const MongeItemlist& m):sz(m.sz)
    {
        for(int i=0;i!=sz;++i)
            mi.push_back(m.mi[i]);
    }
    MongeItem& operator[](int i) {return mi[i];}
    size_t mil_sz() {return sz;}
    void display()
    {
        for(size_t i=0;i!=sz;++i)
            cout<<mi[i].position()<<" "<<mi[i].mo_value()<<endl;
    }
   void push(MongeItem m) {mi.push_back(m);}
};



class Monge
{
private:
    int** p;
    size_t row;
    size_t line;
    void destroy()
    {
        for(size_t i=0;i!=row;++i)
            delete [] p[i];
        delete [] p;
    }
public:
    Monge(size_t r,size_t l):p(0),row(r),line(l)
    {

        p=new int*[row];
        for(int i=0;i!=row;++i)
            p[i]=new int[line];
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            p[i][j]=0;
    }
    Monge(const Monge& m):p(0),row(m.row),line(m.line)
    {
        p=new int*[row];
        for(int i=0;i!=row;++i)
            p[i]=new int[line];
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            p[i][j]=m.p[i][j];
    }
    Monge& operator=(const Monge& m)
    {
        destroy();
        p=new int*[row];
        for(int i=0;i!=row;++i)
            p[i]=new int[line];
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            p[i][j]=m.p[i][j];
        return *this;
    }
    ~Monge() {destroy();}
    void fill_in()
    {
        cout<<"fill the Monge matrix:"<<endl;
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            cin>>p[i][j];
    }
    Monge subarray()
    {
        int rr=row/2.0+0.5;
        Monge tmp(rr,line);
        for(int i=0,k=0;i!=rr;++i,k+=2)
            for(int j=0;j!=line;++j)
            tmp.p[i][j]=p[k][j];
        return tmp;
    }
   friend MongeItemlist Mongesearch(Monge m,int n)
    {
        MongeItemlist mil(n);
        if(n==1)
        {
            int key=m.p[0][0];int po=0;
            for(int i=0;i!=m.line;++i)
               if(m.p[0][i]<key)
            {
                key=m.p[0][i];
                po=i;
            }
            mil[0]=MongeItem(po,key);
            return mil;
        }
        else {
        Monge even=m.subarray();
        MongeItemlist evenlist=Mongesearch(even,even.row);
        int jj=0;int i;
        for(i=1;i<m.row;i+=2,++jj)
        {
            mil[i-1]=evenlist[jj];
            size_t po=evenlist[jj].position();int key=m.p[i][po];int j;
            if(jj+2==m.row) {
                    for(j=evenlist[jj].position()+1;j<m.line;++j)
                     if(m.p[i][j]<key)
            {
                key=m.p[i][j];
                po=j;
            } }
            else {
            for(j=evenlist[jj].position()+1; j <= evenlist[jj + 1].position(); j++)
                if(m.p[i][j]<key)
            {
                key=m.p[i][j];
                po=j;
            } }
            mil[i]=MongeItem(po,key);
            //if(jj < evenlist.mil_sz() &&i + 1 < m.row)
                    mil[i + 1] = evenlist[jj + 1];}

        return mil;

    } }
    friend ostream& operator<<(ostream& os,Monge& m);
};

ostream& operator<<(ostream& os,Monge& m)
{
    for(size_t i=0;i!=m.row;++i)
    {
        for(size_t j=0;j!=m.line;++j)
            os<<m.p[i][j]<<" ";
        os<<endl;
    }
    return os;
}

int main()
{
    Monge m1(3,2);
    m1.fill_in();
    cout<<m1;
    Monge m2=m1.subarray();
    cout<<m2;
  MongeItemlist m=Mongesearch(m1,30);
   m.display();
    //cout<<m2;
   // Monge m3(4,4);
    //cout<<m1;cout<<m2;cout<<m3;
   // m3=m1;
   // cout<<m3;
    return 0;
}
