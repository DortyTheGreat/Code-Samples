/**
Линейно-конгруэнтный метод позволяет создавать псевдо-случайные числа.
Как именно генератор таких чисел, наверное, это не самый лучший метод(так и есть, лол),
однако данная задача способна легко продемонстрировать, как операцию взятие по модулю(%) можно ускорить в разы.
В отличии от банальных ~700 ms на задаче A из https://codeforces.com/contestInvitation/709dc3e3f466e68e1f8e50c71d59427062932a3d
Вот этим вот ускорителем деления можно получить скорость работы ~250 ms. Почти в 3 раза.
Dorty - 03.12.2022
*/

#include <iostream>
using namespace std;

#define FORCE_INLINE __attribute__((always_inline)) inline


uint64_t ret, low;
/// Возвращает большую часть от 128: 64x64
FORCE_INLINE uint64_t hmul64(const uint64_t& a,const uint64_t& b){
    asm ("mulq %3" : "=a"(low), "=d"(ret) : "a"(a), "g"(b) : "cc");
    return ret;
}

class fast_div64{
protected:
    uint64_t my_magic = 1;
    uint_fast8_t shift;

public:
    fast_div64(){}
    fast_div64(const uint64_t& val){
        shift = (127);

        __uint128_t temp = (__uint128_t(1) << 127) / val;
        shift = __builtin_clzll(temp  >> 64); /// zeros
        my_magic = (temp >> (64-shift));
        --shift;

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
        ///cout << my_magic << " " << (int)shift << endl;
    }


    FORCE_INLINE friend uint64_t operator/(const uint64_t& val, const fast_div64& fd){



        return (hmul64(val,fd.my_magic) >> fd.shift ) ;
    }
};


class fast_mod64 : fast_div64{
private:
    uint64_t div;
public:
    fast_mod64(){}
    fast_mod64(uint64_t val) : fast_div64(val), div(val){}
    FORCE_INLINE friend uint64_t operator%(const uint64_t& val, const fast_mod64& fm){
        return val - val/fm * fm.div;
    }
};


template<typename T, typename quick_mod = T>
class LCM{
public:
    T mult, old_rand, add;
    quick_mod fm;
    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add), fm(_mod){}
    FORCE_INLINE T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};



#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

template<typename T>
inline T gcd(T a, T b)
{
    if (b == 0) return a;
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

#define FORCE_INLINE __attribute__((always_inline)) inline

FORCE_INLINE auto ctz(const uint64_t& num){
    return __builtin_ctzll(num);
}

FORCE_INLINE auto ctz(const uint32_t& num){
    return __builtin_ctz(num);
}

/**
 * \brief Greatest common divisor.
 * \ingroup num
 *
 * `std::gcd` is available since C++17, but the GCC implementaiton uses the slow Euclidean algorithm until version 11.
 * This implementation uses binary GCD which is generally several times faster.
 *
 * Note that, unlike `std::gcd`, this function only accepts unsigned integers.
 */
template<typename T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr>
constexpr T binary_gcd(T x, T y) {
    if (x == 0) {
        return y;
    } else if (y == 0) {
        return x;
    }
    int kx = ctz(x);
    int ky = ctz(y);
    x >>= kx;
    while (y != 0) {
        y >>= ctz(y);
        if (x > y) {
            std::swap(x, y);
        }
        y -= x;
    }
    return x << std::min(kx, ky);
}

int main() {

    ///int a,ol, b,c, n;
    ///LCM<uint64_t, fast_mod64> my10k(2,0,1,13);

    LCM<uint64_t, fast_mod64> my100(127,109,113,131);

    LCM<uint64_t, fast_mod64> my10k(10711,10303,10501,11909);
    LCM<uint64_t, fast_mod64> my100k(101483,101027,101267,102107);
    LCM<uint64_t, fast_mod64> my1b(1000002431,1000000579,1000001677,1000003787);

    uint64_t ans = 0;
    auto begin = std::chrono::high_resolution_clock::now();

    begin = std::chrono::high_resolution_clock::now();
    int times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  __gcd(my100.get(),my100.get());
    }
    auto end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100 rnd __gcd: "<< ans <<endl;

    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  __gcd(my10k.get(),my10k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 10k rnd __gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  __gcd(my100k.get(),my100k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100k rnd __gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  __gcd(my1b.get(),my1b.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 1b rnd __gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  gcd(my100.get(),my100.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100 rnd inline_gcd: "<< ans <<endl;

    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  gcd(my10k.get(),my10k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 10k rnd inline_gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  gcd(my100k.get(),my100k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100k rnd inline_gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  gcd(my1b.get(),my1b.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 1b rnd inline_gcd: "<< ans <<endl;





    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  gcd(my100.get(),my100.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100 rnd binary_gcd: "<< ans <<endl;

    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  binary_gcd(my10k.get(),my10k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 10k rnd binary_gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  binary_gcd(my100k.get(),my100k.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 100k rnd binary_gcd: "<< ans <<endl;


    begin = std::chrono::high_resolution_clock::now();
    times = 10 * 1000 * 1000;
    for(int i = 0;i< times;++i){
        ans +=  binary_gcd(my1b.get(),my1b.get());
    }
    end = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000 << " - 10m times 1b rnd binary_gcd: "<< ans <<endl;



    cout << ans;


    return 0;
}
