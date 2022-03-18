#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
/// ПОЧЕМУ ???? ?!?? !??!
using namespace std;

int n, m;
vector<vector<int> > g;
vector<int> used, tin, up;

vector<pair<int, int> > bridges;

int k = 0;

void dfs(int v, int p = -1) {
    k++;
    up[v] = k;
    tin[v] = k;

    used[v] = 1;

    for (int to : g[v]) {
        if (to != p) {
            if (used[to])
                up[v] = min(up[v], tin[to]);
            else {
                dfs(to, v);
                up[v] = min(up[v], up[to]);
                if (tin[v] < up[to]) {
                    if (v < to)
                        bridges.push_back(make_pair(v, to));
                    else
                        bridges.push_back(make_pair(to, v));
                }
            }
        }
    }
}

int main() {
#ifdef gosunov_local
    freopen("input.txt", "r", stdin);
#endif
    cin >> n;

    g.resize(n);
    tin.resize(n);
    up.resize(n);
    used.resize(n);

    int from, to;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            cin >> a;
            if (a)
                g[i].push_back(j);
        }
    }
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);

    sort(bridges.begin(), bridges.end());
    int l = unique(bridges.begin(), bridges.end()) - bridges.begin();
    cout << l << "\n";
    for (int i = 0; i < l; ++i)
        cout << bridges[i].first + 1 << ' ' << bridges[i].second + 1 << '\n';
}
