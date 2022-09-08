#include <bits/stdc++.h>

using namespace std;

const int k = 1000;
int temp[2 * k];

struct Block {
    int data[2 * k];
    int size;
    Block *next;

    Block() : size(0), next(0) {}

    inline bool full() const {
        return size == 2 * k;
    }
};

Block *head = new Block();

void insert(int pos, int x) {
    Block *node = head;
    while (pos > node->size) {
        pos -= node->size;
        node = node->next;
    }


    memcpy(temp, node->data + pos, sizeof(int) * (2 * k - pos) ); /// Оптимизировать
    memcpy(node->data + 1 + pos, temp, sizeof(int) * (2 * k - pos - 1) ); /// Оптимизировать
    node->data[pos] = x;


    ++node->size;
    if (node->full()) {
        Block *extra = new Block();
        extra->next = node->next;
        node->next = extra;
        extra->size = node->size = k;
        memcpy(extra->data, node->data + k, sizeof(int) * k);
    }
}

int get(int pos) {
    Block *node = head;
    while (pos >= node->size) {
        pos -= node->size;
        node = node->next;
    }
    return node->data[pos];
}

void solve() {
    int q;
    cin >> q;
    char c;
    int idx, val;
    while (q--) {
        cin >> c;
        if (c == '+') {
            cin >> idx >> val;
            insert(idx, val);
        }
        if (c == '?') {
            cin >> idx;
            cout << get(idx) << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
