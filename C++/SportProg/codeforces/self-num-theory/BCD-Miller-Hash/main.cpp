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
        shift = 127;

        __uint128_t temp = (__uint128_t(1) << 127) / val;
        shift = __builtin_clzll(temp  >> 64); /// zeros
        my_magic = (temp >> (64-shift));
        --shift;

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
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

#include <iostream>
using namespace std;
// fastmod computes (n mod d) given precomputed c





uint16_t bases[]={15591,2018,166,7429,8064,16045,10503,4399,1949,1295,2776,3620,560,3128,5212,
2657,2300,2021,4652,1471,9336,4018,2398,20462,10277,8028,2213,6219,620,3763,4852,5012,3185,
1333,6227,5298,1074,2391,5113,7061,803,1269,3875,422,751,580,4729,10239,746,2951,556,2206,
3778,481,1522,3476,481,2487,3266,5633,488,3373,6441,3344,17,15105,1490,4154,2036,1882,1813,
467,3307,14042,6371,658,1005,903,737,1887,7447,1888,2848,1784,7559,3400,951,13969,4304,177,41,
19875,3110,13221,8726,571,7043,6943,1199,352,6435,165,1169,3315,978,233,3003,2562,2994,10587,
10030,2377,1902,5354,4447,1555,263,27027,2283,305,669,1912,601,6186,429,1930,14873,1784,1661,
524,3577,236,2360,6146,2850,55637,1753,4178,8466,222,2579,2743,2031,2226,2276,374,2132,813,
23788,1610,4422,5159,1725,3597,3366,14336,579,165,1375,10018,12616,9816,1371,536,1867,10864,
857,2206,5788,434,8085,17618,727,3639,1595,4944,2129,2029,8195,8344,6232,9183,8126,1870,3296,
7455,8947,25017,541,19115,368,566,5674,411,522,1027,8215,2050,6544,10049,614,774,2333,3007,
35201,4706,1152,1785,1028,1540,3743,493,4474,2521,26845,8354,864,18915,5465,2447,42,4511,
1660,166,1249,6259,2553,304,272,7286,73,6554,899,2816,5197,13330,7054,2818,3199,811,922,350,
7514,4452,3449,2663,4708,418,1621,1171,3471,88,11345,412,1559,194};

template<typename unsign>
FORCE_INLINE unsign sqr(const unsign& num){
    return num*num;
}

/// важно, чтобы тип unsign позволял вместить в себя произведение mod*mod. aka избавляйтесь от переполнения
template<typename unsign, typename power_type, typename modulus_obj>
FORCE_INLINE unsign modul_pow(unsign num, power_type power, const modulus_obj& mod){
    unsign cur = 1;
    for(;power;power >>= 1) {
        if (power & 1) cur = (cur*num) % mod;
        num = sqr(num) % mod;
    }
    return cur;
}

/// http://ceur-ws.org/Vol-1326/020-Forisek.pdf
bool is_SPRP(uint32_t n, const uint64_t& a) {

    fast_mod64 fm_n(n);
    uint_fast8_t s = __builtin_ctz(--n);
    uint64_t cur = modul_pow(a, n>>s, fm_n);
    if (cur == 1) return true;
    for (uint_fast8_t r=0; r<s; ++r) {
        if (cur == n) return true;
        cur = sqr(cur) % fm_n;
    }
    return false;
}

/// check factor
/// check factor
#define cf(t) if (!(x%t)){ return (x==t);}


#define _5c(a,b,c,d,e) cf(a) cf(b) cf(c) cf(d) cf(e)

constexpr uint8_t type_log_2(uint32_t) {return 5;}
constexpr uint8_t type_log_2(uint64_t) {return 6;}
constexpr uint8_t type_log_2(__uint128_t) {return 7;}

template<typename T>
T binary_inverse(const T& n){
    T inv = n;

    for (uint8_t i = 0; i < type_log_2(T(0)); i++)
        inv *= 2 - n * inv;
    return inv;
}


template <typename T>
class fast_divisibility{
public:
    T inverse;
    T limit;
public:
    fast_divisibility() = default;
    fast_divisibility(const T& mod){
        limit = ~T(0) / mod;
        inverse = binary_inverse(mod);
    }
    FORCE_INLINE constexpr bool check(const T& data) const{
        return (data*inverse) <= limit;
    }
};

fast_divisibility<uint32_t> f1(3), f2(5), f3(7), f4(11), f5(13), f6(17), f7(19), f8(23), f9(29), f10(31), f11(37), f12(41), f13(43), f14(47), f15(53), f16(59), f17(61), f18(67), f19(71);

bool is_prime_WTF(uint32_t x) {
    /*
    _5c(2,3,5,7,11)
    _5c(13,17,19,23,29)
    _5c(31,37,41,43,47)
    _5c(53,59,61,67,71)
    _5c(73,79,83,89,97)
    */
    if (!(x & 1)) return x == 2;
    if (f1.check(x)) return x == 3;
    if (f2.check(x)) return x == 5;
    if (f3.check(x)) return x == 7;
    if (f4.check(x)) return x == 11;
    if (f5.check(x)) return x == 13;
    if (f6.check(x)) return x == 17;
    if (f7.check(x)) return x == 19;
    if (f8.check(x)) return x == 23;
    if (f9.check(x)) return x == 29;
    if (f10.check(x)) return x == 31;
    if (f11.check(x)) return x == 37;
    if (f12.check(x)) return x == 41;
    if (f13.check(x)) return x == 43;
    if (f14.check(x)) return x == 47;
    if (f15.check(x)) return x == 53;
    if (f16.check(x)) return x == 59;
    if (f17.check(x)) return x == 61;
    if (f18.check(x)) return x == 67;
    if (f19.check(x)) return x == 71;
    if (x<121) return (x>1);
    uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    return is_SPRP(x,bases[h]);
}




/// возвращает большее, можно дать ссылку для меньшего


using namespace std;
int main(void) {

    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t, fast_mod64> myl(a,ol,b,c);
    uint64_t ans = 0;
    for(int i = 0;i< n;++i){
        ans += is_prime_WTF( myl.get());
    }
    cout << ans;


    return 0;
}
