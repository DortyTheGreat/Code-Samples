/// https://introcs.cs.princeton.edu/java/99crypto/PollardRho.java.html

/**

https://www.rsok.com/~jrm/9_digit_palindromic_primes.html

100030001
100050001
100060001
100111001
100131001
*/

/// https://codeforces.com/blog/entry/1729?locale=ru
template<typename T>
T mulmod(T a, T b, T MOD)
{
    if (b == 0) return 0;
    T res = mulmod(a, b >> 1, MOD);
    res += res;
    res %= MOD;
    return (b & 1)? (a + res) % MOD : res;
}

template<typename T>
T powmod(T a, T b, T MOD)
{
    if (b == 0) return 1;
    T res = powmod(a, b >> 1, MOD);
    res *= res;
    res %= MOD;
    return (b & 1)? (a * res) % MOD : res;
}



#include <iostream>

using namespace std;

unsigned int mod_pow(unsigned int a, unsigned int t, unsigned int mod) {
    unsigned long long r = 1;

    for (; t; t >>= 1, a = (unsigned long long)(a) * a % mod)
        if (t & 1)
            r = (unsigned long long)(r) * a % mod;

    return r;
}



template <typename T>
bool check_prime(T n) {
    /// Китаец сказал, что 2, 3, 5, 7, 11, 13, 17, 19 для ull
    /// 2, 3, 5 - наверное следует использовать для интов, но 2 и 3 заходит для https://vjudge.net/problem/SPOJ-PRIME1
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
            y = (unsigned long long)x * x % n;

            if (y == 1 && x != n - 1)
                return false;

            x = y;

        }

        if (x != 1)
            return false;
    }

    return true;
}


template<typename ll>
bool MillerRabin(ll n){
    if (n < 2 || (n != 2 && n%2 ==0)){return 0;}
    int s = 0;
    ll d = n - 1;
    while(!(d&1)){
        ++s;d>>=1;
    }

    int checks[] = {2,3,5,7,11,13,17,19,23,29,31,37,41};
    for(int i =i;i<13 && checks[i]<n-1;++i){
        ll x = powmod(checks[i],d,n);
        if (x == 1 || x == n - 1) continue;
        bool cmp = 1;
        for(int j = 1;j<s;++j){
            x = mulmod(x,x,n);
            if (x == 1) return 0;
            if (x == n - 1){
                cmp = 0;
                break;
            }
        }
        if(cmp) return 0;
    }
    return 1;
}






/// Чуть быстрее __gcd
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



long long rho(long long n) {
    long long divisor = 1;
    long long c  = rand() % n;
    long long x  = rand() % n;
    long long xx = x;

    // check divisibility by 2
    if (n % 2 == 0) return 2;

    do {
        x  =  (((__int128)(x) * x % n) + c) % n;

        xx  =  (((__int128)(xx) * xx % n) + c) % n;
        xx  =  (((__int128)(xx) * xx % n) + c) % n;
        divisor = gcd(abs(x-xx),n);
    } while(divisor == 1);

    return divisor;
}

#include <map>

void factor(long long n, map<long long,int>& ans) {

    if (n == 1) return;
    if (check_prime(n)) { ++ans[n]; return; } /// got here n as a factor
    long long divisor = rho(n);
    factor(divisor, ans);
    factor(n / divisor, ans);
}

int main()
{
    long long N;
    cin >> N;
    map<long long,int> ans;
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
