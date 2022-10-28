// sieve.c -- Copyright (C) 2019 by Mark Adler, all rights reserved
//
// Make a bit vector of primes. This takes less than one second to
// create a bit vector for all of the primes less than 2x10^9 on a
// 2.5 GHz Kaby Lake Core i7 (I7-7660U). The size of the resulting
// bit vector of odd primes is 120 MB.
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
#define local static
// Bit vector word type -- should be the processor register size.
typedef uint64_t vec_t;                 // vector word type
#define VEC_BIT 64                      // bits in vec_t
#define VEC_LOG 6                       // base 2 log of VEC_BIT
// Get bit k from the bit vector vec, returning 0 or 1.
local inline unsigned get(vec_t *vec, uintmax_t k) {
    return (vec[k >> VEC_LOG] >> (k & (VEC_BIT - 1))) & 1;
}
// Clear bit k in the bit vector vec.
local inline void clear(vec_t *vec, uintmax_t k) {
    vec[k >> VEC_LOG] &= ~((vec_t)1 << (k & (VEC_BIT - 1)));
}
// Return an allocated bit vector with the bits corresponding to
// the odd numbers less than or equal to n. A bit is set only if
// the corresponding odd number is prime. The least significant bit
// of the first word represents 1, the next bit represents 3, and
// so on. (1 is not prime.) All of the bits in the last returned
// word of the vector properly indicate primality or not, even if
// those bits correspond to numbers > n. sieve() generates the bit
// vector using Eratosthenes' sieve. sieve() returns NULL if the
// memory for the bit vector could not be allocated.
//
// sieve() builds the vector in two passes: the first pass clearing
// composites that are multiples of primes less than 2*VEC_BIT,
// which in general clears multiple bits per word; and the second
// pass which clears multiples of larger primes, which clear one
// bit at a time in scattered words. Both passes operate on chunks
// of the bit vector at a time, in order to take advantage of
// processor memory caches.
local vec_t *sieve(uintmax_t n) {
    // allocate bit vector with one bit for each odd number
    n = n ? (n - 1) >> 1 : 0;   // half of n bits for just the odds
    n |= VEC_BIT - 1;           // round up to fill the last word
    uintmax_t bytes = (n >> 3) + 1;     // bytes in the bit vector
    size_t len = (size_t)bytes;
    if (len != bytes)
        return NULL;                    // overflow of size_t
    vec_t *prime = (vec_t *)malloc(len);
    if (prime == NULL)
        return NULL;
    len >>= VEC_LOG - 3;                // vec_t's in the vector
    // initialize the odd primes in the first word of the bit
    // vector here p is the prime being sieved, k is the index of p
    // -- in the bit vector, and q is one-fourth of the index of
    // the square of p in the bit vector
    prime[0] = ~1;                      // 1 is not prime
    for (unsigned k = 1, p = 3, q = 1; q < VEC_BIT/4;
                  k++, p += 2, q += k)
        if (get(prime, k)) {
            unsigned next = q << 2;     // start at p squared
            do {
                clear(prime, next);
                next += p;
            } while (next < VEC_BIT);
        }
    if (len == 1)
        return prime;
    // sum the odd primes in the first word, in order to allocate
    // space for p masks for each odd prime p -- initialize the
    // masks to all ones
    unsigned sum = 0;
    for (unsigned k = 1; k < VEC_BIT; k++)
        if (get(prime, k))
            sum += 2 * k + 1;
    sum <<= VEC_LOG - 3;        // bytes for s vec_t's
    vec_t *mask = (vec_t *)malloc(sum);
    if (mask == NULL) {
        free(prime);
        return NULL;
    }
    memset(mask, ~0, sum);
    // build a set of repeating masks for the primes from 3 to
    // 2*VEC_BIT, for which one or more bits are reset in every
    // word, where off is the offset of the current p masks in
    // mask[]
    for (unsigned k = 1, p = 3, off = 0; k < VEC_BIT;
                  k++, p += 2)
        if (get(prime, k)) {
            size_t next = (k + VEC_BIT * (p - 1)) % p;
            size_t end = (p > len - 1 ? len - 1 :
                                        (size_t)p) << VEC_LOG;
            while (next < end) {
                clear(mask + off, next);
                next += p;
            }
            off += p;
        }
    // now sieve the entire bit vector after the first word using
    // the repeating masks -- do a chunk at a time to take
    // advantage of the processor cache (the chunk size was
    // determined empirically, buying half a second over going
    // through the entire bit vector for each prime's set of masks)
    {
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
                        i = 0;
                        do {
                            prime[next + i] &= mask[off + i];
                        } while (++i < p);
                        next += p;
                    }
                    i = 0;
                    while (next < end)
                        prime[next++] &= mask[off + i++];
                    off += p;
                }
            start = end;
        } while (start < len);
    }
    // done with masks
    free(mask);
    // sieve from the smallest prime greater than twice VEC_BIT to
    // the square root of largest integer represented in the bit
    // vector, for which zero or one bits are reset in each word
    // for each prime -- break up the job into chunks of the
    // vector, going through all of the primes for each chunk (the
    // chunk size was determined empirically -- this is about three
    // times as fast as going through the entire bit vector for
    // each prime)
    {
        uintmax_t start = 0;
        do {
            // last is the last bit location for this chunk, not
            // past the end
            uintmax_t last = start + (((uintmax_t)1 << 19) - 1);
            if (last > n || last < start)
                last = n;
            // clear composites at bit locations start..last
            uintmax_t k = VEC_BIT;
            for (;;) {
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
                        if (next >= p)
                            next -= p;
                        next += start;
                    }
                    // clear composites, effectively adding 2*p to
                    // the current odd integer in order to get to
                    // the next odd integer
                    while (next <= last) {
                        clear(prime, next);
                        next += p;
                    }
                }
                k++;
            }
            // go to the next chunk
                = last + 1;
        } while (start <= n);
    }
    // prime has now been sieved by the odd primes up to the square
    // root of the largest represented integer, clearing all
    // composites in the bit vector
    return prime;
}
// Find primes up to 2,000,000,000. There are 98,222,287 of them.
#define N 1000000000
// Find all primes <= N and count them.
int main(void) {
    // generate the primes vector
    vec_t *prime = sieve(N);
    if (prime == NULL) {
        fputs("out of memory\n", stderr);
        return 1;
    }
    // count the primes <= N to check for correctness
    intmax_t p = 1;
    for (size_t i = 0; i < ((N - 1) >> (VEC_LOG + 1)); i++)
        p += __builtin_popcountll(prime[i]);
    p += __builtin_popcountll(
            prime[(N - 1) >> (VEC_LOG + 1)] &
            (((vec_t)2 << (((N - 1) >> 1) & (VEC_BIT - 1))) - 1));
    printf("%jd\n", p);
    // clean up
    free(prime);
    return 0;
}
