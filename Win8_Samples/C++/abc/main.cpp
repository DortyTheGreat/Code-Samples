
#include <bits/stdc++.h>

using namespace std;

#define int long long

int counter;
int _size = 2001;
vector<vector<int>> grid(_size, vector<int>(_size));
void search_near_points(int i, int j) {
  ++counter;
  grid[i][j] = 0;
  if (i - 1 > -1 && grid[i - 1][j]) {
    search_near_points(i - 1, j);
  }
  if (j - 1 > -1 && grid[i][j - 1]) {
    search_near_points(i, j - 1);
  }
  if (i + 1 < _size && grid[i + 1][j]) {
    search_near_points(i + 1, j);
  }
  if (j + 1 < _size && grid[i][j + 1]) {
    search_near_points(i, j + 1);
  }
}


signed main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int _x1, _x2, _y1, _y2, x1, x2, y1, y2;
    cin >> _x1 >> _y1 >> _x2 >> _y2, --_x1, --_y1, --_x2, --_y2;

    x1 = min(_x1, _x2) + 1001;
    x2 = max(_x1, _x2) + 1001;
    y1 = min(_y1, _y2) + 1001;
    y2 = max(_y1, _y2) + 1001;

    cout << x1 << " " << x2 << " " << y1 << " "  << y2 << endl;

    for (int u = x1; u < x2; ++u) {
      for (int v = y1; v < y2; ++v) {
        grid[u][v] = 1;
      }
    }
  }

  int res = 0;
  for (int i = 0; i < _size; i++) {
    for (int j = 0; j < _size; j++) {
      if (grid[i][j]) {
        counter = 0;
        search_near_points(i, j);
        res = max(counter, res);
      }
    }
  }

  cout << res;

ending:
  cout << endl;

  return 0;
}
