
#ifdef __cplusplus
#  include <cstdio>         // fputs(), puts(), printf()
#  include <cstdlib>        // size_t, malloc(), free()
#  include <cstring>        // memset()
#  include <cinttypes>      // uint64_t, uintmax_t
#else
#  include <stdio.h>        // fputs(), puts(), printf()
#  include <stdlib.h>       // size_t, malloc(), free()
#  include <string.h>       // memset()
#  include <inttypes.h>     // uint64_t, uintmax_t
#endif
                // vector word type


#include <iostream>




#include <iostream>
using namespace std;


constexpr uint32_t __high_type(uint16_t) {return uint32_t(0);}
constexpr uint64_t __high_type(uint32_t) {return uint64_t(0);}
constexpr __uint128_t __high_type(uint64_t) {return __uint128_t(0);}

#define high_type(x) decltype(__high_type(x(0)))

template<typename T>
class fast_div{
protected:
    high_type(T) my_magic = 1;
    unsigned char shift;

public:
    fast_div(){}
    fast_div(T val){
        shift = (sizeof(high_type(T)) * 8 - 1);
        my_magic = (my_magic << shift) / val;

        while(my_magic >= (high_type(T))(1) << (sizeof(high_type(T)) * 4) ) {
            my_magic >>= 1;--shift;
        }

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
    }


    __attribute__((always_inline)) friend T  operator/(const T& val, const fast_div<T>& fd){
        return ((fd.my_magic * val) >> fd.shift);
    }
};

template<typename T>
class fast_mod : fast_div<T>{
private:
    T div;
public:
    fast_mod(){}
    fast_mod(T val) : fast_div<T>(val), div(val){}
    __attribute__((always_inline)) friend T  operator%(const T& val, const fast_mod<T>& fm){
        return val - val/fm * fm.div;
    }
};


#include <vector>
vector<int> minmax(int a, int b){
    if (a < b) return {a,b};
    return {b,a};
}

template<typename T>
class LCM{
public:
    T mult, old_rand, add;
    fast_mod<T> fm;

    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add){
        fm = _mod;
    }

    __attribute__((always_inline)) T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};

#include <iostream>
using namespace std;
// fastmod computes (n mod d) given precomputed c

typedef unsigned int u128 __attribute__((mode(TI)));





#include <cmath>
bool isPrimeSimple(int n){
    if (n < 2) return false;
    int limit = sqrt(n) + 1;
    for(int i = 2;i<limit;++i){
        if (!(n % i)) return false;
    }
    return true;
}

uint16_t bases[]={15591,2018,166,7429,8064,16045,10503,4399,1949,1295,2776,3620,560,3128,5212,
2657,2300,2021,4652,1471,9336,4018,2398,20462,10277,8028,2213,6219,620,3763,4852,5012,3185,
1333,6227,5298,1074,2391,5113,7061,803,1269,3875,422,751,580,4729,10239,746,2951,556,2206,
3778,481,1522,3476,481,2487,3266,5633,488,3373,6441,3344,17,15105,1490,4154,2036,1882,1813,
467,3307,14042,6371,658,1005,903,737,1887,7447,1888,2848,1784,7559,3400,951,13969,4304,177,41,
19875,3110,13221,8726,571,7043,6943,1199,352,6435,165,1169,3315,978,233,3003,2562,2994,10587,
10030,2377,1902,5354,4447,1555,263,27027,2283,305,669,1912,601,6186,429,1930,14873,1784,1661,
524,3577,236,2360,6146,2850,55637,1753,4178,8466,222,2579,2743,2031,2226,2276,374,2132,813,
23788,1610,4422,5159,1725,3597,3366,14336,579,165,1375,10018,12616,9816,1371,536,1867,10864,
857,2206,5788,434,8085,17618,727,3639,1595,4944,2129,2029,8195,8344,6232,9183,8126,1870,3296,
7455,8947,25017,541,19115,368,566,5674,411,522,1027,8215,2050,6544,10049,614,774,2333,3007,
35201,4706,1152,1785,1028,1540,3743,493,4474,2521,26845,8354,864,18915,5465,2447,42,4511,
1660,166,1249,6259,2553,304,272,7286,73,6554,899,2816,5197,13330,7054,2818,3199,811,922,350,
7514,4452,3449,2663,4708,418,1621,1171,3471,88,11345,412,1559,194};

