#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

int gcd(int a, int b) {
    return a ? gcd(b % a, a) : b;
}

int powmod(int a, int b, int p) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// Finds the primitive root modulo p
int generator(int p) {
    vector<int> fact;
    int phi = p-1, n = phi;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back(n);

    for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (int factor : fact) {
            if (powmod(res, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return res;
    }
    return -1;
}

bool isPerfectSquareUnderModulo(int64_t number, int64_t mod){
    int n = mod, k = 2, a = number;
    if (a == 0) {
        return 0;
    }

    int g = generator(n);

    // Baby-step giant-step discrete logarithm algorithm
    int sq = (int) sqrt (n + .0) + 1;
    vector<pair<int, int>> dec(sq);
    for (int i = 1; i <= sq; ++i)
        dec[i-1] = {powmod(g, i * sq * k % (n - 1), n), i};
    sort(dec.begin(), dec.end());
    for (int i = 0; i < sq; ++i) {
        int my = powmod(g, i * k % (n - 1), n) * a % n;
        auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0));
        if (it != dec.end() && it->first == my) {
            return 1;
        }
    }
    return 0;
}

bool isPerfectForthUnderModulo(int64_t number, int64_t mod){
    int n = mod, k = 4, a = number;
    if (a == 0) {
        return 0;
    }

    int g = generator(n);

    // Baby-step giant-step discrete logarithm algorithm
    int sq = (int) sqrt (n + .0) + 1;
    vector<pair<int, int>> dec(sq);
    for (int i = 1; i <= sq; ++i)
        dec[i-1] = {powmod(g, i * sq * k % (n - 1), n), i};
    sort(dec.begin(), dec.end());
    for (int i = 0; i < sq; ++i) {
        int my = powmod(g, i * k % (n - 1), n) * a % n;
        auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0));
        if (it != dec.end() && it->first == my) {
            return 1;
        }
    }
    return 0;
}

#define FORCE_INLINE __attribute__((always_inline)) inline

