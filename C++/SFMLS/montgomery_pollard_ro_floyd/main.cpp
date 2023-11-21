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
#include <vector>

using namespace std;

#define FORCE_INLINE __attribute__((always_inline)) inline

uint64_t ret, low;
/// Возвращает большую часть от 128: 64x64
FORCE_INLINE uint64_t hmul64(const uint64_t& a,const uint64_t& b){
    asm ("mulq %3" : "=a"(low), "=d"(ret) : "a"(a), "g"(b) : "cc");
    return ret;
}

FORCE_INLINE auto ctz(const uint64_t& num){
    return __builtin_ctzll(num);
}

FORCE_INLINE auto ctz(const uint32_t& num){
    return __builtin_ctz(num);
}

template<typename unsign>
FORCE_INLINE unsign sqr(const unsign& num){
    return num*num;
}

/// Computes (a + b) % m, assumes a < m and b < m.
template<typename T>
FORCE_INLINE T addmod(const T& a,const T& b,const T& m) {
    if (b >= m - a) return a - m + b;
    return a + b;
}

/// Computes (a - b) % m, assumes a < m and b < m.
template<typename T>
FORCE_INLINE T submod(const T& a,const T& b,const T& m) {
    if (b > a) return m - b + a;
    return a - b;
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


template<typename T, typename quick_mod>
class LCM{
public:
    T mult, old_rand, add;
    quick_mod fm;
    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add), fm(_mod){}
    FORCE_INLINE T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};






// Computes aR * bR mod N with R = 2**64.


FORCE_INLINE uint64_t montmul(const uint64_t& a,const uint64_t& b,const uint64_t& mod,const uint64_t& inv){
    //a *= b;
    uint64_t high = hmul64(a,b);

    return submod(high, hmul64((low * inv), mod), mod);
}




template<typename T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr>
constexpr T gcd_any_odd(T x, T y) {
    if (x == 0) {
        return y;
    }

    x >>= ctz(x);
    while (y != 0) {
        y >>= ctz(y);
        if (x > y) {
            std::swap(x, y);
        }
        y -= x;
    }
    return x;
}


// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

/// since (a == 0) === !a




// Returns a factor of n, assumes n is odd.

uint64_t pollard_brent_montgomery(uint64_t n) {
    /*
    if (!(n & 1))
        return 2;
    */


    // Random number Linear Congruential Generator MMIX from D.E. Knuth
    static uint64_t rng = 0xdeafbeef;
    uint64_t a = rng * 6364136223846793005ull + 1442695040888963407ull;
    uint64_t b = a * 6364136223846793005ull + 1442695040888963407ull;
    rng = (a + b) ^ (a * b);

    // y and c are "montgomery space" numbers
    uint64_t y = 1 + a % (n - 1);
    uint64_t c = 1 + b % (n - 1);


    // nneginv is m' (mprime) in Warren

    uint64_t inv = n;
    for(int i = 0;i < 5; ++i) inv *= 2 - n * inv;




    uint64_t factor = 1, x = y;

    uint64_t q = 1;

    while(factor == 1){

        for(int i = 0; i < 10; ++i){
            x = addmod(montmul(x, x, n, inv), c, n);

            y = addmod(montmul(y, y, n, inv), c, n);
            y = addmod(montmul(y, y, n, inv), c, n);

            q = montmul(q, x < y ? y - x : x - y, n, inv);
        }
        factor = gcd_any_odd(q, n);
    }

    if (factor == n) {
        return pollard_brent_montgomery(n);
    }

    return factor;
}





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
    uint_fast8_t s = ctz(--n);
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

bool is_prime_WTF(uint32_t x) {

    if (x<121) return (x>1);
    uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    return is_SPRP(x,bases[h]);
}



#define cf3(k) while (!(num % k)){arr[size++] = k; num /= k;}

std::vector<uint64_t> factor(uint64_t num){
    ///cout <<"F: " << num << endl;
    vector<uint64_t> arr(30);
    unsigned int size = 0;

    cf3(2) cf3(3) cf3(5) cf3(7) cf3(11)
    cf3(13) cf3(17) cf3(19) cf3(23) cf3(29)
    cf3(31) cf3(37) cf3(41) cf3(43) cf3(47)
    cf3(53) cf3(59) cf3(61) cf3(67) cf3(71)
    if (num == 1) goto last;
    if (num < 5329){
        arr[size++] = num;
        goto last;
    }
    arr[size] = num;



    for(size_t i = size;i < size + 1; ){
        ///cout << arr[i] << endl;
        ///cout << isPrime(arr[i]) << endl;
        ///if(arr[i] == 1){++i; continue;}
        if (is_prime_WTF(arr[i])) { ++i; continue; } /// got here n as a factor
        arr[++size] = pollard_brent_montgomery( arr[i]);

        arr[i] /= arr[size];

    }
    ++size;
    last:
        arr.resize(size);
        //sort(arr.begin(),arr.end());
        return arr;
}



std::istream& operator>>(std::istream& in, __uint128_t &ui128) {


    std::string stream_;
    in >> stream_;

    ui128 = 0;
    for(char c : stream_){
        ui128 *= 10;
        ui128 += c-'0';
    }

    return in;

}




template <typename T>
std::ostream& operator<<(std::ostream &in, const std::vector<T> &vect) {
    int n = vect.size();
    for(int i =0;i<n;i++){
        in << vect[i] << " " ;
    }
    return in;
}

template <typename T>
uint64_t summ(const std::vector<T> &vect) {
    int n = vect.size();
    uint64_t s = 0;
    for(int i =0;i<n;i++){
        s += vect[i];
    }
    return s;
}

int main()
{


    ios::sync_with_stdio(0); cin.tie(0);
    int a,ol, b,c, n;
    cin >> a >> ol >> b >> c >> n;
    LCM<uint64_t, fast_mod64> myl(a,ol,b,c);
    uint64_t ans = 0;

    for(int i = 0;i< n;++i){

        ans += summ(factor(myl.get()));
    }
    cout << ans;


    return 0;
}
