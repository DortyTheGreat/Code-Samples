#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/* Trivial Sieve of Erastosthenes demonstration.
   Dana Jacobsen, 2014 */

/* test and set inside an array of 32-bit ints representing 32 odds */
#define TSTVAL(arr, val)   (arr[(val) >> 6] & (1U << (((val)>>1) & 0x1F)))
#define SETVAL(arr, val)   arr[(val) >> 6] |= 1U << (((val)>>1) & 0x1F)

static void count_primes(unsigned long base, unsigned long limit) {
  unsigned long i, n, sqrtlim = (sqrtl((double)limit) + 0.00001), count = 0;
  uint32_t* composite;
  if (base > limit) return;
  composite = (uint32_t*) calloc(limit/64+1, sizeof(uint32_t));
  /* A simple monolithic SoE should only take 4 lines */
  for (n = 3; n <= sqrtlim; n += 2)
    if (!TSTVAL(composite, n))
      for (i = n*n; i <= limit; i += 2*n)
        SETVAL(composite, i);
  /* Now go through bit array to count/print results */
  if (base <= 2 && limit >= 2)
    count++;
  base |= 1; /* make odd */
  for (n = base; n <= limit; n += 2)
    if (!TSTVAL(composite, n))
      count++;
  free(composite);
  printf("count: %lu\n", count);
}

int main(int argc, char *argv[]) {
  unsigned long n = 1000 * 1000 * 1000, base = 2;

  count_primes(base, n);
  return 0;
}
