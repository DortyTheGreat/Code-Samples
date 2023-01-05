

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



#define FORCE_INLINE __attribute__((always_inline)) inline

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


template<typename T, typename quick_mod = T>
class LCM{
public:
    T mult, old_rand, add;
    quick_mod fm;
    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add), fm(_mod){}
    FORCE_INLINE T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};



/// check factor
/// check factor




constexpr uint8_t type_log_2(uint32_t) {return 5;}
constexpr uint8_t type_log_2(uint64_t) {return 6;}
constexpr uint8_t type_log_2(__uint128_t) {return 7;}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>


class Sieve{

public:
    uint8_t *prime;

    constexpr const static uint8_t diff[8] = {6,4,2,4,2,4,6,2};
    constexpr const static uint8_t bval[8] = {1,7,11,13,17,19,23,29};

    constexpr const static uint8_t back_tracker[30] = {0,1 << 0,0,0,0,0,0,1 << 1,0,0,0,1 << 2,0,1 << 3,0,0,0,1 << 4,0,1 << 5,0,0,0,1 << 6,0,0,0,0,0,1 << 7};

    template <typename sz_t>
    static inline int num2bit(sz_t num) { return (num % 30) * 8 / 30; }



public:

    Sieve(size_t max){


        prime = (uint8_t*)calloc(max/30 + 2*32*1024 + sqrtl(max) + 1, 1);
        uint64_t  adj_max;
        int       a_i;

        /* adjust max to a multiple of 2,3,5 */
        for (adj_max = (max - 1) / 30 * 30 + 1, a_i = 0;
            adj_max + diff[a_i%8] <= max;
            adj_max += diff[a_i++%8]);

        uint8_t     *bmp, *prime_end, pattern[3][16*8] = {{0}};;
        uint64_t  a, cur;
        uint32_t sqrt = sqrtl(max);

        uint32_t *as   = (uint32_t*)malloc(sizeof(uint32_t) * (sqrt / 4 + 1000)),
                *bmps = (uint32_t*)malloc(sizeof(uint32_t) * (sqrt / 4 + 1000)),
                *offs = (uint32_t*)malloc(sizeof(uint32_t) * 8 * (sqrt / 4 + 1000));
        int i,j,r,cnt = 0;


        /* Init lower primes */
        for (i = 1; i < 4; i++)
          for (r = bval[i], a_i = 0; r < bval[i] * 30 * 8; r += bval[i] * diff[a_i++ % 8])
             pattern[i-1][r / 30] |= 1 << num2bit(r);

        /*
        * Find sieving primes
        */
        prime_end = prime + (int64_t)sqrtl(max) + 1;

        for (i = 1; i < 4; i++)
          for (bmp = prime; bmp < prime_end; bmp += bval[i]*8)
             for (j = 0; j < bval[i]; j++)
                *((uint64_t *)bmp + j) |= *((uint64_t *)pattern[i-1] + j);

        for (a = 17, a_i = 4; a <= sqrtl(max); a += diff[a_i++%8]) {
          if (prime[a / 30] & 1 << (a_i%8))
             continue;

          as[cnt] = a;
          for (i = 0; i < 8; i++)
             offs[cnt*8 + num2bit(a * bval[i])] = a * bval[i] / 30;

          for (bmp = prime + (uint64_t)a * (a / 30); bmp < prime_end; bmp += a)
             for (i = 0; i < 8; i++)
                *(bmp + offs[cnt*8 + i]) |= 1 << i;

          bmps[cnt++] = (bmp - prime);
        }

        /*
        * Calculate blocks
        */
        prime_end = prime + 32*1024;
        for (cur = 0; cur <= max; cur += 32*1024*30, prime_end += 32*1024) {

          for (i = 1; i < 4; i++)
             for (bmp = prime + cur/30/(8*bval[i])*(bval[i]*8); bmp < prime_end; bmp += bval[i]*8)
                for (j = 0; j < bval[i]; j++)
                   *((uint64_t *)bmp + j) |= *((uint64_t *)pattern[i-1] + j);

          for (i = 0; i < cnt; i++)
             for (; bmps[i] < cur/30 + 32*1024; bmps[i] += as[i])
                for (j = 0; j < 8; j++)
                   *(prime + bmps[i] + offs[i*8 + j]) |= 1 << j;
        }


        /* First byte gets clobbered for the first block */
        prime[0] = 0x1;

        free(as);
        free(bmps);
        free(offs);

    }

    bool isPrime(int num){
        if (num < 30){
            if (num < 2) return false;
            if (num % 2 == 0) return num == 2;
            if (num % 3 == 0) return num == 3;
            if (num % 5 == 0) return num == 5;
        }
        auto bt = back_tracker[num % 30];
        if (!bt) return false;
        ///cout <<endl <<num << " " << int(back_tracker[num % 30]) << endl;
        return !(prime[num / 30] & bt);
    }

    ~Sieve(){
        free(prime);
    }
};



using namespace std;
int main(void) {
    // generate the primes vector



    Sieve S(1001 * 1000 * 1000);

    for(int i = 0;i< 100;++i){
        ///cout << endl <<"b " << i <<" " << int(S.prime[i / 30]) << endl;
        ///cout << i << " " << S.isPrime(i) << endl;
    }

    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t> myl(a,ol,b,c);
    uint64_t ans = 0;
    for(int i = 0;i< n;++i){
        ans += S.isPrime( myl.get());
    }
    cout << ans;


    return 0;
}
