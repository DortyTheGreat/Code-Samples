#include <iostream>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int n = 10;
const int m = 10;

void solve() {
    int x2, y2;
    cin >> x2 >> x2 >> x2 >> y2;
    int x1 = 0;
    int y1 = 0;
    for (int i = 0; i < 1; ++i) {
        string path = "";
        path += string(max(0, y2 - y1), 'd');
        path += string(max(0, y1 - y2), 'u');
        path += string(max(0, x2 - x1), 'r');
        path += string(max(0, x1 - x2), 'l');
        cout << path;
        x1 = x2;
        y1 = y2;
        cin >> x2 >> y2;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    solve();
}
