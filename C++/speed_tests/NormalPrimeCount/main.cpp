#include <iostream>

/**
 * Counts primes, using a hybrid approach of Meissel Lehmer + compressed Sieve of Eratosthenes algorithms.
 */

#include <cmath>
#include <vector>
#include <utility>
uint64_t intSqrt(uint64_t x){
    return pow(x,0.5);
}

uint64_t intSqrt3(uint64_t x){
    return pow(x,1/3);
}

/**
 * Compressed SoE calculator for primes + counters.
 */
std::pair<std::vector<uint32_t>, std::vector<uint32_t> >  soeCalc(uint32_t x){
    // Pierre Dusart's maximum primes: PI(x) < (x/ln x)(1 + 1.2762/ln x)
    const uint32_t maxPrimes = x / log(x) * (1 + 1.2762 / log(x));
    const uint32_t upperLimit = intSqrt(x);
    const uint32_t bmc = ((x+31) / 32); // bitmask compression
    std::vector<uint32_t> primes = std::vector<uint32_t>(maxPrimes);
    std::vector<uint32_t> pi = std::vector<uint32_t>(x);
    std::vector<uint32_t> arr = std::vector<uint32_t>(bmc);
    std::fill(arr.begin(), arr.end(), 0xFFFFFFFF);
    for (uint32_t i = 2; i <= upperLimit; i++) {
        if (arr[i >> 5] & 1 << i % 32) {
            for (uint32_t j = i * i; j < x; j += i) {
                arr[j >> 5] &= ~(1 << j % 32);
            }
        }
    }
    uint32_t count = 0;
    for (uint32_t i = 2; i < x; i++) {
        if (arr[i >> 5] & 1 << i % 32) {
            primes[count++] = i;
        }
        pi[i] = count;
    }
    return {primes, pi};
}



uint64_t Phi(uint64_t m1, uint64_t b1, const std::vector<uint32_t>& p){
    uint64_t fts = 800; // factorial table size
    uint64_t maxMem = b1 * fts + std::min(m1, fts) + 1;
    std::vector<uint64_t> memo = std::vector<uint64_t>(maxMem,0);

    auto lambda = [&](uint64_t m, uint64_t b, auto&& lambda){
        if (b == 0 || m == 0) {
            return m;
        }
        if (m >= fts) {
            return lambda(m, --b, lambda) - lambda(m / p[b], b, lambda);
        }
        uint64_t t = b * fts + m;
        if (!memo[t]) {
            memo[t] = lambda(m, --b, lambda) - lambda(m / p[b], b, lambda);
        }
        return memo[t];
    };




    return lambda(m1,b1, lambda);
}

uint64_t countPrimes(uint64_t x){
    const static uint64_t smallCount[] = {0,0,1,2,2,3};
    if (x < 6) {
        return smallCount[x];
    }
    uint64_t root2 = intSqrt(x);
    uint64_t root3 = intSqrt3(x);
    uint64_t top = (x / root3) + 1;
    auto pai = soeCalc(top + 2);
    uint64_t a = pai.second[root3 + 1], b = pai.second[root2 + 1];
    uint64_t sum = 0;
    for (uint64_t i = a; i < b; ++i) {
        uint64_t p = pai.first[i];
        sum += pai.second[x / p] - pai.second[p] + 1;
    }
    return Phi(x, a, pai.first) + a - 1 - sum;
}





using namespace std;

int main()
{
    auto p = soeCalc(1000 * 1000 * 1000);

    for(int i = 0;i < p.first.size();++i){
        cout << p.first[i] << endl;
    }
    cout << countPrimes(1000 * 1000 * 100) << endl;
    return 0;
}
