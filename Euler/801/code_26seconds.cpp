#include <iostream>
#include <map>
#include <cmath>
#include <vector>

#include <cstdint>
#include <iostream>
#include <tuple>




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


uint64_t montmul(__uint128_t a, uint64_t b, __uint128_t mod, uint64_t inv){
    a *= b;
    uint64_t y = (a >> 64) - (__uint128_t(uint64_t(a) * inv) * mod >> 64);
    return int64_t(y) < 0 ? y + mod : y;

}

/// Чуть быстрее __gcd, для int
template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}




#include <utility> // pair



template<typename T>
T mont_mul(T a, T b, T N, T Nneginv) {
    T Th, Tl, m, mNh, mNl;

    Tl = mult(a, b, Th);
    m = Tl * Nneginv;
    mNl = mult(m, N, mNh);

    bool lc = Tl + mNl < Tl;
    T th = Th + mNh + lc;
    bool hc = (th < Th) || (th == Th && lc);

    if (hc > 0 || th >= N) th = th - N;

    return th;
}


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


// Returns a factor of n, assumes n is odd.



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

using namespace std;

__uint128_t mod_pow(__uint128_t a, __uint128_t t, __uint128_t mod) {
    __uint128_t r = 1;

    for (; t; t >>= 1, a = (a) * a % mod)
        if (t & 1)
            r = (r) * a % mod;

    return r;
}




bool isPrime(unsigned long long n) {

    static const int jp[] = { 2, 3, 5, 7, 11, 13, 17, 19};

    if (n == 1)
        return false;


    unsigned long long r = n - 1, x, y;

    unsigned char e = __builtin_ctz(r);
    r >>= e;

    for (int p : jp) {
        if (n % p == 0)
            return n == p;
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


#define cf(k) while (!(num % k)){++ret[k]; num /= k;}

std::map<uint64_t,int> factor(__uint128_t num){
    std::map<unsigned long long,int> ret;
    uint64_t* arr = new uint64_t[sizeof(uint64_t) ];
    unsigned int size = 0;

    cf(2) cf(3) cf(5) cf(7) cf(11)

    arr[0] = num;



    for(size_t i = 0;i < size + 1; ){
        if(arr[i] == 1){++i; continue;}
        if (isPrime(arr[i])) { ++ret[arr[i++]]; continue; } /// got here n as a factor
        arr[++size] = pollard_brent_montgomery( arr[i]);

        arr[i] /= arr[size];

    }

    delete[] arr;

    return ret;
}





const uint64_t mod = 993353399;

map<uint64_t, uint64_t> phi_precalc;

uint64_t phi(uint64_t n) {

    if (phi_precalc.find(n) != phi_precalc.end()) return phi_precalc[n];
    auto mp = factor(n);

    uint64_t orig_n = n;
    uint64_t result = n;

    for(auto pa : mp){
        result -= result / pa.first;
    }

    return phi_precalc[orig_n] = result;
}



vector<uint64_t> all_divisers2(uint64_t number){
    auto mp = factor(number);
    vector<uint64_t> abobus = {1};

    for(auto pair_ : mp){

    }

    for(auto pair_ : mp){
        vector<uint64_t> new_vc;
        for(int i = 0; i < abobus.size();++i){
            uint64_t mult = 1;
            for(int j = 0; j < pair_.second + 1; ++j){

                new_vc.push_back(abobus[i] * mult);
                mult *= pair_.first;
            }
        }
        abobus = new_vc;

    }

    return abobus;

}



uint64_t f(uint64_t n){

    auto vc = all_divisers2(n);
    uint64_t summ = 0;
    for(auto elem : vc){
        auto vc2 = all_divisers2(elem);

        uint64_t summ_inside = 0;

        for(auto elem2 : vc2){
            summ_inside += (elem2%mod) * (phi(n/elem2)%mod);
            summ_inside %= mod;
        }


        summ_inside *= summ_inside;
        summ_inside %= mod;



        summ += summ_inside * (phi(n/elem)%mod);
        summ %= mod;
    }

    n %= mod;

    summ += n*n;
    summ %= mod;

    return summ;

}



int main()
{


    uint64_t num_10_16 = 10000000000000000;
    uint64_t num_10_6 = 1000000;

    uint64_t BIG_BOY = 0;
    int checker = 1000;
    int a = 0;
    for(uint64_t i = num_10_16; i <= num_10_16 + num_10_6; ++i){
        if (isPrime(i)){
                a++;
            if (a % checker == 0)
                cout << i << endl;
            BIG_BOY += f(i-1);
            BIG_BOY %= mod;
        }
        ///cout << i << endl;
    }
    cout << BIG_BOY;

    ///cout << "Hello world!" << endl;
    return 0;
}
