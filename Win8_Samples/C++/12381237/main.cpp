#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>
#include <set>
#include <numeric>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(11);
    int n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    vector<bool> used(n);
    vector<pair<int, int> > points;
    used[0] = 1;
    for (int i = 0; i < n; ++i) {
        pair<int, int> tmp1;
        cin >> tmp1.first >> tmp1.second;
        points.push_back(tmp1);
    }
    double ans = 0;
    for (int t = 0; t < n - 1; ++t) {
        int minn = 1e9;
        int best_point = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i])
                continue;
            for (int j = 0; j < n; ++j) {
                if (used[j])
                    continue;
                int d = (points[i].first - points[j].first) * (points[i].first - points[j].first) + (points[i].second - points[j].second) * (points[i].second - points[j].second);
                if (d < minn) {
                    minn = d;
                    best_point = j;
                }
            }
        }
        ans += sqrt((double)minn);
        used[best_point] = 1;
    }
    cout << ans << "\n";
}
