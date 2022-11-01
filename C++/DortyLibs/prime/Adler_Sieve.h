/**
Бла-бла-бла. Немного оптимизации, чистки чужого кода.
Сурс: https://ntheory.org/sieves/pr/adler2019.c
*/

#include "../BitsPrecision/type_log_2.h"
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
