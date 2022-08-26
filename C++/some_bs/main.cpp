#include <iostream>
#include <algorithm>
using namespace std;





unsigned int mod_pow(unsigned int a, unsigned int t, unsigned int mod) {
    unsigned long long r = 1;

    for (; t; t >>= 1, a = (unsigned long long)(a) * a % mod)
        if (t & 1)
            r = (unsigned long long)(r) * a % mod;

    return r;
}



template <typename T>
bool check_prime(T n) {
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
            y = (unsigned long long)x * x % n;

            if (y == 1 && x != n - 1)
                return false;

            x = y;

        }

        if (x != 1)
            return false;
    }

    return true;
}


int gcd1(int a, int b) {
    while(b) {
        int t = a % b;
        b = a;
        a = t;
    }
    return a;

}




// calcul a^n%mod
size_t power(size_t a, size_t n, size_t mod)
{
    size_t power = a;
    size_t result = 1;

    while (n)
    {
        if (n & 1)
            result = (result * power) % mod;
        power = (power * power) % mod;
        n >>= 1;
    }
    return result;
}

// n−1 = 2^s * d with d odd by factoring powers of 2 from n−1
bool witness(size_t n, size_t s, size_t d, size_t a)
{
    size_t x = power(a, d, n);
    size_t y;

    while (s) {
        y = (x * x) % n;
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }
    if (y != 1)
        return false;
    return true;
}

/*
 * if n < 1,373,653, it is enough to test a = 2 and 3;
 * if n < 9,080,191, it is enough to test a = 31 and 73;
 * if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
 * if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
 * if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
 * if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
 * if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
 */

bool is_prime_mr(size_t n)
{
    if (((!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3))
        return false;
    if (n <= 3)
        return true;

    size_t d = n / 2;
    size_t s = 1;
    while (!(d & 1)) {
        d /= 2;
        ++s;
    }

    if (n < 1373653)
        return witness(n, s, d, 2) && witness(n, s, d, 3);
    if (n < 9080191)
        return witness(n, s, d, 31) && witness(n, s, d, 73);
    if (n < 4759123141)
        return witness(n, s, d, 2) && witness(n, s, d, 7) && witness(n, s, d, 61);
    if (n < 1122004669633)
        return witness(n, s, d, 2) && witness(n, s, d, 13) && witness(n, s, d, 23) && witness(n, s, d, 1662803);
    if (n < 2152302898747)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
    if (n < 3474749660383)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13);
    return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17);
}


template<typename positive_number>
static inline positive_number multiplication_modulo(positive_number lhs, positive_number rhs, positive_number mod) {
    positive_number res = 0; // we avoid overflow in modular multiplication
    for (lhs %= mod, rhs%= mod; rhs; (rhs & 1) ? (res = (res + lhs) % mod) : 0, lhs = (lhs << 1) % mod, rhs >>= 1);
    return res; // <= (lhs * rhs) % mod
}

template<typename positive_number>
positive_number factor_worker(positive_number n) {
    size_t a; positive_number b = 0, c, d, e, f;
    for (a = 0; a < sizeof(positive_number); ((char*)&b)[a++] = rand()); // pick random polynomial
    c = b %= n;
    int i = 0;
    do {
        ++i;
        b = multiplication_modulo(b, b, n); if(++b == n) b = 0;
        c = multiplication_modulo(c, c, n); if(++c == n) c = 0;
        c = multiplication_modulo(c, c, n); if(++c == n) c = 0;
        for (d = n, e = b > c ? b - c : c - b; e; f = e, e = multiplication_modulo(d / f, f, n), e = (d - e) % n, d = f);
        // handle your precise timeout in the for loop body
    } while (d == 1);
    return d;
}

template<typename positive_number>
positive_number exec(positive_number n) {
    positive_number res = factor_worker(n); // 2 seconds
    if (res == n) return res + printf("%llu * ", n) * fflush(stdout) ;
    return exec(res) * exec(n / res);
}

/// https://codeforces.com/blog/entry/1729?locale=ru
template<typename T>
T mulmod(T a, T b, T MOD)
{
    if (b == 0) return 0;
    T res = mulmod(a, b >> 1, MOD);
    res += res;
    res %= MOD;
    return (b & 1)? (a + res) % MOD : res;
}

template<typename T>
T powmod(T a, T b, T MOD)
{
    if (b == 0) return 1;
    T res = powmod(a, b >> 1, MOD);
    res *= res;
    res %= MOD;
    return (b & 1)? (a * res) % MOD : res;
}


template<typename ll>
bool MillerRabin(ll n){
    if (n < 2 || (n != 2 && n%2 ==0)){return 0;}
    int s = 0;
    ll d = n - 1;
    while(!(d&1)){
        ++s;d>>=1;
    }

    ll checks[] = {2,3,5,7,11,13,17,19,23,29,31,37,41};
    for(int i =0;i<11 && checks[i]<n-1;++i){
        ll x = powmod(checks[i],d,n);
        if (x == 1 || x == n - 1) continue;
        bool cmp = 1;
        for(int j = 1;j<s;++j){
            x = mulmod(x,x,n);
            if (x == 1) return 0;
            if (x == n - 1){
                cmp = 0;
                break;
            }
        }
        if(cmp) return 0;
    }
    return 1;
}


int main()
{


    int t;
    cin >> t;
    while(t--){
        int a,b;
        cin >> a >> b;
        for(long long i = a;i<=b;++i){
            if (MillerRabin(i)){
                cout << i << '\n';
            }
        }
    }


}
