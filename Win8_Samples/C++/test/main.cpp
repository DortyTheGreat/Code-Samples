#include <bits/stdc++.h>

using namespace std;

#define all(a) (a).begin(), (a).end()
#define ll long long

const int k = 599;
const int maxn = 1e5 + 100;

const ll mod = 1000000007;

int answers[maxn];
vector<int> factor[maxn];

struct Query {
    int l, r, id;

    Query() {}

    Query(int _l, int _r, int _id) {
        l = _l;
        r = _r;
        id = _id;
    }

    inline bool operator<(const Query &q) const {
        if (l / k != q.l / k)
            return l < q.l;
        return r < q.r;
    }
};

ll binpow(ll a, int n) {
    ll res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return binpow(x, mod - 2);
}

int l = 0, r = 0;
ll ans = 1;
ll del = 1;

const int maxa = 1e7;
int state[maxa];

void add_right() {
    for (int i : factor[r]) {
        del *= state[i];
        del %= mod;
        state[i] += 1;
        ans *= state[i];
        ans %= mod;
    }
    r += 1;
}

void del_right() {
    r -= 1;
    for (int i : factor[r]) {
        del *= state[i];
        del %= mod;
        state[i] -= 1;
        ans *= state[i];
        ans %= mod;
    }
}

void add_left() {
    l -= 1;
    for (int i : factor[l]) {
        del *= state[i];
        del %= mod;
        state[i] += 1;
        ans *= state[i];
        ans %= mod;
    }
}

void del_left() {
    for (int i : factor[l]) {
        del *= state[i];
        del %= mod;
        state[i] -= 1;
        ans *= state[i];
        ans %= mod;
    }
    l += 1;
}

void solve() {
    fill(state, state + maxa, 1);
    int n, q;
    cin >> n >> q;
    int num;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        for (int j = 2; j * j <= num; ++j) {
            while (num % j == 0) {
                factor[i].push_back(j);
                num /= j;
            }
        }
        if (num != 1)
            factor[i].push_back(num);
    }
    Query queries[q];
    for (int i = 0; i < q; ++i) {
        int lq, rq;
        cin >> lq >> rq;
        lq--;
        queries[i] = Query(lq, rq, i);
    }
    sort(queries, queries + q);
    for (Query query : queries) {
        while (r < query.r)
            add_right();
        while (r > query.r)
            del_right();
        while (l < query.l)
            del_left();
        while (l > query.l)
            add_left();
        answers[query.id] = ans * inv(del) % mod;
    }
    for (int i = 0; i < q; ++i) {
        cout << answers[i] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
