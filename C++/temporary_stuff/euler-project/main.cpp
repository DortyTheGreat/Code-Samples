#include <iostream>
#include <map>
#include <cmath>
#include <vector>


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


// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

/// since (a == 0) === !a

#include <utility> /// pair


// Computes aR * bR mod N with R = 2**64.
template<typename T>
T mont_mul(T a, T b, T N, T Nneginv) {
    T Th, Tl, m, mNh, mNl;

    Tl = mult(a, b, Th);
    m = Tl * Nneginv;
    mNl = mult(m, N, mNh);


    /*
    T tl2, th2;
    uint32_t low_carry_in = 0;

    uint32_t carryL = _addcarry_u64(low_carry_in, Tl, mNl, &tl2);
    uint32_t carryH = _addcarry_u64(carryL, Th, mNh, &th2);

    if (carryH || (th2 >= N)) th2 = th2 - N;

    return th2;
    */

    bool lc = Tl + mNl < Tl;
    T th = Th + mNh + lc;
    bool hc = (th < Th) || (th == Th && lc);

    if (hc > 0 || th >= N) th = th - N;

    return th;
}


template <typename T>
inline std::pair<T, T> mont_modinv(T m) {
    const size_t shift = sizeof(m) * 8 - 1;
    T a = T(1) << shift;
    T u = 1;
    T v = 0;

    while (a) {
        a >>= 1;
        if (u & 1) {
            u = ((u ^ m) >> 1) + (u & m);
            v = (v >> 1) + (T(1) << shift);
        }
        else {
            u >>= 1; v >>=1;
        }
    }
    return std::make_pair(u, v);
}


// Returns a factor of n, assumes n is odd.



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
    static const int jp[] = { 2, 3, 5, 7, 11, 13, 17, 19};

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
        if (n % p == 0)
            return n == p;
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

#define cf(k) while (!(num % k)){++ret[k]; num /= k;}

std::map<unsigned long long,int> factor(__uint128_t num){
    std::map<unsigned long long,int> ret;
    unsigned long long* arr = new unsigned long long[sizeof(unsigned long long) - 1];
    unsigned int size = 0;

    cf(2) cf(3) cf(5) cf(7) cf(11)

    arr[0] = num;



    for(size_t i = 0;i < size + 1; ){
        if(arr[i] == 1){++i; continue;}
        if (isPrime(arr[i])) { ++ret[arr[i++]]; continue; } /// got here n as a factor
        arr[++size] = pollard_brent_montgomery( arr[i]);

        arr[i] /= arr[size];

    }

    delete[] arr;




    return ret;
}







using namespace std;

const uint64_t mod = 993353399;

map<uint64_t, uint64_t> phi_precalc;

uint64_t phi(uint64_t n) {

    if (phi_precalc.find(n) != phi_precalc.end()) return phi_precalc[n];

    uint64_t orig_n = n;
    uint64_t result = n;
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return phi_precalc[orig_n] = result;
}

bool IsSquare(uint64_t number){
    return (uint64_t)(sqrtl( number)) == sqrtl( number);
}

/// return all divisors
vector<uint64_t> all_divisers(uint64_t number){
    vector<uint64_t> ans;
    uint64_t sqrt_= sqrtl( number );
    for(uint64_t i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(uint64_t counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}

vector<uint64_t> all_divisers2(uint64_t number){
    auto mp = factor(number);
    vector<uint64_t> abobus = {1};

    for(auto pair_ : mp){
        //cout << pair_.first << " " << pair_.second << endl;
    }

    for(auto pair_ : mp){
        vector<uint64_t> new_vc;
        for(int i = 0; i < abobus.size();++i){
            uint64_t mult = 1;
            for(int j = 0; j < pair_.second + 1; ++j){
                //cout << abobus[i] * mult << endl;
                new_vc.push_back(abobus[i] * mult);
                mult *= pair_.first;
            }
        }
        abobus = new_vc;

    }

    return abobus;

}



uint64_t f(uint64_t n){

    auto vc = all_divisers2(n);
    uint64_t summ = 0;
    for(auto elem : vc){
        auto vc2 = all_divisers2(elem);

        uint64_t summ_inside = 0;

        for(auto elem2 : vc2){
            summ_inside += (elem2%mod) * (phi(n/elem2)%mod);
            summ_inside %= mod;
        }

        //cout << n/elem << endl;
        //cout << phi(n/elem) << endl;
        //cout << phi(n) << " " << phi(n/elem) << " " << phi(elem) << " " << elem << endl;

        summ_inside *= summ_inside;
        summ_inside %= mod;



        summ += summ_inside * (phi(n/elem)%mod);
        summ %= mod;
    }

    n %= mod;

    summ += n*n;
    summ %= mod;

    return summ;

}



int main()
{
    auto vc_all = all_divisers2(9);
    for(auto elem : vc_all){
        cout << elem << " ";
    }
    cout << endl;

    uint64_t num_10_16 = 10000000000000000;
    uint64_t num_10_6 = 1000000;

    uint64_t BIG_BOY = 0;

    for(uint64_t i = num_10_16; i <= num_10_16 + num_10_6; ++i){
        if (isPrime(i)){
            cout << i << endl;
            BIG_BOY += f(i-1);
            BIG_BOY %= mod;
        }
        ///cout << i << endl;
    }
    cout << BIG_BOY;

    ///cout << "Hello world!" << endl;
    return 0;
}
