#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int matr[105][105];

    int mod = 1000 * 1000 * 1000 + 7;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> matr[i][j];
        }
    }

    vector<int> dv = {0,0,-1,1};
    vector<int> du = {1,-1,0,0};

    map<int,int> mp;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if ( !(i == 0 || j == 0 || j == (n-1) || i == (n-1) )) {
                continue;
            }

            bool flag = 0;
            for(int dir = 0; dir < 4; ++ dir){
                int n_u = i + du[dir];
                int n_v = j + dv[dir];
                if (n_u >= 0 && n_u < n && n_v >= 0 && n_v < n  ){
                    if ( !(n_u == 0 || n_v == 0 || n_u == (n-1) || n_v == (n-1) )) continue;
                    if (matr[n_u][n_v] > matr[i][j]) flag = 1;
                }
            }
            if (flag) continue;

            cout << i << " " << j << endl;

            map<pair<int,int>, int > visited; /// типо ДП
            visited[{i,j}] = 1;
            int itteration = 1;





            for(itteration = 1; visited.size(); ++itteration){
                map<pair<int,int>, int > new_visited;
                int summ = 0;
                for(const auto& [p,ways]  : visited){


                    for(int dir = 0; dir < 4; ++ dir){
                        int n_u = p.first + du[dir];
                        int n_v = p.second + dv[dir];

                        if (n_u >= 0 && n_u < n && n_v >= 0 && n_v < n  ){
                            if (matr[n_u][n_v] < matr[p.first][p.second]){
                                new_visited[{n_u,n_v}] += ways;
                                new_visited[{n_u,n_v}] %= mod;
                                summ += ways;
                                summ %= mod;
                            }
                        }
                    }


                }

                mp[itteration] += summ;
                mp[itteration] %= mod;
                visited = new_visited;

            }

        }
    }


    int last_u, last_v;
    for(auto [u,v] : mp){
        if (v != 0){
            last_u = u;
            last_v = v;
        }

        cout << u << " " << v << endl;
    }


    cout << last_u+1 << " " << last_v;


    return 0;
}
