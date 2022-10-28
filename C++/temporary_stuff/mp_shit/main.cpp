#include <iostream>
#include <unordered_map>
#include <vector>


int mod = (int)(1e9) + 7;
using namespace std;

struct pairhash {
    size_t operator()(const pair<int, int> &p) const {
        return hash<int>()((p.first << 11) + p.second);
    }
};

signed main()
{
    int arr[104][104];
    int dp[104][104];

    int n,m;
    cin >> n >> m;



    vector< pair<int,int > > vc;
    for(int i = 0;i < n; ++i){
        for(int j = 0;j < m; ++j){
            cin >> arr[i][j];
            dp[i][j] = 0;
            if (arr[i][j] == 1){
                vc.push_back({i,j});
                dp[i][j] = 1;
            }
        }
    }


    int itter = 1;
    int ans = 0;
    while(!vc.empty()){

        itter++;
        vector< pair<int,int > > new_vc;
        for(auto elem : vc){

            bool flag = 1;
            int n_i = elem.first + 1;
            int n_j = elem.second;
            if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m ){
                if (arr[n_i][n_j] == itter){
                    flag = 0;

                    dp[n_i][n_j] += dp[elem.first][elem.second];
                    dp[n_i][n_j] %= mod;

                }
            }


            n_i = elem.first - 1;
            n_j = elem.second;
            if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m ){
                if (arr[n_i][n_j] == itter){
                    flag = 0;

                    dp[n_i][n_j] += dp[elem.first][elem.second];
                    dp[n_i][n_j] %= mod;
                }
            }


            n_i = elem.first;
            n_j = elem.second - 1;
            if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m ){
                if (arr[n_i][n_j] == itter){
                    flag = 0;

                    dp[n_i][n_j] += dp[elem.first][elem.second];
                    dp[n_i][n_j] %= mod;
                }
            }


            n_i = elem.first;
            n_j = elem.second + 1;
            if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m ){
                if (arr[n_i][n_j] == itter){
                    flag = 0;

                    dp[n_i][n_j] += dp[elem.first][elem.second];
                    dp[n_i][n_j] %= mod;
                }
            }
            /// Что-то пошло не так, элемента не нашлось, добавить или ничего не делать
            if (flag){
                if (itter >= 4){
                    ans += dp[elem.first][elem.second];
                    ans %= mod;
                }
            }


        }
        vc = new_vc;
    }


    cout << ans << endl;



    return 0;
}
