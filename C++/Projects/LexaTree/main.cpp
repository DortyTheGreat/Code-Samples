#include <bits/stdc++.h>

using namespace std;




class KindArray{
private:



    struct Item {
        int cnt, x, Priority;
        Item *l, *r;
        Item() {}
        Item (int x) : Priority((rand() << 16u) + unsigned(rand())), x(x), l(0), r(0) {}
    };

    Item *t;
    Item *t1;
    Item *t2;
    size_t sz = 0;

    int cnt(Item *t) {
        return t ? t->cnt : 0;
    }

    void upd(Item *t) {
        if (t) {
            t->cnt = 1 + cnt(t->l) + cnt(t->r);
        }
    }

    void Merge(Item *l, Item *r, Item *&t) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->Priority > r->Priority)
            Merge(l->r, r, l->r),  t = l;
        else
            Merge(l, r->l, r->l),  t = r;
        upd(t);
    }

    void Split(Item *t, Item *&l, Item *&r, int pos) {
        if (!t) {
            l = r = 0;
            return;
        }
        if (pos <= cnt(t->l))
            Split(t->l, l, t->l, pos),  r = t;
        else
            Split(t->r, t->r, r, pos - 1 - cnt(t->l)),  l = t;
        upd(t);
    }

public:
    KindArray(int start_val){
        sz++;
        t = new Item(start_val); /// ??
    }

    void insert(int index, int value){
        sz++;
        Split(t,t1,t2,index);
        Merge(t1,new Item(value),t1);
        Merge(t1,t2,t);
    }

    inline size_t size(){
        return sz;
    }

    int operator[](int index){
        int ret;

        Split(t,t,t1,index);
        t2 = t1;
        while (t2->l)
            t2 = t2->l;
        ret = t2->x;
        Merge(t,t1,t);
        return ret;
    }
};

void solve() {




    int q;
    cin >> q;
    char c;
    int idx, val;
    q--;
    cin >> c >> idx >> val;
    KindArray KD(val);
    while (q--) {
        cin >> c;
        if (c == '+') {
            cin >> idx >> val;
            KD.insert(idx,val);
        }
        if (c == '?') {
            cin >> idx;
            cout << KD[idx] << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
