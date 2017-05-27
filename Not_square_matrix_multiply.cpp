#include<iostream>
#include<cctype>
#include<stdexcept>
using namespace std;

template <class T> class square_matrix
{
private:
    size_t row;
    size_t line;
    T **p;
public:
    square_matrix(size_t s1=0,size_t s2=0):row(s1),line(s2) {p=new T*[row];for(size_t i=0;i!=row;++i) p[i]=new T[line];
    for(size_t i=0;i!=row;++i)
        for(size_t j=0;j!=line;++j)
            p[i][j]=0;
    }
    square_matrix(const square_matrix<T>& sm):row(sm.row),line(sm.line),p(0)
    {
        p=new T*[row];
        for(size_t i=0;i!=row;++i)
            p[i]=new T[line];
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            p[i][j]=(sm.p)[i][j];
    }
    ~square_matrix() { for(size_t i=0;i!=row;++i) delete [] p[i];delete [] p;}
    square_matrix<T>& operator=(const square_matrix<T>&sm)
    {
        for(size_t i=0;i!=row;++i) delete [] p[i];delete [] p;
        p=new T*[row];
        for(size_t i=0;i!=row;++i)
            p[i]=new T[line];
        row=sm.row;line=sm.line;
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            p[i][j]=sm.p[i][j];
        return *this;
    }
    void fill_matrix()
    {
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            cin>>p[i][j];
    }
    void display()
    {
        for(size_t i=0;i!=row;++i)
        {
            for(size_t j=0;j!=line;++j)
                cout<<p[i][j]<<" ";
            cout<<endl;
        }
    }
    square_matrix<T> operator+(const square_matrix<T>& sm)
    {
        square_matrix tmp(row,line);
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            tmp.p[i][j]=p[i][j]+sm.p[i][j];
        return tmp;
    }
    square_matrix<T> operator-(const square_matrix<T> &sm)
    {
        square_matrix<T> tmp(row,line);
        for(size_t i=0;i!=row;++i)
            for(size_t j=0;j!=line;++j)
            tmp.p[i][j]=p[i][j]-sm.p[i][j];
        return tmp;
    }
    square_matrix<T> square_matrix_multiply(const square_matrix<T> &sm)
    {
    square_matrix<T> tmp(row,line);

    for(size_t i=0;i!=row;++i)
        for(size_t j=0;j!=sm.line;++j)
        for(size_t k=0;k!=line;++k)
        (tmp.p)[i][j]+=p[i][k]*(sm.p)[k][j];
    return tmp;
}
   square_matrix<T> square_matrix_multiply_recursive(const square_matrix<T> &b)
   {
       square_matrix c(row,line);
       if(row==1&&line==1&&b.row==1&&b.line==1)
        (c.p)[0][0]=p[0][0]*(b.p)[0][0];
       if(row!=1&&line!=1&&b.row!=1&&b.line!=1)
       {
           size_t sz1=line/2,sz2=line-sz1,sz3=row-sz1,sz4=row-sz2;
           square_matrix<T> a11(sz1,sz1),a12(sz2,sz2),a21(sz3,sz1),a22(sz4,sz2),b11(sz1,sz1),b12(sz2,sz2),b21(sz3,sz1),b22(sz4,sz2),c11(sz1,sz1),c12(sz2,sz2),c21(sz3,sz1),c22(sz4,sz2);
           for(size_t i=0;i!=sz1;++i)
            for(size_t j=0;j!=sz1;++j)
           {
               a11.p[i][j]=p[i][j];
               b11.p[i][j]=b.p[i][j];
           }
           for(size_t i=0;i!=sz2;++i)
            for(size_t j=0;j!=sz2;++j)
           {
               a12.p[i][j]=p[i][j+sz1];
               b12.p[i][j]=b.p[i][j+sz1];
           }
           for(size_t i=0;i!=sz3;++i)
            for(size_t j=0;j!=sz1;++j)
           {
               a21.p[i][j]=p[i+sz1][j];
               b21.p[i][j]=b.p[i+sz1][j];
           }
           for(size_t i=0;i!=sz4;++i)
            for(size_t j=0;j!=sz2;++j)
           {
               a22.p[i][j]=p[i+sz2][j+sz1];
               b22.p[i][j]=b.p[i+sz2][j+sz1];
           }
           c11=a11.square_matrix_multiply_recursive(b11)+a12.square_matrix_multiply_recursive(b21);
           c12=a11.square_matrix_multiply_recursive(b12)+a12.square_matrix_multiply_recursive(b22);
           c21=a21.square_matrix_multiply_recursive(b11)+a22.square_matrix_multiply_recursive(b21);
           c22=a21.square_matrix_multiply_recursive(b12)+a22.square_matrix_multiply_recursive(b22);


       for(size_t i=0;i!=sz1;++i)
        for(size_t j=0;j!=sz1;++j)
       {
           c.p[i][j]=c11.p[i][j]; }
        for(size_t i=0;i!=sz2;++i)
        for(size_t j=0;j!=sz2;++j)
       {
           c.p[i][j+sz1]=c12.p[i][j]; }
        for(size_t i=0;i!=sz3;++i)
        for(size_t j=0;j!=sz1;++j)
       {
           c.p[i+sz1][j]=c21.p[i][j]; }
        for(size_t i=0;i!=sz4;++i)
        for(size_t j=0;j!=sz2;++j)
       {
           c.p[i+sz2][j+sz1]=c22.p[i][j]; } }


        if(row=1&&line!=1&&b.row!=1&&b.line!=1)
        {
            size_t sz1=line/2,sz2=line-sz1,sz3=b.row-sz1,sz4=row-sz2;
           square_matrix<T> a11(1,sz1),a12(1,sz2),b11(1,sz1),b12(1,sz2),b21(sz3,sz1),b22(sz3,sz2),c11(1,sz1),c12(1,sz2),c21(sz3,sz1),c22(sz3,sz2);
           for(size_t i=0;i!=sz1;++i)
            for(size_t j=0;j!=sz1;++j)
           {
               a11.p[i][j]=p[i][j];
               b11.p[i][j]=b.p[i][j];
           }
           for(size_t i=0;i!=sz2;++i)
            for(size_t j=0;j!=sz2;++j)
           {
               a12.p[i][j]=p[i][j+sz1];
               b12.p[i][j]=b.p[i][j+sz1];
           }
           for(size_t i=0;i!=sz3;++i)
            for(size_t j=0;j!=sz1;++j)
           {
               //a21.p[i][j]=p[i+sz1][j];
               b21.p[i][j]=b.p[i+sz1][j];
           }
           for(size_t i=0;i!=sz3;++i)
            for(size_t j=0;j!=sz2;++j)
           {
              // a22.p[i][j]=p[i+sz2][j+sz1];
               b22.p[i][j]=b.p[i+sz2][j+sz1];
           }
           c11=a11.square_matrix_multiply_recursive(b11)+a12.square_matrix_multiply_recursive(b21);
           c12=a11.square_matrix_multiply_recursive(b12)+a12.square_matrix_multiply_recursive(b22);
           c21=a21.square_matrix_multiply_recursive(b11)+a22.square_matrix_multiply_recursive(b21);
           c22=a21.square_matrix_multiply_recursive(b12)+a22.square_matrix_multiply_recursive(b22);


       for(size_t i=0;i!=sz1;++i)
        for(size_t j=0;j!=sz1;++j)
       {
           c.p[i][j]=c11.p[i][j]; }
        for(size_t i=0;i!=sz2;++i)
        for(size_t j=0;j!=sz2;++j)
       {
           c.p[i][j+sz1]=c12.p[i][j]; }
        for(size_t i=0;i!=sz3;++i)
        for(size_t j=0;j!=sz1;++j)
       {
           c.p[i+sz1][j]=c21.p[i][j]; }
        for(size_t i=0;i!=sz4;++i)
        for(size_t j=0;j!=sz2;++j)
       {
           c.p[i+sz2][j+sz1]=c22.p[i][j]; }
        }
       return c;
   }
  /* square_matrix<T> Strassen(const square_matrix<T>& b)
   {
       square_matrix<T> c(n);
       if(n==1)
        c.p[0][0]=p[0][0]*b.p[0][0];
       else
       {
           size_t sz1=n/2,sz2=n-sz1;
           square_matrix<T> a11(sz),a12(sz),a21(sz),a22(sz),b11(sz),b12(sz),b21(sz),b22(sz),c11(sz),c12(sz),c21(sz),c22(sz);
           for(size_t i=0;i!=sz;++i)
            for(size_t j=0;j!=sz;++j)
           {
               a11.p[i][j]=p[i][j];a12.p[i][j]=p[i][j+sz];a21.p[i][j]=p[i+sz][j];a22.p[i][j]=p[i+sz][j+sz];
               b11.p[i][j]=b.p[i][j];b12.p[i][j]=b.p[i][j+sz];b21.p[i][j]=b.p[i+sz][j];b22.p[i][j]=b.p[i+sz][j+sz];
           }
           square_matrix<T> s1(sz),s2(sz),s3(sz),s4(sz),s5(sz),s6(sz),s7(sz),s8(sz),s9(sz),s10(sz);
           s1=b12-b22;s2=a11+a12;s3=a21+a22;s4=b21-b11;s5=a11+a22;s6=b11+b22;s7=a12-a22;s8=b21+b22;s9=a11-a21;s10=b11+b12;
           square_matrix<T> p1(sz),p2(sz),p3(sz),p4(sz),p5(sz),p6(sz),p7(sz);
           p1=a11.Strassen(s1);p2=s2.Strassen(b22);p3=s3.Strassen(b11);p4=a22.Strassen(s4);p5=s5.Strassen(s6);p6=s7.Strassen(s8);p7=s9.Strassen(s10);
           c11=p5+p4-p2+p6;
           c12=p1+p2;
           c21=p3+p4;
           c22=p5+p1-p3-p7;
           for(size_t i=0;i!=sz;++i)
        for(size_t j=0;j!=sz;++j)
       {
           c.p[i][j]=c11.p[i][j];
           c.p[i+sz][j]=c21.p[i][j];
           c.p[i][j+sz]=c12.p[i][j];
           c.p[i+sz][j+sz]=c22.p[i][j];
       } }
       return c;
   } */

};

int main()
{
    square_matrix<double> a(3,3),b(3,3);
    a.fill_matrix();
    cout<<endl;
    b.fill_matrix();
    //square_matrix<int> b(a);
    cout<<endl;
    b.display();
    square_matrix<double> c=a.square_matrix_multiply(b);
    //square_matrix<double> d=a.square_matrix_multiply_recursive(b);
    c.display();
    cout<<endl;
   // d.display();
    cout<<endl;
   // d=a.Strassen(b);
   // d.display();
    return 0;

}

