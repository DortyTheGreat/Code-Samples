#include <iostream>

using namespace std;
/**
Для n=1 ответ a/2
Для n=2 (a <= b) (integral from 0 to a of x*a*(1-x/b)*dx ) / (integral from 0 to a of a*(1-x/b)*dx )
(a (2 a - 3 b))/(3 (a - 2 b))

n = 3
(integral from 0 to a of x*a*(1-x/b)*(1-x/c)*dx ) / (integral from 0 to a of a*(1-x/b)*(1-x/c)*dx )
(3 a^3 - 4 a^2 b - 4 a^2 c + 6 a b c)/(4 a^2 - 6 a b - 6 a c + 12 b c)


n = 4
(a (-12 a^3 + 15 a^2 (b + c + d) - 20 a (b (c + d) + c d) + 30 b c d))/(5 (-3 a^3 + 4 a^2 (b + c + d) - 6 a (b (c + d) + c d) + 12 b c d))

n = 5
(a (10 a^4 - 12 a^3 (b + c + d + e) + 15 a^2 (b (c + d + e) + c (d + e) + d e) - 20 a (b e (c + d) + b c d + c d e) + 30 b c d e))/(12 a^4 - 15 a^3 (b + c + d + e) + 20 a^2 (b (c + d + e) + c (d + e) + d e) - 30 a (b e (c + d) + b c d + c d e) + 60 b c d e)

*/

/**
f2 = (a + b - 2 x)/(a b)


f * (1 - x/c) + 1/c * integral from x to a of f * dx

f[n](x) = f[n-1](x) * (1 - x/var[n]) + 1/var[n] * integral from x to var[1] of f[n-1](x) * dx
f[1](x) = 1 / var[1]


f3 = ( (a + b - 2 x)/(a b) ) * (1 - x/c) + 1/c * integral from x to a of (a + b - 2 x)/(a b) * dx
= (a (b + c - 2 x) + b (c - 2 x) + x (3 x - 2 c))/(a b c)
I3 = (a (a^2 + 6 b c - 2 a (b + c)))/(12 b c)



f4 = ((a (b + c - 2 x) + b (c - 2 x) + x (3 x - 2 c))/(a b c)) * (1 - x/d) + 1/d * integral from x to a of ((a (b + c - 2 x) + b (c - 2 x) + x (3 x - 2 c))/(a b c)) * dx
= (3 x^2 (a + b + c + d) - 2 x (a (b + c + d) + b (c + d) + c d) + a b c + a b d + a c d + b c d - 4 x^3)/(a b c d)
I4 = (a (-3 a^3 + 30 b c d + 5 a^2 (b + c + d) - 10 a (c d + b (c + d))))/(60 b c d)

f5 = ((3 x^2 (a + b + c + d) - 2 x (a (b + c + d) + b (c + d) + c d) + a b c + a b d + a c d + b c d - 4 x^3)/(a b c d)) * (1 - x/e)
 + 1/e * integral from x to a of ((3 x^2 (a + b + c + d) - 2 x (a (b + c + d) + b (c + d) + c d) + a b c + a b d + a c d + b c d - 4 x^3)/(a b c d)) * dx


SP = ((a - x) (b - x) (c - x) (d - x))/(a b c d e)


((3 x^2 (a + b + c + d) - 2 x (a (b + c + d) + b (c + d) + c d) + a b c + a b d + a c d + b c d - 4 x^3)/(a b c d)) * (1 - x/e) + ((a - x) (b - x) (c - x) (d - x))/(a b c d e)







f5 = ((e - x) (3 x^2 (a + b + c + d) - 2 x (a (b + c + d) + b (c + d) + c d) + a b c + a b d + a c d + b c d - 4 x^3) + (a - x) (b - x) (c - x) (d - x))/(a b c d e)
I5 = (a (2 a^4 + 30 b c d e - 3 a^3 (b + c + d + e) - 10 a (b d e + c d e + b c (d + e)) + 5 a^2 (d e + c (d + e) + b (c + d + e))))/(60 b c d e)
*/

#include <cassert>
#include <algorithm>

int main()
{

    int n;
    cin >> n;
    int arr[5];
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    sort(arr, arr + n);

    int64_t a = arr[0];
    int64_t b = arr[1];
    int64_t c = arr[2];
    int64_t d = arr[3];
    int64_t e = arr[4];

    int64_t numer = 0;
    int64_t denom = 0;

    if (n == 1){
        numer = a;
        denom = 2;
    }

    if (n == 2){
        numer = a*(3*b - a);
        denom = 6 * b;
    }

    if (n == 3){
        numer = (a*(a*a + 6*b*c - 2*a*(b + c)));
        denom = (12*b*c);
    }


    if (n == 4){
        numer = (a*(-3*a*a*a + 30*b*c*d + 5*a*a* (b + c + d) - 10*a*(c*d + b*(c + d))));
        denom = (60*b*c*d);
    }

    if (n == 5){
        numer = (a*(2*a*a*a*a + 30*b*c*d*e - 3*a*a*a*(b + c + d + e) - 10*a*(b*d*e + c*d*e + b*c*(d + e)) + 5*a*a*(d*e + c*(d + e) + b*(c + d + e))));
        denom = (60*b*c*d*e);
    }

    if (numer < 0){
        numer *= -1;
        denom *= -1;
    }

    int64_t g = __gcd(numer,denom);

    numer /= g;
    denom /= g;

    cout << numer << "/" << denom << endl;
    return 0;
}
