#include <iostream>
#include <ctime>
using namespace std;

#define pure __attribute__((always_inline))

struct LCM{
    uint64_t mult, incr, mod;
    pure uint64_t step(const uint64_t& arg){ return (arg*mult + incr) % mod; }
    ///pure void step(uint64_t& arg){ arg = (arg*mult + incr) % mod; }
};
LCM L1, L2;
#include <random>
#include <cassert>
#include <chrono>
int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}

uint64_t transform(string path, uint64_t start){
    for(int i = 0; i < path.size(); ++i){
        if (path[i] == 'f' ){
            start = L1.step(start);
        }else{
            start = L2.step(start);
        }
    }
    return start;
}
#include <unordered_map>
#include <map>

const int I = 20;

uint64_t find_;
void reqursion(uint64_t num, const string& path, int depth){
    if (depth > I) return;
    if (num == find_){
        cout << path << endl;
        exit(0);
    }
    reqursion(L1.step(num),path+"f",depth+1);
    reqursion(L2.step(num),path+"s",depth+1);
}

#define chk(a) if (a == 2) return ret; ret += (a == 0) ? 'f' : 's';

string to_str(uint64_t a, uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g,uint64_t h,uint64_t i,uint64_t j,uint64_t k,uint64_t l,uint64_t m,uint64_t n,uint64_t o,uint64_t p,uint64_t q,uint64_t r,uint64_t s,uint64_t t,uint64_t u,uint64_t v,uint64_t w,uint64_t x,uint64_t y,uint64_t z){
    string ret = "";
    chk(a) chk(b) chk(c) chk(d) chk(e) chk(f) chk(g) chk(h) chk(i) chk(j) chk(k) chk(l) chk(m) chk(n) chk(o) chk(p) chk(q) chk(r) chk(s) chk(t) chk(u) chk(v) chk(w) chk(x) chk(y) chk(z)
}

#define step_(arg, extra) for(arg = 0; arg < 2; ++arg){ if (i == 0) number = L1.step(number); else number = L2.step(number); if (number == find_) return to_str(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z); extra }

/**

for(a = 0; a < 2; ++a){

    if (i == 0) number = L1.step(number);
    else number = L2.step(number);
    if (number == find_) return to_str(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z);
    for(){...}
}

*/
string path(uint64_t number){
    if (number == find_) return "";

    uint8_t a = 2,b = 2,c = 2,d = 2,e = 2,f = 2,g = 2,h = 2,i = 2,j = 2,k= 2,l =2,m=2,n=2,o=2,p=2,q=2,r=2,s=2,t=2,u=2,v=2,w=2,x=2,y=2,z=2;

    step_(a, step_(b,step_(c,step_(d,step_(e,step_(f,step_(g,step_(h,step_(i,step_(j,step_(k,step_(l,step_(m,step_(n,step_(o,step_(p,step_(q,step_(r,step_(s,step_(t,step_(u,step_(v,step_(w,step_(x,step_(y,step_(z, ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ))

}

string path2(uint64_t number){
    for (int mask = 0; mask < (1 << I); ++mask) {
        int cur = number;
        for (int i = 0; i < I; ++i) {
            if ((mask >> i) & 1)
                cur = L1.step(cur);
            else
                cur = L2.step(cur);
            if (cur == find_) {
                string ret = "";
                for (int j = 0; j <= i; ++j) {
                    ret += (((mask >> j) & 1) == 0) ? 'f' : 's';
                }
                return ret;
            }
        }
    }
}


int main()
{
    freopen("input.txt", "r", stdin);

    cin >> L1.mult >> L1.incr >> L1.mod;
    cin >> L2.mult >> L2.incr >> L2.mod;

    uint64_t start = 567;
    find_ = start;
    for(int i = 0; i < I; ++i){
        if (rnd(0,1) ){
            find_ = L1.step(find_);
        }else{
            find_ = L2.step(find_);
        }
    }
    cout << find_ << endl;

    cout << path2(start);
    cout <<  endl<< transform(path2(start),start);
    ///reqursion(start,"",0);



    return 0;
}
