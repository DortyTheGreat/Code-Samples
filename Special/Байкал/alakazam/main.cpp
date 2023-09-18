#include <bits/stdc++.h>

using namespace std;

using namespace std;

const int MAXN = 250 * 1001 + 15;

int n;
long double a[MAXN];
long double tree[4 * MAXN];
long double mod[4 * MAXN];

void build_tree(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}


void push(int v, int tl, int tr) {
    if (mod[v] != 0 && v * 2 + 1 < 4 * MAXN) {


        mod[v * 2] = mod[v * 2 + 1] = mod[v];
        mod[v] = 0;


        int tm = (tl + tr) / 2;
        tree[v * 2] = (tm - tl + 1) * mod[v * 2];
        tree[v * 2 + 1] = (tr - tm) * mod[v * 2 + 1];
    }
}


long double get_sum(int l, int r, int v, int tl, int tr) {

    if (l <= tl && tr <= r) {
        return tree[v];
    }


    if (tr < l || r < tl) {
        return 0;
    }


    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return get_sum(l, r, v * 2,     tl,     tm)
         + get_sum(l, r, v * 2 + 1, tm + 1, tr);
}

/// [l;r]
void assign(int l, int r, long double val, int v, int tl, int tr) {

    if (l <= tl && tr <= r) {
        tree[v] = val * (tr - tl + 1);
        mod[v] = val;
        return;
    }


    if (tr < l || r < tl) {
        return;
    }


    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    assign(l, r, val, v * 2,     tl,     tm);
    assign(l, r, val, v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}


void solve() {
    int n, m;
    cin >> n >> m;

    build_tree(1, 0, n - 1);

    for(int i = 0; i < n; ++i){
        int num;
        cin >> num;
        /// get_sum(l, r, 1, 0, n - 1) è assign(l, r, val, 1, 0, n - 1);
        assign(i, i, num, 1, 0, n - 1);
        ///cout << get_sum(i, i, 1, 0, n - 1) << endl;
    }

    int l, r, x;

    string req;

    while (m--) {
        cin >> req;
        if (req == "shuffle") {
            cin >> l >> r;
            --l;
            --r;
            long double summ = get_sum(l, r, 1, 0, n - 1) / (r-l+1);

            ///cout << summ << endl;

            assign(l, r, summ, 1, 0, n - 1);
        }
        if (req == "get") {
            cin >> l;
            --l;
            cout << fixed <<setprecision(15) << get_sum(l, l, 1, 0, n - 1) << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios_base::boolalpha);
    solve();
}
