#include <iostream>
#include <vector>

using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &st) {
    for(auto elem : st){
        out << elem << ' ';
    }

    return out;
}


vector<int> f(int x) {

    vector<int> ret;

    int res = 0;
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            ret.push_back(i);
            x /= i;
        }
    }
    if (x != 1)
        ret.push_back(x);
    return ret;
}

void solve() {
    int n;
    cin >> n;

    long long ans = 0;
    for(int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cout << f(x) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
