#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

vector<int> object_by_k(int n, int m, unsigned int k) {
    vector<int> ans(n);

    vector<vector<unsigned int> > C(n + m + 1, vector<unsigned int>(n + m + 1));
    vector<vector<int> > big(n + m + 1, vector<int>(n + m + 1));
    for (int i = 0; i <= n + m; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            if (C[i - 1][j - 1] > ULLONG_MAX - C[i - 1][j])
                big[i][j] = true;
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            big[i][j] |= big[i - 1][j - 1];
            big[i][j] |= big[i - 1][j];
        }
    }

    int pad = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int sz = n - i - 1;
            int mx = m - j;
            if (big[sz + mx - 1][mx - 1] || C[sz + mx - 1][mx - 1] > k) {
                ans[i] = j + pad;
                pad += j;
                m -= j;
                break;
            }
            k -= C[sz + mx - 1][mx - 1];
        }
    }
    return ans;
}

unsigned int k_by_object(int n, int m, const vector<int>& a) {
    vector<vector<unsigned int> > C(n + m + 1, vector<unsigned int>(n + m + 1));
    for (int i = 0; i <= n + m; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    unsigned int ans = 0;
    int pad = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a[i] - pad; ++j) {
            int sz = n - i - 1;
            int mx = m - j - pad;
            ans += C[sz + mx - 1][mx - 1];
        }
        pad = a[i];
    }

    return ans;
}

signed main() {
    int n, m, k;
    n = 10;
    m = 10000;
    k = 1000000;
    vector<int> a = object_by_k(n, m, k);
    printf("%lld: ", k_by_object(n, m, a));
    for (int i : a) {
        cout << i << ' ';
    }
    cout << '\n';
}
