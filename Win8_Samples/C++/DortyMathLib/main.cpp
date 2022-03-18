#include <iostream>
#include <cmath>

using namespace std;

long double f(long double arg){
return arg * arg;
}

long double derivative(long double (*f)(long double),long double x){
int EpsilonExp = 8;
long double Epsilon = powl(10,EpsilonExp);
long double dx = x/Epsilon;
long double dy = ( f(x+dx) - f(x) )/dx;

return dy;
}

int main()
{
    cout << derivative(f,10) << endl;
    cout << "Hello world!" << endl;
    return 0;
}
