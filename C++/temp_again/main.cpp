#include <iostream>

struct Mont {
    Mont(unsigned int n): mod(n) {
        inv = n;
        for(int i = 0; i < 4;++i) inv *= 2 - n * inv;

    }
    unsigned int reduce(unsigned int x) const {
        unsigned int y = mod - ((unsigned long long)(x * inv) * mod >> 32);
        ///if (y == mod){return 0;}
        return y;
    }


    unsigned int mod, inv;
};

using namespace std;
template<typename T, typename K>
T __attribute__((always_inline)) some_stuff(const T& val, const K& mul, const T& div ){
    return val - ((mul * val) >> 31) * div;
}

// fastmod computes (n mod d) given precomputed c
__attribute__((always_inline))
uint32_t fastmod(const uint32_t& n,const uint64_t& c, const uint32_t& d ) {
  uint64_t lowbits = c * n;
  return ((__uint128_t)lowbits * d) >> 64;
}

int main()
{
    uint32_t a, old_rand, b,c,n;
    cin >> a >> old_rand >> b >> c >> n;
    uint64_t ans = 0;

    uint64_t magic = UINT64_C(0xFFFFFFFFFFFFFFFF) / c + 1;

    uint32_t bi = n / 5;
    uint32_t sm = n % 5;
    for(int i = 0;i < bi;++i){
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
    }

    for(int i = 0;i < sm;++i){
        ans +=  (old_rand = fastmod((a * old_rand) + b, magic, c));
    }

    cout << ans<< endl;
    return 0;
}
