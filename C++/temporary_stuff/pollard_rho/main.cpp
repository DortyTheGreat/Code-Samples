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




// Computes (a + b) % m, assumes a < m and b < m.
template<typename T>
T addmod(T a, T b, T m) {
    if (b >= m - a) return a - m + b;
    return a + b;
}

template<typename T>
static T mult(T x, T y,T& HighProduct) {
    const size_t shift = sizeof(x) * 4;
    T a = x >> shift, b = (x << shift) >> shift;
    T c = y >> shift, d = (y << shift) >> shift;
    // (a*2^64 + b) * (c*2^64 + d) =
    // (a*c) * 2^128 + (a*d + b*c)*2^64 + (b*d)
    T ac = a * c;
    T ad = a * d;
    T bc = b * c;
    T bd = b * d;
    T carry = ((ad << shift) >> shift) + ((bc << shift) >> shift) + (bd >> shift);
    HighProduct = ac + (ad >> shift) + (bc >> shift) + (carry >> shift);
    return (ad << shift) + (bc << shift) + bd;
}

// Computes aR * bR mod N with R = 2**64.


uint64_t montmul(__uint128_t a, uint64_t b, __uint128_t mod, uint64_t inv){
    a *= b;
    uint64_t y = (a >> 64) - (__uint128_t(uint64_t(a) * inv) * mod >> 64);
    return int64_t(y) < 0 ? y + mod : y;

}

/// Чуть быстрее __gcd, для int
template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
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
    uint64_t m = 100;

    // nneginv is m' (mprime) in Warren

    uint64_t inv = n;
    for(int i = 0;i < 5; ++i) inv *= 2 - n * inv;




    uint64_t factor = 1, r, q, x, ys;
    q = r = 1;

    while(factor == 1){
        x = y;
        for (size_t i = 0; i < r; ++i) {
            y = addmod(montmul(y, y, n, inv), c, n);
        }

        for (size_t k = 0; k < r && factor == 1; k += m) {
            ys = y;
            for (size_t i = 0; i < std::min(m, r - k); ++i) {
                y = addmod(montmul(y, y, n, inv), c, n);
                q = montmul(q, x < y ? y - x : x - y, n, inv);
            }

            factor = gcd(q, n);
        }

        r *= 2;
    }

    if (factor == n) {
        do {
            ys = addmod(montmul(ys, ys, n, inv), c, n);
            factor = gcd(x < ys ? ys - x : x - ys, n);
        } while (factor == 1);
    }
    if (factor == 1 || factor == n){
        return pollard_brent_montgomery(n);
    }

    return factor;
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


#include <map>

using namespace std;

__uint128_t mod_pow(__uint128_t a, __uint128_t t, __uint128_t mod) {
    __uint128_t r = 1;

    for (; t; t >>= 1, a = (a) * a % mod)
        if (t & 1)
            r = (r) * a % mod;

    return r;
}




bool isPrime(unsigned long long n) {
    /// Китаец сказал, что 2, 3, 5, 7, 11, 13, 17, 19 для ull
    /// 2, 3, 5 - наверное следует использовать для интов, но 2 и 3 заходит для https://vjudge.net/problem/SPOJ-PRIME1
    static const int jp[] = { 2,3, 5,7,11,13,17};

    if (n == 1)
        return false;

    /*
    if (n % 2 == 0)
        return n == 2;

    if (n % 3 == 0)
        return n == 3;

    if (n % 5 == 0)
        return n == 5;
    */


    unsigned long long r = n - 1, x, y;

    unsigned char e = __builtin_ctz(r);
    r >>= e;

    for (int p : jp) {
        x = mod_pow(p, r, n);

        for (int t = 0; t < e && x > 1; ++t) {
            y = (__uint128_t)x * x % n;

            if (y == 1 && x != n - 1)
                return false;

            x = y;

        }

        if (x != 1)
            return false;
    }

    return true;
}

#include <algorithm>
///  const __uint128_t& ui128, но у меня всё деструктивно
std::ostream& operator <<(std::ostream& os, __uint128_t ui128) {

    string buff;
    while(ui128){
        buff += (ui128%10+'0');
        ui128 /= 10;
    }



    reverse(buff.begin(),buff.end());

	return (os << buff);
}

#define cf(k) while (!(num % k)){arr[size++] = k; num /= k;}

std::vector<uint64_t> factor(__uint128_t num){

    vector<uint64_t> arr(sizeof(uint64_t) * 8 - 1);
    unsigned int size = 0;

    cf(2) cf(3) cf(5) cf(7) cf(11)

    arr[size] = num;



    for(size_t i = size;i < size + 1; ){
        ///cout << arr[i] << endl;
        if(arr[i] == 1){++i; continue;}
        if (isPrime(arr[i])) { ++i; continue; } /// got here n as a factor
        arr[++size] = pollard_brent_montgomery( arr[i]);

        arr[i] /= arr[size];

    }

    arr.resize(size);
    sort(arr.begin(),arr.end());




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

template <typename T>
std::ostream& operator<<(std::ostream &in, const std::vector<T> &vect) {
    int n = vect.size();
    for(int i =0;i<n;i++){
        in << vect[i] << " " ;
    }
    return in;
}

int main()
{
    int n;
    cin >> n;

    for(int i = 0;i< n;++i){
        uint64_t t;
        cin >> t;
        cout << factor(t);

    }
    return 0;


    return 0;
}