bool isPrimeSimple(uint64_t x){
    if (x == 2) return true;
    int res = 0;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

FORCE_INLINE auto ctz(const uint64_t& num){
    return __builtin_ctzll(num);
}

FORCE_INLINE auto ctz(const uint32_t& num){
    return __builtin_ctz(num);
}



/// thx: https://itecnote.com/tecnote/c-efficient-computation-of-the-high-order-bits-of-a-32-bit-integer-multiplication/
uint64_t ret, low;
/// Возвращает большую часть от 128: 64x64
FORCE_INLINE uint64_t hmul64(const uint64_t& a,const uint64_t& b){
    asm ("mulq %3" : "=a"(low), "=d"(ret) : "a"(a), "g"(b) : "cc");
    return ret;
}

class fast_div64{
protected:
    uint64_t my_magic = 1;
    uint_fast8_t shift;

public:
    fast_div64(){}
    fast_div64(const uint64_t& val){
        shift = (127);

        __uint128_t temp = (__uint128_t(1) << 127) / val;
        shift = __builtin_clzll(temp  >> 64); /// zeros
        my_magic = (temp >> (64-shift));
        --shift;

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
        ///cout << my_magic << " " << (int)shift << endl;
    }


    FORCE_INLINE friend uint64_t operator/(const uint64_t& val, const fast_div64& fd){



        return (hmul64(val,fd.my_magic) >> fd.shift ) ;
    }
};


class fast_mod64 : fast_div64{
private:
    uint64_t div;
public:
    fast_mod64(){}
    fast_mod64(uint64_t val) : fast_div64(val), div(val){}
    FORCE_INLINE friend uint64_t operator%(const uint64_t& val, const fast_mod64& fm){
        return val - val/fm * fm.div;
    }
};

/// Computes (a - b) % m, assumes a < m and b < m.
template<typename T>
FORCE_INLINE T submod(const T& a,const T& b,const T& m) {
    if (b > a) return m - b + a;
    return a - b;
}

FORCE_INLINE uint64_t montmul64(const uint64_t& a,const uint64_t& b,const uint64_t& mod,const uint64_t& inv){
    //a *= b;
    uint64_t high = hmul64(a,b);

    return submod(high, hmul64((low * inv), mod), mod);
}


/// 1 * b
FORCE_INLINE uint64_t montmul_1_by_some_64(const uint64_t& b, const uint64_t& mod, const uint64_t& inv){
    //a *= b;

    /// low32 = b
    return mod -  hmul64((b * inv), mod);
}

/// base^exp, also requires 1 in mont (as x).
FORCE_INLINE uint64_t montpow64(uint64_t base, uint64_t exp, uint64_t x, const uint64_t& mod, const uint64_t& inv ){
    /// one = montmul_1_by_some_64(r2,n,inv)
    while (exp) {
        if (exp & 1) {
            x = montmul64(x,base,mod,inv);
        }
        base = montmul64(base,base,mod,inv);
        exp >>= 1;
    }

    return x;
}



bool miller_rabin64(const uint64_t& n, uint64_t a) {

    uint64_t inv = n;
    for(int i = 0;i < 5; ++i) inv *= 2 - n * inv;


    __uint128_t r = ((__uint128_t(1) << 127) % n) << 1;
    if (r > n) r-= n;
    uint64_t r2 = r;

    uint64_t one = montmul_1_by_some_64(r2,n,inv);
    uint64_t d = n-1;
    uint64_t minus_one = montmul64(d,r2,n,inv);

    /// prep ^^^

    a = montmul64(a,r2,n,inv);

    /// Montgomery stuff done


    uint_fast8_t s = ctz(d);
    d >>= s;

    uint64_t x = montpow64(a, d, one, n, inv);

    if (x == one) {
        return 1;
    }

    while(s--){
        if (x == minus_one) return true;
        x = montmul64(x,x,n,inv);
    }
    return false;




}

bool isPrime(uint64_t n){
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    if (n % 11 == 0) return n == 11;
    if (n % 13 == 0) return n == 13;
    if (n % 17 == 0) return n == 17;
    if (n % 19 == 0) return n == 19;
    return miller_rabin64(n, 2) && miller_rabin64(n, 3) && miller_rabin64(n, 5) &&
        miller_rabin64(n, 7) && miller_rabin64(n, 11) && miller_rabin64(n, 13) && miller_rabin64(n, 17) && miller_rabin64(n, 19);
}

/**

2^(n - 1) === 1 (mod n) - just a pseudo

If both numbers q and 2q - 1 are primes (q is in the sequence A005382)
 and n = q*(2q-1) then 2^(n-1) == 1 (mod n) (n is in the sequence) if
  and only if q is of the form 12k + 1. The sequence
   2701, 18721, 49141, 104653, 226801, 665281, 721801, ... is related.
    This subsequence is also a subsequence of the sequences A005937 and A020137. - Farideh Firoozbakht, Sep 15 2006



*/


// This program finds all numbers x such that x^k = a (mod n)
int main() {
    cout << miller_rabin64(42799,2);
    ifstream fin("pseudos.txt");

    vector<int64_t> table_pseudos;

    for(int i = 0; i < 9000; ++i){
        int64_t a,b;
        fin >> a >> b;
        table_pseudos.push_back(b);
    }

    int64_t b = 2; /// base that we are checking, 2 is pretty famous (https://oeis.org/A001262)

    set<int64_t> pseudos;

    for(int small_num = 2; small_num < 300; ++small_num){
        for(int q = 2/* 1 */; q < 1000 * 10; ++q){
            int64_t p1 = q; ///2 * q + 1;
            int64_t p2 =  2*q - 1;///2 * q * small_num + 1;

            int64_t checking = p1 * p2;

            if (!(isPrime(checking)) && (checking % b != 0) && miller_rabin64(checking, b) ) pseudos.insert(checking);



        }
    }



    int i = 0;
    for(auto e : pseudos){
        cout << e << " " << table_pseudos[i] << endl;
        if (i > 8000) break;
        ++i;
    }

}
