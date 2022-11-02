#include <iostream>
using namespace std;
#define int long long

const int K = 22;
int a1 = 39571099;
int b1 = 57195907;
int c1 = 46112819;

int a2 = 24558073;
int b2 = 13976087;
int c2 = 45484819;

int t = 666;

void reqursion(uint64_t num, const string& path, int depth){
    if (depth > K) return;
    if (num == t) {
        cout << path << endl;
        exit(0);
    }
    reqursion((num * a1 + b1) % c1, path+"f", depth+1);
    reqursion((num * a2 + b2) % c2, path+"s", depth+1);
}

void solve() {
    reqursion(0,"",0);
    for (int mask = 0; mask < (1 << K); ++mask) {
        int cur = 0;
        for (int i = 0; i < K; ++i) {
            if ((mask >> i) & 1)
                cur = (cur * a1 + b1) % c1;
            else
                cur = (cur * a2 + b2) % c2;
            if (cur == t) {
                for (int j = 0; j <= i; ++j) {
                    cout << ((mask >> j) & 1);
                }
                cout << '\n';
                return;
            }
        }
    }
}

signed main() {
    solve();
}
