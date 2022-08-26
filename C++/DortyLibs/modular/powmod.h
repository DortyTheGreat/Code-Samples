/// base^e % mod
unsigned long long powmod_64(unsigned long long base, unsigned long long e, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }
    return result;
}

/// base^e % mod
unsigned long long powmod_32(unsigned long long base, unsigned long long e, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (unsigned long long)result * base % mod;
        base = (unsigned long long)base * base % mod;
        e >>= 1;
    }
    return result;
}
