#include <random>
#include <numeric>
#include <bits/stdc++.h>
#include "../DortyLibs/rand.h"
#include "../DortyLibs/gcd.h"
#define ll long long

using namespace std;
/**
 * https://www.geeksforgeeks.org/pollards-rho-algorithm-prime-factorization/
 *
 * To compare in terms of performance to my qs implementation
*/



long long int modular_pow(long long int base, int exponent,
                          long long int modulus)
{
    /* initialize result */
    long long int result = 1;

    while (exponent > 0)
    {
        /* if y is odd, multiply base with result */
        if (exponent & 1)
            result = (result * base) % modulus;

        /* exponent = exponent/2 */
        exponent = exponent >> 1;

        /* base = base * base */
        base = (base * base) % modulus;
    }
    return result;
}

/* method to return prime divisor for n */
long long int PollardRho(long long int n)
{
    /* initialize random seed */
    srand (time(NULL));

    /* no prime divisor for 1 */
    if (n==1) return n;

    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) return 2;

    /* we will pick from the range [2, N) */
    long long int x = (rand()%(n-2))+2;
    long long int y = x;

    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    long long int c = (rand()%(n-1))+1;

    /* Initialize candidate divisor (or result) */
    long long int d = 1;

    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (d==1)
    {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        x = (modular_pow(x, 2, n) + c + n)%n;

        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (modular_pow(y, 2, n) + c + n)%n;
        y = (modular_pow(y, 2, n) + c + n)%n;

        /* check gcd of |x-y| and n */
        d = __gcd(abs(x-y), n);

        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (d==n) return PollardRho(n);
    }

    return d;
}

/// src : https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
template <typename INT>
INT modInverse(INT a, INT m)
{
    INT m0 = m;
    INT y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        INT q = a / m;
        INT t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}


ll getOneFactor(ll n,int maximumIterations = 10000){

    int iteration = 0;

    ll factor = 1;
    ll x = rnd(2,n);
    ll y = rnd(2,n);
    ll A = rnd(2,n);
    ll LT = (3 * x * x + A);
    ll LN = (2 * y);


    if (gcd(LN, n) == 1){
        ll L = (LT * modInverse(LN, n)) % n;
        ll x2 = (L*L - x*2) % n;
        ll y2 = (L*(x - x2) - y) % n;

        for (int i = 0; i < maximumIterations; ++i){

                LT = (y2 - y) % n;
                LN = (x2 - x) % n;

                if (LT < n ){LT += n;}
                if (LN < n ){LN += n;}

                if (gcd(LN, n) == 1){
                    L = (LT * modInverse(LN, n)) % n;
                    ll x3 = (L*L - x - x2) % n;
                    ll y3 = (L*(x - x3) - y) % n;
                    x2 = x3; y2 = y3;
                }else{
                    cout << "here" << endl;
                    cout << LN << " " << n << endl;
                    return gcd(LN, n);
                }
        }

        return n;

    }else{
        return gcd(LN, n);
    }

}
/*
ll Ferma(ll n){
     if (n % 2 == 0)
        return 2;

    ll a = ceil(sqrt(n));
    ll b2 = a*a - n;
    while (!isSquare(b2)){
        a += 1
        b2 = a*a - n
    }
    b = sqrt(b2)
    return p = (a + b), q = (a - b)
}
*/

/**

https://www.rsok.com/~jrm/9_digit_palindromic_primes.html

100030001
100050001
100060001
100111001
100131001
*/

/// rho(n,1)
long long rho(long long n, int c) {
    long long t = 2;
    long long h = 2;
    long long  d = 1;
    long long g;

    while (d == 1) {
        t = (t*t + c) % n;
        h = (h*h + c) % n;
        h = (h*h + c) % n;

        g = t-h;
        if (g < n){g += n;}

        d = gcd(g, n); }

    if (d == n)
        return rho(n, c+1);

    cout << d << endl;
    return d;
}

/* driver function */
int main()
{


    long long int n = 100030001LL * 100030001LL;

    cout << PollardRho(n) << endl;

    printf("One of the divisors for %lld is %lld.",
          n, getOneFactor(n));
    return 0;

}
