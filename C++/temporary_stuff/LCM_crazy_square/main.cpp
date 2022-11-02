#include <iostream>
#include <ctime>
using namespace std;

#define pure __attribute__((always_inline))

struct LCM{
    uint64_t mult, incr, mod;
    pure uint64_t step(uint64_t arg){ return (arg*mult + incr) % mod; }
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

    reqursion(start,"",0);



    return 0;
}
