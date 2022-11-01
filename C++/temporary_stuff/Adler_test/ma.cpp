#line 1 "main.cpp"
#include <iostream>
using namespace std;

#line 1 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\BitsPrecision\\high_type.h"
constexpr uint32_t __high_type(uint16_t) {return 0;}
constexpr uint64_t __high_type(uint32_t) {return 0;}
constexpr __uint128_t __high_type(uint64_t) {return 0;}

#define high_type(x) decltype(__high_type(x(0)))
#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\fast_calculations\\fast_div.h"
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
#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\fast_calculations\\fast_mod.h"
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
#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\fast_calculations\\LCM.h"
template<typename T>
class LCM : fast_mod<T>{
public:
    T mult, old_rand, add;

    LCM(T _mult,T _old_rand,T _add,T _mod) : fast_mod<T>(_mod), mult(_mult), old_rand(_old_rand), add(_add){}

    __attribute__((always_inline)) T get(){
        return old_rand = (mult * old_rand + add) % (*this);
    }

};
#line 5 "main.cpp"


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

/**
Это лишь интересный концпет, на практике его применение вероятнее всего будет сужено, но всё же...
Идея в том, чтобы проверять число не на всю делимость, и даже не только по нечётным, а строго по простым, в добавок используя
трюки из модульной арифметики выходит крутой чикибабонёнок.
*/

#line 1 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\prime\\Adler_Sieve.h"
/**
Бла-бла-бла. Немного оптимизации, чистки чужого кода.
Сурс: https://ntheory.org/sieves/pr/adler2019.c
*/

#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\BitsPrecision\\type_log_2.h"
constexpr uint8_t type_log_2(uint32_t) {return 5;}
constexpr uint8_t type_log_2(uint64_t) {return 6;}
constexpr uint8_t type_log_2(__uint128_t) {return 7;}
#line 7 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\prime\\Adler_Sieve.h"
#include <cstring>
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
        return prime[num / VEC_BIT] & (block_type(1) << (num % VEC_BIT));
    }

    ~Sieve(){
        free(prime);
    }
};
#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\modular\\binary_inverse.h"
template<typename T>
T binary_inverse(const T& n){
    T inv = n;

    for (uint8_t i = 0; i < type_log_2(T(0)); i++)
        inv *= 2 - n * inv;
    return inv;
}
#line 2 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\fast_calculations\\fast_divisibility.h"
template <typename T>
class fast_divisibility{
public:
    T inverse;
    T limit;
public:
    fast_divisibility() = default;
    fast_divisibility(const T& mod){
        limit = ~T(0) / mod;
        inverse = binary_inverse(mod);
    }
    __attribute__((always_inline)) constexpr bool check(const T& data) const{
        return (data*inverse) <= limit;
    }
};
#line 31 "main.cpp"
#include <cmath>
struct divisor : fast_divisibility<uint32_t>{
    uint32_t div;
    divisor(const uint32_t& n) : fast_divisibility<uint32_t>(n),div(n) {}
    divisor() = default;
};

#line 1 "C:\\Users\\Saha2\\Desktop\\Code-Samples\\C++\\DortyLibs\\prime\\pi_upper_bound.h"
// Pierre Dusart's maximum primes: PI(x) < (x/ln x)(1 + 1.2762/ln x)
template<typename T>
constexpr T pi_upper_bound(const T& x){
    return x / log(x) * (1 + 1.2762 / log(x));
}
#line 39 "main.cpp"
class PrimeFactorizer{
    divisor *primes;
    size_t h;
public:

    PrimeFactorizer(size_t size){
        size = sqrt(size);
        Sieve<uint64_t> S(size);
        primes = new divisor[pi_upper_bound(size)];
        h = 0;
        for(size_t i = 3; i <= size;++i){
            if (S.isPrime(i)){
                primes[h++] = i;
                ///cout << i << endl;
            }
        }
    }

    size_t prime_summ(size_t number){
        if (number < 2) return 0;
        size_t ret = 0;
        while ( number % 2 == 0 ){ret += 2; number /= 2;}



        for(size_t i = 0; i < h; ++i){
            while ( primes[i].check(number) ){ret += primes[i].div; number /= primes[i].div;}
        }

        if (number != 1) ret += number;
        return ret;
    }


};



using namespace std;
int main(void) {

    PrimeFactorizer PF(1000 * 1000 * 1000);

    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t> myl(a,ol,b,c);
    uint64_t ans = 0;


    for(int i = 0;i < n; ++i){
        ans += PF.prime_summ(myl.get());
    }
    cout << ans;


    // clean up

    return 0;
}
