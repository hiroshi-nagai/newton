
//==================================================
// newton
//==================================================
#include <iostream>
#include <valarray>
#include <boost/function.hpp>
/*
 ◆開発環境
 [OS]: macOS 10.14~
 [c++] gcc version 9.2.0
 [boost] 1.71.0
 
 */
// テスト用パラメータークラス
class Param
{
    public:
        double t=0;
        double x=0;
        double y=0;
};


class Newton
{
    private:
        double f( double t, double ox, boost::function<double(double, Param)> method, Param _param )
        {
            double x;
            double _dif;
            x = method(t, _param);
            _dif = ox - x;
            return _dif;
        }
        
        double df( double t, double ox, boost::function<double(double, Param)> method, Param _param )
        {
            double x;
            double h;
            double dx;
            h = 0.00001;
            x = this->f(t, ox, method, _param);
            dx = this->f(t+h, ox, method, _param);
            return (dx-x)/h;
        }
    
    public:
        double newton( double initval, double ox, boost::function<double(double, Param)> method, Param _param , int count=1000000000, double ep=0.0001)
        {
            /*
             oxに最も近づくt値を近似する。epは収束時の許容誤差
             */
            double x2;
            double rf;
            double rdf;
            double x=initval;
            for (int i=0; i<count; i++)
                {
                    rf = this->f(x, ox, method, _param);
                    rdf = this->df(x, ox, method, _param);
                    std::cout<<"x:  " << x <<",   ox: "<< ox << ",  rf: " << rf << ",    rdf: " << rdf << std::endl;
                    if (rf ==0.0 || rdf==0.0)
                        {
                            return 0;
                        }
                    x2 = x - rf / rdf;
                    if (std::abs(x2-x) < ep)
                        {
                            x=x2;
                            break;
                        }else{
                            x=x2;
                            continue;
                        }
                        return x2;
                }
         return x2;
        }
};


// 動作テスト用
double testMethod(double t, Param _param)
{
    double result;
    result = (_param.x * (_param.y/2)) *t;
    return result;
};

int main()
{
    double t;
    Param test_param;
    test_param.t = 0.0;
    test_param.x = 3.0;
    test_param.y = 4.0;
    Newton nt;
    t = nt.newton(0.001, 200.34, testMethod, test_param, 1000000000, 0.0001);
    std::cout<<"t:  " <<t<< std::endl;
    return 0;
}
