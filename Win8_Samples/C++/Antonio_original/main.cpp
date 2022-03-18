#pragma GCC optimize("O3")
#pragma target("avx2.0")

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

#define int long long

int flag = 0;
void gSort(int i, vector<int>* graph, int* color, vector<int>& res, int c) {
    if (color[i] == 1 && flag == 0) {
        flag = 1;
        return;
    }
    if (color[i]) return;

    color[i] = 1;
    for (int j = 0; j < graph[i].size(); j++) {
        gSort(graph[i][j], graph, color, res, c);
    }
    res.push_back(i);

    color[i] = c;
}

signed main() {
  int n, m;
  cin >> n;
  int* color = new int[n] {};
  vector<int>* graph = new vector<int>[n];
  vector<int>* inv_graph = new vector<int>[n];
  vector<int> res;

  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    inv_graph[v - 1].push_back(u - 1);
  }

  for (int i = 0; i < n; i++) {
    if (!color[i]) {
      gSort(i, graph, color, res, i + 1);
    }
  }

  reverse(res.begin(), res.end());

  vector<int> _res;
  int* inv_color = new int[n] {};
  set<int> used;
  for(auto val: res) {
    //cout << val << endl;
    gSort(val, inv_graph, inv_color, _res, val + 1);
  }
  int counter = 0;
  set<pair<int, int>> diff_col;
  for (int i = 0; i < n; ++i) {
    for (auto v: inv_graph[i]) {
      //cout << i << " " << v << " "  << inv_color[i] << " " << inv_color[v] << endl;
      if (inv_color[i] != inv_color[v]) {
        counter++;
        diff_col.emplace(inv_color[i], inv_color[v]);
      }
    }
  }

  cout << diff_col.size();

ending:
  cout << endl;

  system("pause");
  return 0;
}
