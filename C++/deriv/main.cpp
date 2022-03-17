#include <iostream>
#include <cmath>
using namespace std;

double V1, V2;
double D;

double inline sqr(double a){
    return a * a;
}

double piff(double dx, double dy){
    return sqrt(sqr(dx) + sqr(dy));
}

double f(double a){
    ///return sqr(a);
    return piff(1-D,a)/V1 + piff(D,1-a)/V2;
}

const double precision = 1e-8;
double deriv( double (*func)(double a), double x){
    double dx = max(abs(x) * precision,precision);
    return (func(x + dx) - func(x))/ dx;
}

///
double newton_method(double (*func)(double a), int itterations, double step){
    double ret = 0;

    for(int i = 0;i<itterations;i++){
        ret += deriv(func,ret) / func(ret) * step * pow(0.99,i);
    }
    return ret;
}

int main()
{
    V1 = 5;
    V2 = 3;
    D = 0.4;
    cin >> V1 >> V2 >> D;

    cout << newton_method(f,1000,-0.2);

    ///cout << "Hello world!" << endl;
    return 0;
}
