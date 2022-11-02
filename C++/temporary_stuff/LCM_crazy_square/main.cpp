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
int main()
{
    freopen("input.txt", "r", stdin);
    const int I = 20;
    cin >> L1.mult >> L1.incr >> L1.mod;
    cin >> L2.mult >> L2.incr >> L2.mod;

    uint64_t start = 567;
    uint64_t find = start;
    for(int i = 0; i < I; ++i){
        if (rnd(0,1) ){
            find = L1.step(find);
        }else{
            find = L2.step(find);
        }
    }
    cout << find << endl;

    unordered_map<uint64_t, string> mp = {{start, ""}};


    for(int itter = 0; itter < I + 1; ++itter){
        unordered_map<uint64_t, string> new_mp;
        new_mp.reserve(1 << (itter+3) );

        for (auto elem : mp){
            if (elem.first == find){
                cout << elem.second << " " << itter << endl;
                return 0;
            }
            new_mp[L1.step(elem.first)] = elem.second+"f";
            new_mp[L2.step(elem.first)] = elem.second+"s";
        }
        mp = new_mp;

    }


    return 0;
}
