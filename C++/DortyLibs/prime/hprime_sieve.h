/**
http://tverniquet.com/hprime/#p2
Модифицировал чутка. Но проблема: доступ к эдементу долгий. Но постройку убер быстрая.
https://github.com/tverniquet/hprime/tree/master/src/prog
*/


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

    constexpr const static uint32_t block_size = 32*1024;

    template <typename sz_t>
    static inline int num2bit(sz_t num) { return (num % 30) * 8 / 30; }



public:

    Sieve(size_t max){

        uint32_t sqrt = sqrtl(max);
        prime = (uint8_t*)calloc(max/30 + 2*block_size + sqrt + 1, 1);
        uint64_t  adj_max;
        int       a_i;

        /* adjust max to a multiple of 2,3,5 */
        for (adj_max = (max - 1) / 30 * 30 + 1, a_i = 0;
            adj_max + diff[a_i%8] <= max;
            adj_max += diff[a_i++%8]);

        uint8_t     *bmp, *prime_end, pattern[3][16*8] = {{0}};;
        uint64_t  a, cur;


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
        prime_end = prime + sqrt + 1;

        for (i = 1; i < 4; i++)
          for (bmp = prime; bmp < prime_end; bmp += bval[i]*8)
             for (j = 0; j < bval[i]; j++)
                *((uint64_t *)bmp + j) |= *((uint64_t *)pattern[i-1] + j);

        for (a = 17, a_i = 4; a <= sqrt; a += diff[a_i++%8]) {
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

        for (prime_end = prime + block_size,cur = 0; cur <= max; cur += block_size*30, prime_end += block_size) {

          for (i = 1; i < 4; i++)
             for (bmp = prime + cur/30/(8*bval[i])*(bval[i]*8); bmp < prime_end; bmp += bval[i]*8)
                for (j = 0; j < bval[i]; j++)
                   *((uint64_t *)bmp + j) |= *((uint64_t *)pattern[i-1] + j);

          for (i = 0; i < cnt; i++)
             for (; bmps[i] < cur/30 + block_size; bmps[i] += as[i])
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
