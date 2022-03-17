#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stack>
#include <fstream>
#include <queue>

using namespace std;

#define i128 long long
ofstream out("ou.txt");
ifstream in("input.txt");
stack<int> st;
queue<int> qu;

bool que_pop(int x) {

    if (qu.empty())
        return false;

    if (qu.front() != x)
        return false;
    qu.pop();
    return true;
}

bool sta_pop(int x) {

    if (st.empty())
        return false;

    if (st.top() != x)
        return false;

    st.pop();
    return true;
}

void solve() {
    int q, x;
    bool st_li = true, qu_li = true;
    in >> q;
    while (!st.empty())
        st.pop();
    while (!qu.empty())
        qu.pop();
    while (q--) {
        string s;
        in >> s >> x;
        if (s == "push") {
            qu.push(x);
            st.push(x);
        }
        else {
            st_li = min(st_li, sta_pop(x));
            qu_li = min(qu_li, que_pop(x));
        }
    }
    if (st_li && qu_li) {
        out << "both\n";
        return;
    }

    if (!st_li && !qu_li) {
        out << "none\n";
        return;
    }

    if (st_li)
        out << "stack\n";
    else
        out << "queue\n";
}

signed main() {
    int q;
    in >> q;
    while (q--)
        solve();
}
