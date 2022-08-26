
/**
основано на МиллераРабине   https://cp-algorithms.com/algebra/primality_tests.html#practice-problems
tested at : https://vjudge.net/problem/SPOJ-PRIME1
*/

/// base^e % mod
/**
unsigned long long binpower(unsigned long long base, unsigned long long e, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }
    return result;
}

/// я хз, что это
bool check_composite(unsigned long long n, unsigned long long a, unsigned long long d, int s) {
    unsigned long long x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (__uint128_t)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool isPrime(unsigned long long n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    unsigned long long d = n - 1;
    for (; (d & 1) == 0; ++r) {
        d >>= 1;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % a == 0)
            return (n == a);
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

*/

__uint128_t mod_pow(__uint128_t a, __uint128_t t, __uint128_t mod) {
    __uint128_t r = 1;

    for (; t; t >>= 1, a = (__uint128_t)(a) * a % mod)
        if (t & 1)
            r = (__uint128_t)(r) * a % mod;

    return r;
}



template <typename T>
bool isPrime(T n) {
    /// Китаец сказал, что 2, 3, 5, 7, 11, 13, 17, 19 для ull
    /// 2, 3, 5 - наверное следует использовать для интов, но 2 и 3 заходит для https://vjudge.net/problem/SPOJ-PRIME1
    static const int jp[] = { 2,3, 5};

    if (n == 1)
        return false;


    if (n % 2 == 0)
        return n == 2;

    if (n % 3 == 0)
        return n == 3;

    if (n % 5 == 0)
        return n == 5;


    T r = n - 1, x, y;
    int e = 0;

    while (~r & 1)
        r >>= 1, ++e;

    for (int p : jp) {
        x = mod_pow(p, r, n);

        for (int t = 0; t < e && x > 1; ++t) {
            y = (__uint128_t)x * x % n;

            if (y == 1 && x != n - 1)
                return false;

            x = y;

        }

        if (x != 1)
            return false;
    }

    return true;
}
