/// https://github.com/armchaircaver/Factors/blob/c475fd6d4116ed9da6b34f20be35f712cf92235a/Pollard%20Rho%20trials/Pollard%20Rho%20Montgomery.cpp


// source : http://coliru.stacked-crooked.com/a/f57f11426d06acd8
// referenced in https://projecteuler.chat/viewtopic.php?t=3776

/*
 A fun property of Pollard-Brent's factorization algorithm
Post by nightcracker » Mon Jan 12, 2015 12:15 pm
As some of you know, you can speed up repeated modular multiplication using Montgomery reduction.
The conversion takes some time, but if you do quite some multiplications it should speed up by a lot.
At first look Pollard-Brent doesn't seem like it could benefit that much from this,
since it doesn't do too many modular multiplications in a row,
so you'd think you'd spend too much time converting back and forth.
However, as it turns out, absolutely no conversions are needed!
The initial random parameters are supposed to be uniform over [1, N),
so there's absolutely no reason to convert them - the result would be another uniform random variable over [1, N).
So we'll just generate random parameters as usual, and treat them as if they were of the form aR mod N.
Then in the algorithm you replace all multiplications with Montgomery multiplication.
I don't know exactly how the end result is still correct,
but it I think just so happens to be because you are working with aR mod N and R and N are coprime,
thus not affecting the algorithm logic which checks gcd(aR mod N, N) = 1.
Either way, here's some code implementing this
(sorry, only GCC on x86-64 because I need inline assembly): http://coliru.stacked-crooked.com/a/f57f11426d06acd8
This trick made the implementation 4 times faster.
*/

#include <cstdint>
#include <iostream>
#include <tuple>
#include <intrin.h>

std::pair<uint64_t, uint64_t> mulu64(uint64_t a, uint64_t b) {
    uint64_t high, low;
    low = _umul128(a, b, &high);
    return std::make_pair(high, low);
}


// Computes (a + b) % m, assumes a < m and b < m.
uint64_t addmod64(uint64_t a, uint64_t b, uint64_t m) {
    if (b >= m - a) return a - m + b;
    return a + b;
}

// Computes aR * bR mod N with R = 2**64.
uint64_t montmul64(uint64_t a, uint64_t b, uint64_t N, uint64_t Nneginv) {
    uint64_t Th, Tl, m, mNh, mNl;

    Tl = _umul128(a, b, &Th);
    m = Tl * Nneginv;
    mNl = _umul128(m, N, &mNh);

    /*
     bool lc = Tl + mNl < Tl;
     uint64_t th = Th + mNh + lc;
     bool hc = (th < Th) || (th == Th && lc);
     if (hc || (th >= N)) th = th - N;
     */

     // my attempt at speeding up.

    uint64_t tl2, th2;
    uint32_t low_carry_in = 0;

    uint32_t carryL = _addcarry_u64(low_carry_in, Tl, mNl, &tl2);
    uint32_t carryH = _addcarry_u64(carryL, Th, mNh, &th2);

    if (carryH || (th2 >= N)) th2 = th2 - N;

    return th2;
}

// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

inline std::pair<uint64_t, uint64_t> mont_modinv(uint64_t m) {
    uint64_t a = 1ull << 63;
    uint64_t u = 1;
    uint64_t v = 0;

    while (a > 0) {
        a = a >> 1;
        if ((u & 1) == 0) {
            u = u >> 1; v = v >> 1;
        }
        else {
            u = ((u ^ m) >> 1) + (u & m);
            v = (v >> 1) + (1ull << 63);
        }
    }
    return std::make_pair(u, v);
}

uint64_t prgcd(uint64_t a, uint64_t b) {
    if (a == b) return a;
    while (b > 0) {
        uint64_t tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

// Returns a factor of n, assumes n is odd.
uint64_t pollard_brent_montgomery(uint64_t n) {

    if ((n & 1) == 0) {
        printf("Unable to run pollard_brent_montgomery for even value n=%llu\n", n);
        exit(1);
    }

    // Random number Linear Congruential Generator MMIX from D.E. Knuth
    static uint64_t rng = 0xdeafbeef;
    uint64_t a = rng * 6364136223846793005ull + 1442695040888963407ull;
    uint64_t b = a * 6364136223846793005ull + 1442695040888963407ull;
    rng = (a + b) ^ (a * b);

    // y and c are "montgomery space" numbers
    uint64_t y = 1 + a % (n - 1);
    uint64_t c = 1 + b % (n - 1);
    uint64_t m = 100;

    // nneginv is m' (mprime) in Warren
    uint64_t nneginv = mont_modinv(n).second;


    uint64_t g=1, r, q, x, ys;
    q = r = 1;

    do {
        x = y;
        for (uint64_t i = 0; i < r; ++i) {
            y = addmod64(montmul64(y, y, n, nneginv), c, n);
        }

        for (uint64_t k = 0; k < r && g == 1; k += m) {
            ys = y;
            for (uint64_t i = 0; i < std::min(m, r - k); ++i) {
                y = addmod64(montmul64(y, y, n, nneginv), c, n);
                q = montmul64(q, x < y ? y - x : x - y, n, nneginv);
            }

            g = prgcd(q, n);
        }

        r *= 2;
    } while (g == 1);

    if (g == n) {
        do {
            ys = addmod64(montmul64(ys, ys, n, nneginv), c, n);
            g = prgcd(x < ys ? ys - x : x - ys, n);
        } while (g == 1);
    }

    return g;
}

int tries = 0;
uint64_t pollard_brent_montgomery_retry(uint64_t n) {
    uint64_t f=0;
    tries = 0;
    do {
        f = pollard_brent_montgomery(n);
        tries++;
     } while (f == n);
    return f;
}

int getTries() {
    return tries;
}

/**

911787119
911838119
911868119
911919119
912161219
912323219
912373219
912464219
912484219
912535219
912707219
912727219
912797219
912808219
912898219
913050319
913212319
913272319
913282319
913323319
913404319
913414319
913474319
913575319
913747319
913878319
913939319
913969319
914151419
914252419
914282419
914393419
914505419
914565419
914676419
914909419

1073741827ull * 1073741831ull

*/

int main(){
    std::cout << pollard_brent_montgomery_retry(914676419ull * 913323319ull) << std::endl;
    std::cout << getTries() << std::endl;
    return 0;
}
