#include <iostream>
using namespace std;


const int K = 12;
uint64_t a1;
uint64_t b1;
uint64_t c1;

uint64_t a2;
uint64_t b2;
uint64_t c2;

uint64_t t;
uint64_t s;

void print(uint64_t path, bool exit_ = 1){
    bool flag = 0;
    for(int i = 30; i > -1; --i){
        bool v = ((path >> i) & 1);
        if (flag) cout << "fs"[((path >> i) & 1)];
        if (v) flag = 1;
    }
    if (exit_) exit(0);
}

const uint64_t WIDE = 12;
const uint64_t L1D_CACHE_SIZE = 32768 / 4;

void p2(uint64_t start_path, uint64_t path){
    print(start_path,0);
    print(path);
}

uint64_t memo[ L1D_CACHE_SIZE ];
void requir_opt(uint64_t num, uint64_t start_path){


    for(uint64_t path = 1;(path < (1 << WIDE) ); num = memo[++path]){
        if ( (memo[path*2] = (num * a1 + b1) % c1) == t) p2(start_path,path*2);
        if ( (memo[path*2+1] = (num * a2 + b2) % c2) == t) p2(start_path,path*2+1);
    }

}

void reqursion(uint64_t num, uint64_t path){
    if (num == t) print(path);
    if (path > (1 << (K+1)) ){ requir_opt(num,path); return; }
    reqursion((num * a1 + b1) % c1, path*2);
    reqursion((num * a2 + b2) % c2, path*2+1);
}




void solve() {
    reqursion(s,1);;
}

signed main() {
    cin >> a1 >> b1 >> c1;
    cin >> a2 >> b2 >> c2;
    cin >> s >> t;
    solve();
    return 0;
}