/// http://ceur-ws.org/Vol-1326/020-Forisek.pdf
bool is_SPRP(uint32_t n, uint32_t a) {
    uint32_t d = n-1, s = 0;
    while ((d&1)==0) ++s, d>>=1;
    uint64_t cur = 1, pw = d;
    while (pw) {
        if (pw & 1) cur = (cur*a) % n;
        a = ((uint64_t)a*a) % n;
        pw >>= 1;
    }
    if (cur == 1) return true;
    for (uint32_t r=0; r<s; r++) {
        if (cur == n-1) return true;
        cur = (cur*cur) % n;
    }
return false;
}

/// check factor
/// check factor
#define cf(t) if (!(x%t)){ return (x==t);}


#define _5c(a,b,c,d,e) cf(a) cf(b) cf(c) cf(d) cf(e)

bool is_prime_WTF(uint32_t x) {
    _5c(2,3,5,7,11)
    _5c(13,17,19,23,29)
    _5c(31,37,41,43,47)
    _5c(53,59,61,67,71)
    _5c(73,79,83,89,97)
    if (x<121) return (x>1);
    uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    return is_SPRP(x,bases[h]);
}



constexpr uint8_t type_log_2(uint32_t) {return 5;}
constexpr uint8_t type_log_2(uint64_t) {return 6;}
constexpr uint8_t type_log_2(__uint128_t) {return 7;}


template < typename block_type >
class Sieve{

public:
    block_type *prime;

    const static uint_fast8_t VEC_BIT =  sizeof(block_type) * 8;
    const static uint_fast8_t VEC_LOG = type_log_2(block_type(0));

    static inline unsigned get(block_type *vec, uintmax_t k) {
        return (vec[k >> VEC_LOG] >> (k & (VEC_BIT - 1))) & 1;
    }
    // Clear bit k in the bit vector vec.
    static inline void clear(block_type *vec, uintmax_t k) {
        vec[k >> VEC_LOG] &= ~((block_type)1 << (k & (VEC_BIT - 1)));
    }

public:

