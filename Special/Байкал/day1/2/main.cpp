#include <iostream>
#include <algorithm>
using namespace std;

// Function for extended Euclidean Algorithm
int64_t Find_gcd_Extended(int64_t a, int64_t b, int64_t* x, int64_t* y);

// Function to find modulo inverse of a
int64_t Find_mod_Inverse(int64_t a, int64_t m)
{
    int64_t x, y;
    int64_t g = Find_gcd_Extended(a, m, &x, &y);

    /*
      If the gcd value doesn't matches
      to 1, then inverse doesn't exist
    */

      return (x % m + m) % m;

}

// Function to find extended Euclidean Algorithm
int64_t Find_gcd_Extended(int64_t a, int64_t b, int64_t* x, int64_t* y)
{

    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }


    int64_t x1, y1;
    int64_t gcd = Find_gcd_Extended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}



int main()
{
    int64_t a,n,m;
    cin >> a >> n >> m;
    if (__gcd(a,m) != 1){
        cout << -1;
        return 0;
    }
    int64_t rev = Find_mod_Inverse(a,m);
    int64_t ans = 0;

    int64_t rev_c = rev;

    for(int64_t i = 1;i <= n;++i){
        ans += i*rev_c;
        ans %= m;

        rev_c *= rev;
        rev_c %= m;
    }
    cout << ans;
    return 0;
}
