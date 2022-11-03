#include <iostream>
using namespace std;
#define int long long

const int K = 25;
int a1;
int b1;
int c1;

int a2;
int b2;
int c2;

int t = 666;
int s;
void reqursion(uint64_t num, int path){
    if (path > (1 << (K+1)) ) return;
    if (num == t) {
        bool flag = 0;
        for(int i = 30; i > -1; --i){
            bool v = ((path >> i) & 1);
            if (flag) cout << "fs"[((path >> i) & 1)];
            if (v) flag = 1;
        }
        exit(0);
    }
    reqursion((num * a1 + b1) % c1, path*2);
    reqursion((num * a2 + b2) % c2, path*2+1);
}

void solve() {
    reqursion(s,1);
}

signed main() {
    cin >> a1 >> b1 >> c1;
    cin >> a2 >> b2 >> c2;
    cin >> s >> t;
    solve();
}
