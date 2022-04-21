#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 100;

struct Node {
    int s;
    int push;

    Node() : s(0), push(0) {}
    Node(int s) : s(s), push(0) {}
};

Node combine(const Node &a, const Node &b) {
    return Node(a.s + b.s);
}

Node t[4 * maxn];

void push(int id, int l, int r) {
    t[id].s += t[id].push * (r - l);
    if (r - l > 1) {
        t[id * 2 + 1].push += t[id].push;
        t[id * 2 + 2].push += t[id].push;
    }
    t[id].push = 0;
}

/// Получить сумму на отрезке с [lq;rq]
Node get(int id, int l, int r, int lq, int rq) {
    push(id, l, r);
    if (lq <= l && r <= rq)
        return t[id];
    if (l >= rq || r <= lq)
        return Node();
    int m = (l + r) / 2;
    Node tl = get(id * 2 + 1, l, m, lq, rq);
    Node tr = get(id * 2 + 2, m, r, lq, rq);
    return combine(tl, tr);
}
/// upd(0,0, n, l, r, x)

/// Первые три элемента фиксированы. (0,0,n)

/// на [l;r] += x
void upd(int id, int l, int r, int lq, int rq, int x) {
    push(id, l, r);
    if (lq <= l && r <= rq) {
        t[id].push += x;
        push(id, l, r);
        return;
    }
    if (l >= rq || r <= lq)
        return;
    int m = (l + r) / 2;
    upd(id * 2 + 1, l, m, lq, rq, x);
    upd(id * 2 + 2, m, r, lq, rq, x);
    t[id] = combine(t[id * 2 + 1], t[id * 2 + 2]);
}

void solve() {
    int n, m;
    cin >> n >> m;
    int c, l, r, x;
    while (m--) {
        cin >> c;
        if (c == 1) {
            cin >> l >> r >> x;
            upd(0, 0, n, l, r, x);
        }
        if (c == 2) {
            cin >> l >> r;
            cout << get(0, 0, n, l, r).s << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios_base::boolalpha);
    solve();
}
