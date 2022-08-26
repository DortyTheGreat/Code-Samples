#include "../modular/mont_modinv.h"
#include "../modular/addmod.h"
#include "../modular/mont_mul.h"
#include "../gcd.h"
template <typename T>
T pollard_brent_montgomery(T n) {

    if (!(n & 1))
        return 2;


    // Random number Linear Congruential Generator MMIX from D.E. Knuth
    static uint64_t rng = 0xdeafbeef;
    uint64_t a = rng * 6364136223846793005ull + 1442695040888963407ull;
    uint64_t b = a * 6364136223846793005ull + 1442695040888963407ull;
    rng = (a + b) ^ (a * b);

    // y and c are "montgomery space" numbers
    T y = 1 + a % (n - 1);
    T c = 1 + b % (n - 1);
    const T m = 100;

    // nneginv is m' (mprime) in Warren
    T nneginv = mont_modinv(n).second;


    T factor = 1, r, q, x, ys,tries;
    q = r = 1;

    while(factor == 1){
        x = y;
        for (size_t i = 0; i < r; ++i) {
            y = addmod(mont_mul(y, y, n, nneginv), c, n);
        }

        for (size_t k = 0; k < r && factor == 1; k += m) {
            ys = y;

            tries = (r - k);
            if (tries > m){tries = m;}

            for (size_t i = 0; i < tries; ++i) {
                y = addmod(mont_mul(y, y, n, nneginv), c, n);
                q = mont_mul(q, x < y ? y - x : x - y, n, nneginv);
            }

            factor = gcd(q, n);
        }

        r *= 2;
    }

    if(factor == n) {
        do {
            ys = addmod(mont_mul(ys, ys, n, nneginv), c, n);
            factor = gcd(x < ys ? ys - x : x - ys, n);
        } while (factor == 1);
    }

    if (factor == n){return pollard_brent_montgomery(n);}

    return factor;
}
