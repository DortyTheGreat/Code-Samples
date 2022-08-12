
/**
основано на МиллераРабине   https://cp-algorithms.com/algebra/primality_tests.html#practice-problems
tested at : https://vjudge.net/problem/SPOJ-PRIME1
*/

/// base^e % mod
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
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
