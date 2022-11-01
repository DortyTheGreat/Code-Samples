#include <iostream>
using namespace std;

#include "../../DortyLibs/fast_calculations/LCM.h"


uint64_t factorize(int number){
    uint64_t ret = 0;
    while (!(number % 2)){
        number /= 2;
        ret += 2;
    }
    for(int factor = 3; factor * factor <= number; factor += 2 ){
        while ( !(number % factor) ){
            number /= factor;
            ret += factor;
        }
    }
    if(number != 1) ret += number;
    return ret;
}

/**
Это лишь интересный концпет, на практике его применение вероятнее всего будет сужено, но всё же...
Идея в том, чтобы проверять число не на всю делимость, и даже не только по нечётным, а строго по простым, в добавок используя
трюки из модульной арифметики выходит крутой чикибабонёнок.
*/

#include "../../DortyLibs/prime/Adler_Sieve.h"
#include "../../DortyLibs/fast_calculations/fast_divisibility.h"
#include <cmath>
struct divisor : fast_divisibility<uint32_t>{
    uint32_t div;
    divisor(const uint32_t& n) : fast_divisibility<uint32_t>(n),div(n) {}
    divisor() = default;
};

#include "../../DortyLibs/prime/pi_upper_bound.h"
class PrimeFactorizer{
    divisor *primes;
    size_t h;
public:

    PrimeFactorizer(size_t size){
        size = sqrt(size);
        Sieve<uint64_t> S(size);
        primes = new divisor[pi_upper_bound(size)];
        h = 0;
        for(size_t i = 3; i <= size;++i){
            if (S.isPrime(i)){
                primes[h++] = i;
                ///cout << i << endl;
            }
        }
    }

    size_t prime_summ(size_t number){
        if (number < 2) return 0;
        size_t ret = 0;
        while ( number % 2 == 0 ){ret += 2; number /= 2;}



        for(size_t i = 0; i < h; ++i){
            while ( primes[i].check(number) ){ret += primes[i].div; number /= primes[i].div;}
        }

        if (number != 1) ret += number;
        return ret;
    }


};



using namespace std;
int main(void) {

    PrimeFactorizer PF(1000 * 1000 * 1000);

    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t> myl(a,ol,b,c);
    uint64_t ans = 0;


    for(int i = 0;i < n; ++i){
        ans += PF.prime_summ(myl.get());
    }
    cout << ans;


    // clean up

    return 0;
}
