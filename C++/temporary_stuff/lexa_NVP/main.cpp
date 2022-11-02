#include <iostream>
using namespace std;

const int maxn = 200500;
int a[maxn];
int b[maxn];

int n;

#define pure __attribute__((always_inline))

struct maxint{
    int value;

    pure maxint(const int& v = 0) : value(v) {};

    pure void operator= (const int& other){
        if (value < other) value = other;
    }

    pure operator int() const{return value;}

};

struct tree {
    maxint mx;

    tree* left = nullptr;
    tree* right = nullptr;

    tree() {}
};

tree* t[2 * maxn];

int x, y, v;
void upd_y(tree* node, int l, int r) {
    if (r - l == 1) {
        node->mx = v;
        return;
    }
    int m = (l + r) / 2;
    if (y < m) {
        if (!node->left)
            node->left = new tree();
        upd_y(node->left, l, m);
    } else {
        if (!node->right)
            node->right = new tree();
        upd_y(node->right, m, r);
    }
    if (node->left)
        node->mx = node->left->mx;
    if (node->right)
        node->mx = node->right->mx;
}

void upd_x() {
    x += n;
    if (!t[x])
        t[x] = new tree();
    upd_y(t[x], 0, n);
    for (; x > 1; x >>= 1) {
        if (!t[x])
            t[x] = new tree();
        upd_y(t[x], 0, n);
    }
}

int rx, ry;
int get_y(tree* node, int l, int r) {
    if (r <= ry) {
        return node->mx;
    }
    if (l >= ry) {
        return 0;
    }
    int m = (l + r) / 2;
    maxint ma;
    if (node->left)
        ma = get_y(node->left, l, m);
    if (node->right)
        ma = get_y(node->right, m, r);
    return ma;
}

int get_x() {
    maxint res;
    int l = 0;
    int r = rx;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) {
            if (t[l])
                res =  get_y(t[l], 0, n);
            ++l;
        }
        if (r&1) {
            --r;
            if (t[r])
                res = get_y(t[r], 0, n);
        }
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
    }
    maxint ans;
    for (int i = 0; i < n; ++i) {
        int dp_i = 1;
        rx = a[i];
        ry = b[i];
        dp_i = get_x() + 1;
        ans = dp_i;
        x = a[i];
        y = b[i];
        v = dp_i;
        upd_x();
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
