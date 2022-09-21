/// https://introcs.cs.princeton.edu/java/99crypto/PollardRho.java.html

/**

https://www.rsok.com/~jrm/9_digit_palindromic_primes.html

100030001
100050001
100060001
100111001
100131001
*/




#include <iostream>

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

template<typename T>
T abs(T value){
    if (value < 0){return -value;}
    return value;
}

__uint128_t rho(__int128 n) {
    __uint128_t divisor = 1;
    __uint128_t c  = rand() % n;

    __int128 x  = rand() % n;
    __int128 xx = x;

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

void factor(__uint128_t n, map<__uint128_t,int>& ans) {

    if (n == 1) return;
    if (check_prime(n)) { ++ans[n]; return; } /// got here n as a factor
    __uint128_t divisor = rho(n);
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
