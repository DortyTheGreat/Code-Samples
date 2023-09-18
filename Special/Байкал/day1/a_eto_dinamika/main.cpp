#include <iostream>
#define int long long


using namespace std;

int dinamo[103][1504];
int mod = 1000000000 + 7;


int f(int n_, int k_){
    ///if (k_ < n_) return 0;
    if (k_ < 0) return 0;
    if (n_*16 <= k_) return 0;

    //if (n_ == k_) return 1;

    if (n_ == 1) return 1;

    if (dinamo[n_][k_] != -1337) return dinamo[n_][k_];

    int ans = 0;
    for(int i = 0; i <= 15; ++i ){
        ans += f(n_ - 1, k_ - i);
    }
    ans %= mod;
    return dinamo[n_][k_] = ans;
}

signed main()
{
    int n,k; /// k - summ, n - cifri

    cin >> n >> k;

    for(int i = 0; i < 103; ++i){
        for(int j = 0; j < 1504; ++j){
            dinamo[i][j] = -1337;
        }
    }

    int ans = 0;
    for(int i = 1; i <= 15; ++i ){
        ans += f(n - 1, k - i);
    }
    ans %= mod;
    cout << ans;
    return 0;
}
