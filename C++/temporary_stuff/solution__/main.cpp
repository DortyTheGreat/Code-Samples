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
                    ret += (((mask >> j) & 1) == 0) ? 's' : 'f';
                }
                return ret;
            }
        }
    }
}


int main()
{


    cin >> L1.mult >> L1.incr >> L1.mod;
    cin >> L2.mult >> L2.incr >> L2.mod;

    uint64_t start;
    cin >> start;
    cin >> find_;

    cout <<path2(start);
    ///reqursion(start,"",0);



    return 0;
}
