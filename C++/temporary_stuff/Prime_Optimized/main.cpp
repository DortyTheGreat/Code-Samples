/// https://github.com/armchaircaver/Factors/blob/c475fd6d4116ed9da6b34f20be35f712cf92235a/Pollard%20Rho%20trials/Pollard%20Rho%20Montgomery.cpp

ck made the implementation 4 times faster.
*/

/**
¬Ќ»ћјЌ»≈! ƒјЌЌјя ќѕ“»ћ»«ј÷»я ћќ∆≈“ –јЅќ“ј“№ Ќ≈¬≈–Ќќ, ƒелалось из-за подозрений в особенных тестах в
https://vjudge.net/status/#un=&OJId=SPOJ&probNum=FACT1&res=0&orderBy=run_id&language=
*/

#include <cstdint>
#include <iostream>
#include <tuple>


using u128 = __uint128_t;



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
template<typename T>
T montmul(T a, T b, T N, T Nneginv) {
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

/// „уть быстрее __gcd
template<typename T>
T gcd(T a, T b)
{
    T c;
    while (b)
    {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}



// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

/// since (a == 0) === !a

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
    T m = 100;

    // nneginv is m' (mprime) in Warren
    T nneginv = mont_modinv(n).second;


    T factor = 1, r, q, x, ys;
    q = r = 1;

    while(factor == 1){
        x = y;
        for (size_t i = 0; i < r; ++i) {
            y = addmod(montmul(y, y, n, nneginv), c, n);
        }

        for (size_t k = 0; k < r && factor == 1; k += m) {
            ys = y;
            for (size_t i = 0; i < std::min(m, r - k); ++i) {
                y = addmod(montmul(y, y, n, nneginv), c, n);
                q = montmul(q, x < y ? y - x : x - y, n, nneginv);
            }

            factor = gcd(q, n);
        }

        r *= 2;
    }

    if (factor == n) {
        do {
            ys = addmod(montmul(ys, ys, n, nneginv), c, n);
            factor = gcd(x < ys ? ys - x : x - ys, n);
        } while (factor == 1);
    }

    return factor;
}

int tries = 0;
uint64_t pollard_brent_montgomery_retry(uint64_t n) {
    uint64_t f=0;
    tries = 0;
    do {
        f = pollard_brent_montgomery(n);
        tries++;
     } while (f == n);
    return f;
}

int getTries() {
    return tries;
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

    for (; t; t >>= 1, a = (__uint128_t)(a) * a % mod)
        if (t & 1)
            r = (__uint128_t)(r) * a % mod;

    return r;
}



template <typename T>
bool check_prime(T n) {
    ///  итаец сказал, что 2, 3, 5, 7, 11, 13, 17, 19 дл€ ull
    /// 2, 3, 5 - наверное следует использовать дл€ интов, но 2 и 3 заходит дл€ https://vjudge.net/problem/SPOJ-PRIME1
    static const int jp[] = { 2,3, 5};

    if (n == 1)
        return false;


    if (n % 2 == 0)
        return n == 2;

    if (n % 3 == 0)
        return n == 3;

    if (n % 5 == 0)
        return n == 5;


    T r = n - 1, x, y;
    int e = 0;

    while (~r & 1)
        r >>= 1, ++e;

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

void factor(__uint128_t n, map<__uint128_t,int>& ans) {

    if (n == 1) return;
    if (check_prime(n)) { ++ans[n]; return; } /// got here n as a factor
    __uint128_t divisor = pollard_brent_montgomery(n);
    factor(divisor, ans);
    factor(n / divisor, ans);
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


#include <algorithm>
///  const __uint128_t& ui128, но у мен€ всЄ деструктивно
std::ostream& operator <<(std::ostream& os, __uint128_t ui128) {

    string buff;
    while(ui128){
        buff += (ui128%10+'0');
        ui128 /= 10;
    }



    reverse(buff.begin(),buff.end());

	return (os << buff);
}

int main()
{
    __uint128_t N;
    cin >> N;
    map<__uint128_t,int> ans;
    while(N){
        ans.clear();


        factor(N,ans);

        for(auto p : ans){
            cout << p.first << "^" << p.second << " ";
        }
        cout << '\n';
        cin >> N;
    }

    return 0;
}
