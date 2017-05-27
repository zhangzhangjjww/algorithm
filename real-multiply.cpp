#include<iostream>

using namespace std;

class real_number
{
private:
    double real;
    double vir;
public:
    real_number(double r=0,double v=0):real(r),vir(v) {}
    real_number operator*(const real_number& re)
    {
        double re1,re2,re3;
        re1=(real-vir)*(re.real+re.vir);
        re2=(real+vir)*(re.real-re.vir);
        re3=vir*re.vir;
        real_number answer;
        answer.real=(re1+re2)/2.0;
        answer.vir=(re2-re1+4.0*re3)/2;
        return answer;
    }
    friend ostream& operator<<(ostream& os,const real_number& r)
    {
        os<<"real part:"<<r.real<<endl;
        os<<"virtual part:"<<r.vir<<endl;
        return os;
    }
    double& re_number() {return real;}
    double& v_number() {return vir;}
};

int main()
{
    real_number r1(1,1);
    real_number r2(3,3);
    cout<<r1*r2;
    return 0;
}
