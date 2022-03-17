#pragma GCC optimize("Ofast")

#include <iostream>
#include <algorithm>
#include <cstring>



using namespace std;

const int maxn = 501;
const int mod = 1000000007;
int dp[maxn][maxn][2];
/// n -> [k][x][> || <]

int summ[maxn][maxn][2];


void inline mod_check(int& a){
    if (a < 0){
        a += mod;
    }
    if (a >= mod){
        a -= mod;
    }
}

void inline mod_plus(int& a, int add){
    a += add;
    if (a >= mod){
        a -= mod;
    }
}

void inline mod_minus(int& a, int minus_){
    a -= minus_;
    if (a < 0){
        a += mod;
    }
}



signed main() {
    int n, x, k;
    cin >> n >> x >> k;

    for (int i = 0; i < x; ++i) {
        dp[0][i][0] = 1;
    }


    summ[0][0][0] = 0;
    for (int i = 1; i <= x; ++i) {
        summ[0][i][0] = summ[0][i-1][0] + dp[0][i-1][0];
        if (summ[0][i][0] >= mod){
            summ[0][i][0] -= mod;
        }
    }

    for (int i = 1; i < n; ++i) {
        int ndp[maxn][maxn][2];
        memset(ndp, 0, sizeof ndp);

        for (int j = 0; j <= k; ++j) {
            for (int c = 0; c < x; ++c) {

                ndp[j][c][1] = summ[j][c][1];
                ndp[j][c][1] += summ[j][c][0];

                if (ndp[j][c][1] >= mod){
                    ndp[j][c][1] -= mod;
                }


                ndp[j + 1][c][0] = summ[j][x][1] - summ[j][c + 1][1];

                if (ndp[j + 1][c][0] < 0){
                    ndp[j + 1][c][0] += mod;
                }

                mod_plus(ndp[j][c][0], summ[j][c + 1][1]);
                mod_minus(ndp[j][c][0],summ[j][c][1]);

                mod_minus(ndp[j][c][0], summ[j][c][0]);

                mod_plus(ndp[j][c][0],summ[j][x][0]);
            }
        }

        memcpy(dp, ndp, sizeof ndp);

        for (int j = 0; j <= k; ++j) {
            for (int c = 0; c < x; ++c) {
                summ[j][c + 1][0] = (summ[j][c][0] + dp[j][c][0]);
                if (summ[j][c + 1][0] >= mod){
                    summ[j][c + 1][0] -= mod;
                }
                summ[j][c + 1][1] = (summ[j][c][1] + dp[j][c][1]);

                if (summ[j][c + 1][1] >= mod){
                    summ[j][c + 1][1] -= mod;
                }

            }
        }
    }





    int ans = summ[k][x][0];
    mod_plus(ans,summ[k][x][1]);

    cout << ans;
}
