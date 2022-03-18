#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

const int size_ = 200000;

vector<vector<pair<int, int>>> g;

int first_[size_], second_[size_];


vector<int> Dinf, Dins;

const int pseudo_inf = 1e9;

void calculate(int n,int m) {

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++)
            if (first_[i - 1] == second_[j - 1]) {
                g[i][j] = { g[i - 1][j - 1].first + 1,
                    j == 1? i : max(g[i - 1][j].second, g[i][j - 1].second) };
                if ((j == m) && (g[i][j].first == m)) {

                    Dins.push_back(i);
                    Dinf.push_back(g[i][j].second);

                }
            }
            else {

                if (j == m){
                    g[i][j] = g[i][j - 1];
                }else{
                    if (g[i][j - 1] == g[i - 1][j]){
                        g[i][j] = { g[i][j - 1].first,
                        max(g[i][j - 1].second, g[i - 1][j].second) };
                    }else{

                        g[i][j] = (g[i][j - 1].first > g[i - 1][j].first ? g[i][j - 1] : g[i - 1][j]);

                    }
                }
            }
    }

}

signed main() {

    int n,m;

    cin >> n >> m;

    for(int i =0;i<n;i++){
        cin >> first_[i];
    }

    for(int i =0;i<m;i++){
        cin >> second_[i];
    }

    g.resize(n + 1, vector<pair<int, int> >(m + 1));

    calculate(n,m);


    Dins.push_back(-1);
    Dinf.push_back(pseudo_inf);


    for (int i = 0; i < n; i++)
        cout << Dins[upper_bound(Dinf.begin(), Dinf.end(), i) - Dinf.begin()] << " "; /// Как вывести уппер боунд, что это?
}
