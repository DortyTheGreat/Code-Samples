#include <iostream>

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
    return miller_rabin64(n, 2) && miller_rabin64(n, 3) && miller_rabin64(n, 5) &&
        miller_rabin64(n, 7) && miller_rabin64(n, 11) && miller_rabin64(n, 13) && miller_rabin64(n, 17) && miller_rabin64(n, 19);
}


void finding_pseudos(int64_t start, int64_t end, int64_t base){

    int pseudo_primes = 0;
    for(int64_t i = start; i < end; ++i){
        if (miller_rabin64(i, base) != isPrime_det_mr_mont(i)){
            ++pseudo_primes;
            cout << "fp " << i << " " << base << endl;
        }
    }

    cout << double(pseudo_primes) / (end - start) << " "<< pseudo_primes <<  endl;

    ///return pseudo_primes;
}



int main()
{
    int64_t million = 1001ll * 1001ll;
    int64_t billion = 1001ll * 1001ll * 1001ll;
    int64_t trillion = billion * 1001ll;

    finding_pseudos(2, million * 40, 2);

    int ans = 0;
    for(int i = 1000; i < million * 10; ++i){
        ans += is_SPRP(i,2);
    }
    cout << ans << endl;

    /*finding_pseudos(billion, billion + 40 * million, 2);


    int pseudo_primes = 0;
    for(int i = 2; i < 1001 * 1001 * 10; ++i){
        if (i % (1000 * 1000) == 0){
            cout << "p " << i << endl;
        }
        if (miller_rabin64(i, 5) != isPrime_det_mr_mont(i)){
            ++pseudo_primes;
            cout << i << " " << isPrimeSimple(i) << " " << isPrime_det_mr_mont(i) << " " << miller_rabin64(i, 2) << " " << miller_rabin64(i, 325) << " " << miller_rabin64(i, 9375) << endl;
        }
    }

    */

    return 0;
}
