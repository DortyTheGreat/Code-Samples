/*
---------------------
This File was Build Automatically by DortyBuild v 1.4.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

/// https://informatics.msk.ru/mod/statements/view.php?chapterid=623#1

#include <algorithm>
#include <cstdio>
#include <iostream>
#include "../../../DortyLibs/DortyBuild.h"
#include "../../../DortyLibs/prime/factor.h"


using namespace std;

int main()
{

    AppBuild();
    unsigned int n;
    cin >> n;

    auto v = prime_factor(n);
    sort(v.begin(),v.end());
    cout << v[0];
    for(int i = 1;i < v.size();++i){
        cout <<'*' <<v[i];
    }
    return 0;
}

*/
/// https://informatics.msk.ru/mod/statements/view.php?chapterid=623#1

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>

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

// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

/// since (a == 0) === !a

#include <utility> /// pair

template <typename T>
inline std::pair<T, T> mont_modinv(T m) {
    const size_t shift = sizeof(m) * 8 - 1;
    T a = T(1) << shift;
    T u = 1;
    T v = 0;

    while (a) {
        a >>= 1;
        if (u & 1) {
            u = ((u ^ m) >> 1) + (u & m);
            v = (v >> 1) + (T(1) << shift);
        }
        else {
            u >>= 1; v >>=1;
        }
    }
    return std::make_pair(u, v);
}

// Computes (a + b) % m, assumes a < m and b < m.
template<typename T>
T addmod(T a, T b, T m) {
    if (b >= m - a) return a - m + b;
    return a + b;
}

template<typename T>
static T mult(T x, T y,T& HighProduct) {
    const size_t shift = sizeof(x) * 4;
    T a = x >> shift, b = (x << shift) >> shift;
    T c = y >> shift, d = (y << shift) >> shift;
    // (a*2^64 + b) * (c*2^64 + d) =
    // (a*c) * 2^128 + (a*d + b*c)*2^64 + (b*d)
    T ac = a * c;
    T ad = a * d;
    T bc = b * c;
    T bd = b * d;
    T carry = ((ad << shift) >> shift) + ((bc << shift) >> shift) + (bd >> shift);
    HighProduct = ac + (ad >> shift) + (bc >> shift) + (carry >> shift);
    return (ad << shift) + (bc << shift) + bd;
}

// Computes aR * bR mod N with R = 2**64.
template<typename T>
T mont_mul(T a, T b, T N, T Nneginv) {
    T Th, Tl, m, mNh, mNl;

    Tl = mult(a, b, Th);
    m = Tl * Nneginv;
    mNl = mult(m, N, mNh);


    /*
    T tl2, th2;
    uint32_t low_carry_in = 0;

    uint32_t carryL = _addcarry_u64(low_carry_in, Tl, mNl, &tl2);
    uint32_t carryH = _addcarry_u64(carryL, Th, mNh, &th2);

    if (carryH || (th2 >= N)) th2 = th2 - N;

    return th2;
    */

    bool lc = Tl + mNl < Tl;
    T th = Th + mNh + lc;
    bool hc = (th < Th) || (th == Th && lc);

    if (hc > 0 || th >= N) th = th - N;

    return th;
}

/// Чуть быстрее __gcd, для int
template<typename T>
T gcd(T a, T b)
{
    T c;
    while (b)
    {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}
/// Для long long и выше - предпочтительнее -
/// https://github.com/NyaanNyaan/library/blob/master/math-fast/gcd.hpp
template<typename T>
inline T binary_gcd(T a, T b) {
  if (a == 0 || b == 0) return a + b;
  unsigned char n = __builtin_ctzll(a);
  unsigned char m = __builtin_ctzll(b);
  a >>= n;
  b >>= m;
  n = std::min(n, m);
  while (a != b) {
    T d = a - b;
    unsigned char s = __builtin_ctzll(d);
    bool f = a > b;
    b = f ? b : a;
    a = (f ? d : -d) >> s;
  }
  return a << n;
}


template <typename T>
T pollard_brent_montgomery(T n) {

    if (!(n & 1))
        return 2;


    // Random number Linear Congruential Generator MMIX from D.E. Knuth
    static uint64_t rng = 0xdeafbeef;
    uint64_t a = rng * 6364136223846793005ull + 1442695040888963407ull;
    uint64_t b = a * 6364136223846793005ull + 1442695040888963407ull;
    rng = (a + b) ^ (a * b);

    // y and c are "montgomery space" numbers
    T y = 1 + a % (n - 1);
    T c = 1 + b % (n - 1);
    const T m = 100;

    // nneginv is m' (mprime) in Warren
    T nneginv = mont_modinv(n).second;


    T factor = 1, r, q, x, ys,tries;
    q = r = 1;

    while(factor == 1){
        x = y;
        for (size_t i = 0; i < r; ++i) {
            y = addmod(mont_mul(y, y, n, nneginv), c, n);
        }

        for (size_t k = 0; k < r && factor == 1; k += m) {
            ys = y;

            tries = (r - k);
            if (tries > m){tries = m;}

            for (size_t i = 0; i < tries; ++i) {
                y = addmod(mont_mul(y, y, n, nneginv), c, n);
                q = mont_mul(q, x < y ? y - x : x - y, n, nneginv);
            }

            factor = gcd(q, n);
        }

        r *= 2;
    }

    if(factor == n) {
        do {
            ys = addmod(mont_mul(ys, ys, n, nneginv), c, n);
            factor = gcd(x < ys ? ys - x : x - ys, n);
        } while (factor == 1);
    }

    if (factor == n){return pollard_brent_montgomery(n);}

    return factor;
}

#include <map>
#include <vector>

template<typename T>
void factor(T n, std::map<T,int>& ans) {

    if (n == 1) return;
    if (isPrime(n)) { ++ans[n]; return; } /// got here n as a factor
    T divisor = pollard_brent_montgomery(n);
    factor(divisor, ans);
    factor(n / divisor, ans);
}

template<typename T>
std::vector<T> prime_factor(T n) {
    std::vector<T> ret;
    ret.push_back(n);
    for(size_t i = 0;i < ret.size(); ){

        if (isPrime(ret[i])) { ++i;continue; } /// got here n as a factor
        ret.push_back(pollard_brent_montgomery(ret[i]));

        ret[i] /= ret.back();


    }




    return ret;
}




using namespace std;

int main()
{

     
    unsigned int n;
    cin >> n;

    auto v = prime_factor(n);
    sort(v.begin(),v.end());
    cout << v[0];
    for(int i = 1;i < v.size();++i){
        cout <<'*' <<v[i];
    }
    return 0;
}

