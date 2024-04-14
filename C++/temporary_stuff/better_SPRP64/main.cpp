#include <iostream>
#include <cstdint>
#include <map>

#include <iostream>
#include <set>
#include <fstream>
using namespace std;

#include <chrono>
#include <random>
int64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937_64 mt(seed);
/// [a;b]
int64_t rnd(int64_t a, int64_t b) {
    return a + mt() % (b - a + 1);
}


using namespace std;

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

template<typename unsign, typename power_type, typename modulus_obj>
FORCE_INLINE unsign modul_pow(unsign num, power_type power, const modulus_obj& mod){
    unsign cur = 1;
    for(;power;power >>= 1) {
        if (power & 1) cur = (cur*num) % mod;
        num = num * num % mod;
    }
    return cur;
}

bool is_SPRP(uint32_t n, const uint64_t& a) {

    fast_mod64 fm_n(n);
    uint_fast8_t s = ctz(--n);
    uint64_t cur = modul_pow(a, n>>s, fm_n);
    if (cur == 1) return true;
    for (uint_fast8_t r=0; r<s; ++r) {
        if (cur == n) return true;
        cur = cur * cur % fm_n;
    }
    return false;
}

/**
deterministic bases for int64 {2, 325, 9375, 28178, 450775, 9780504, 1795265022}
*/




bool miller_rabin64(const uint64_t& n, uint64_t a, uint64_t r2, uint64_t inv, uint64_t d, uint64_t one, uint64_t minus_one){

    if (n % a == 0) return n == a;
    a %= n;

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


/*
uint64_t inv = v;
                        for(int ii = 0;ii < 5; ++ii) inv *= 2 - v * inv;


                        __uint128_t r = ((__uint128_t(1) << 127) % v) << 1;
                        if (r > v) r-= v;
                        uint64_t r2 = r;

                        uint64_t one = montmul_1_by_some_64(r2,v,inv);
                        uint64_t d = v-1;
                        uint64_t minus_one = montmul64(d,r2,v,inv);

                        ///if (v % 3 == 0 || v % 2 == 0) continue;

                        if ( miller_rabin64(v, svid1, r2, inv, d, one, minus_one)
*/



/// this is probably correct, ig
bool isPrime_det_mr_mont(uint64_t n){

    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;

    if (n % 11 == 0) return n == 11;
    if (n % 13 == 0) return n == 13;
    if (n % 17 == 0) return n == 17;
    if (n % 19 == 0) return n == 19;

    if (n % 23 == 0) return n == 23;
    if (n % 29 == 0) return n == 29;
    if (n % 31 == 0) return n == 31;
    if (n % 37 == 0) return n == 37;

    if (n % 41 == 0) return n == 41;
    if (n % 43 == 0) return n == 43;
    if (n % 47 == 0) return n == 47;
    if (n % 53 == 0) return n == 53;


    uint64_t inv = n;
    for(int ii = 0;ii < 5; ++ii) inv *= 2 - n * inv;


    __uint128_t r = ((__uint128_t(1) << 127) % n) << 1;
    if (r > n) r-= n;
    uint64_t r2 = r;

    uint64_t one = montmul_1_by_some_64(r2,n,inv);
    uint64_t d = n-1;
    uint64_t minus_one = montmul64(d,r2,n,inv);

    ///if (v % 3 == 0 || v % 2 == 0) continue;


    return miller_rabin64(n, 2, r2, inv, d, one, minus_one) && miller_rabin64(n, 3, r2, inv, d, one, minus_one) && miller_rabin64(n, 5, r2, inv, d, one, minus_one) &&
        miller_rabin64(n, 7, r2, inv, d, one, minus_one) && miller_rabin64(n, 11, r2, inv, d, one, minus_one) && miller_rabin64(n, 13, r2, inv, d, one, minus_one) &&
         miller_rabin64(n, 17, r2, inv, d, one, minus_one) && miller_rabin64(n, 19, r2, inv, d, one, minus_one);
}


unsigned int in_u32(void) { uint32_t c, x = 0; while (c = _getchar_nolock(), c < 48 || c > 57); while (47 < c && c < 58) { x = x * 10 + c - 48; c = _getchar_nolock(); } return x; }


uint64_t in_u64() { uint64_t c, x = 0; while (c = _getchar_nolock(), c < 48 || c > 57); while (47 < c && c < 58) { x = x * 10 + c - 48; c = _getchar_nolock(); } return x; }


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int64_t million = 1001ll * 1001ll;
    int64_t billion = 1001ll * 1001ll * 1001ll;
    int64_t trillion = billion * 1001ll;


    uint64_t start, shift, mult, n;


    cin >> start >> shift >> mult >> n;

    int ans = 0;
    for(int i = 0; i < n; ++i){
        start = ((start >> shift) ^ start) * mult;
        ///cout << start << endl;
        ans += isPrime_det_mr_mont(start);
    }

    cout << ans;

    return 0;
}
