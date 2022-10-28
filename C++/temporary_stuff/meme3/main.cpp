#include <iostream>
#pragma GCC optimize("O3")
#pragma GCC target("avx2,tune=native")
using namespace std;
#define int long long
int mod = (int)(1e9) + 7;

const int sz = 504;

const int secret_number = -1337;

int arr[sz][sz];
int dp[sz][sz];

int calls = 0;

int f(int x,int y, int depth){
    if (dp[x][y] != secret_number) return dp[x][y];

    int summ = 0;
    bool flag = 1;
    if (arr[x+1][y] + 1 == arr[x][y]){ flag = 0; summ += f(x+1,y, depth+1);}
    if (arr[x-1][y] + 1 == arr[x][y]){ flag = 0; summ += f(x-1,y, depth+1);}
    if (arr[x][y+1] + 1 == arr[x][y]){ flag = 0; summ += f(x,y+1, depth+1);}
    if (arr[x][y-1] + 1 == arr[x][y]){ flag = 0; summ += f(x,y-1, depth+1);}
    if (flag){
        summ = 1;
        if (depth < 4) return 0;
    }


    return dp[x][y] = summ % mod;
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    for(int i = 0;i < sz; ++i){
        for(int j = 0;j < sz; ++j){
            arr[i][j] = -1e9;
            dp[i][j] = 0;
        }
    }
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n; ++i){
        for(int j = 1;j <= m; ++j){
            cin >> arr[i][j];
            dp[i][j] = secret_number;

        }
    }
    int ans = 0;
    for(int i = 1;i <= n; ++i){
        for(int j = 1;j <= m; ++j){

            if ( arr[i][j] >= arr[i+1][j] && arr[i][j] >= arr[i-1][j] && arr[i][j] >= arr[i][j-1] && arr[i][j] >= arr[i][j+1] ){
                ans += f(i,j,1);
            }

        }
    }

    cout << ans % mod<< endl;
    return 0;
}
