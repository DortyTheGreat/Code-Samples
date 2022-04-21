
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {

    freopen("inp.txt", "r", stdin);
    int n;
    cin >> n;
    cout << n << endl;
    vector<int> a(n);
    int s = 0;
    cout << "here" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cout << i << endl;
        s += a[i];
    }
    cout << n << '\n';
    sort(a.begin(), a.end(), greater<int>());
    int p = 0;
    int ans1 = 0;
    int i = 0;
    while (((long double)p + (long double)a[i]) < (long double)s * 0.3) {
        p += a[i];
        ans1 += 1;
        i += 1;
    }

    long double summi = 0;
    for (i = 0; i < ans1; ++i) {
        summi += ((long double)(a[i])  + (long double)(a[ans1 + i])) * 0.8 ;
    }
    /// 87071285
    /// 88 432 434
    /// 43334381
    cout << (long long)(summi) << endl;
    cout << ans1 << endl;

    return 0;
}