    Sieve(size_t n){
        n = n ? (n - 1) >> 1 : 0;   // half of n bits for just the odds
        n |= VEC_BIT - 1;           // round up to fill the last word
        size_t len = (n >> 3) + 1;

        prime = (block_type *)malloc(len);

        len >>= VEC_LOG - 3;
        prime[0] = ~1;                      // 1 is not prime
        for (unsigned k = 1, p = 3, q = 1; q < VEC_BIT/4;
                      k++, p += 2, q += k)
            if (get(prime, k)) {
                for (unsigned next = q << 2; next < VEC_BIT; next += p){
                    clear(prime, next);
                }
            }
        if (len == 1)
            return;
        // sum the odd primes in the first word, in order to allocate
        // space for p masks for each odd prime p -- initialize the
        // masks to all ones
        unsigned sum = 0;
        for (unsigned k = 1; k < VEC_BIT; ++k)
            if (get(prime, k))
                sum += 2 * k + 1;
        sum <<= VEC_LOG - 3;        // bytes for s vec_t's
        block_type *mask = (block_type *)malloc(sum);

        memset(mask, ~0, sum);
        // build a set of repeating masks for the primes from 3 to
        // 2*VEC_BIT, for which one or more bits are reset in every
        // word, where off is the offset of the current p masks in
        // mask[]
        for (unsigned k = 1, p = 3, off = 0; k < VEC_BIT;
                      ++k, p += 2)
            if (get(prime, k)) {
                size_t next = (k + VEC_BIT * (p - 1)) % p;
                size_t end = (p > len - 1 ? len - 1 :
                                            (size_t)p) << VEC_LOG;
                for (; next < end; next += p) {
                    clear(mask + off, next);
                }
                off += p;
            }
        // now sieve the entire bit vector after the first word using
        // the repeating masks -- do a chunk at a time to take
        // advantage of the processor cache (the chunk size was
        // determined empirically, buying half a second over going
        // through the entire bit vector for each prime's set of masks)

        size_t start = 1;
        do {
            // last is the last vec_t index of this chunk, not past
            // the end
            size_t end = start + ((size_t)1 << 12);
            if (end > len || end < start)
                end = len;
            // initialize this chunk to all 1's
            memset(prime + start, ~0,
                  (end - start) << (VEC_LOG - 3));
            // apply masks for each prime to the indices
            // start..end-1 -- for speed, handle the edge cases
            // outside of the center loop, which does the vast
            // majority of the work
            for (unsigned k = 1, p = 3, off = 0;
                          k < VEC_BIT; k++, p += 2)
                if (get(prime, k)) {
                    size_t next = start;
                    size_t i = (start - 1) % p;
                    do {
                        prime[next++] &= mask[off + i++];
                    } while (i < p && next < end);

                    while (end - next >= p) {
                        for (i = 0; i < p;++i ){
                            prime[next + i] &= mask[off + i];
                        }
                        next += p;
                    }

                    for (i = 0; next < end; ++i, ++next)
                        prime[next] &= mask[off + i];
                    off += p;
                }
            start = end;
        } while (start < len);

        // done with masks
        free(mask);


        uintmax_t incr = ((uintmax_t)1 << 19); /// Это что-то подбирали опытным путём наверное или это L1_CACHE_SIZE

        for(start = 0; start <= n ; start += incr){
            // last is the last bit location for this chunk, not
            // past the end
            uintmax_t last = start + (incr - 1);
            if (last > n) last = n;
            // clear composites at bit locations start..last

            for (uintmax_t k = VEC_BIT;;++k) {
                if (get(prime, k)) {
                    // start at the location of p squared (before
                    // there, primes less than p already cleared
                    // multiples of p)
                    uintmax_t next = 2 * k * (k + 1);
                    // p is the prime that corresponds to bit
                    // location k
                    uintmax_t p = 2 * k + 1;
                    // if the square of p is past the end of this
                    // chunk, then all of the subsequent primes
                    // will be too
                    if (next > last)
                        break;
                    // add just enough p's to the bit location to
                    // put it in this chunk (this effectively adds
                    // just enough 2*p's to the corresponding odd
                    // integer)
                    if (next < start) {
                        next = k + p - start % p;
                        if (next >= p) next -= p;
                        next += start;
                    }
                    // clear composites, effectively adding 2*p to
                    // the current odd integer in order to get to
                    // the next odd integer
                    for (; next <= last; next += p) {
                        clear(prime, next);
                    }
                }

            }

        }

    }

    bool isPrime(int num){
        if (num < 3) return num == 2;
        if (num % 2 == 0) return false;
        num /= 2;
        return prime[num / 64] & (1ull << (num % 64));
    }

    ~Sieve(){
        free(prime);
    }
};

#include <vector>
uint64_t factorize(int number){
    uint64_t ret = 0;
    while (!(number % 2)){
        number /= 2;
        ret += 2;
    }
    for(int factor = 3; factor * factor <= number; factor += 2 ){
        while ( !(number % factor) ){
            number /= factor;
            ret += factor;
        }
    }
    if(number != 1) ret += number;
    return ret;
}

using namespace std;
int main(void) {
    // generate the primes vector



    Sieve<uint64_t> S(1001 * 1000 * 1000);

    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t> myl(a,ol,b,c);
    uint64_t ans = 0;
    for(int i = 0;i< n;++i){
        ans += S.isPrime( myl.get());
    }
    cout << ans;


    // clean up

    return 0;
}
