#include <inttypes.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define N 64
#include "common/bits.h"
#include "signed/runtime/signed_division.h"
#include "unsigned/runtime/unsigned_division.h"

uint64_t get_nanoseconds() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

 uint unsigned_divisor = 123456;
const uint32_t number_of_divisions = 1000000;

u128 reduce(u128 x) {
        i128 a = mod - u256::mult(x * inv, mod).high;
        if (a < 0)
            a += mod;
        return a;
    }


int main(){
    srand(time(0));
    unsigned_divisor = rand() % 10000000000;

    uint64_t reference_sum = 0, reference_start = get_nanoseconds();
    for (uint32_t n = 1; n <= number_of_divisions; n++) {
        reference_sum += n / unsigned_divisor;
    }
    uint64_t reference_end = get_nanoseconds();
    printf("Standard division took %.3f nanoseconds per division\n", 1.0 * (reference_end - reference_start) / number_of_divisions);

    uint64_t fast_sum = 0, fast_start = get_nanoseconds();

    udivdata_t dd = precompute_unsigned(unsigned_divisor);
    const uint64_t m = dd.mul;
    const uint64_t a = dd.add;
    const uint64_t s = dd.shift + N;

    for (uint32_t n = 1; n <= number_of_divisions; n++) {



        fast_sum +=  (((big_uint)n) * m + a) >> s;
    }
    uint64_t fast_end = get_nanoseconds();
    printf("Fast division took %.3f nanoseconds per division\n", 1.0 * (fast_end - fast_start) / number_of_divisions);

    assert(fast_sum == reference_sum);

}
