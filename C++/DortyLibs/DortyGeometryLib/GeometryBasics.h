#include <cmath>


const double PI = 3.14159265358979323846 ;

double Epsilon = 0.00001;
bool doubleEqual(double a, double b){
    return (abs(a-b) <= Epsilon);
}
