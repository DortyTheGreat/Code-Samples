#include <iostream>

using namespace std;
#include <chrono>
#include <random>
int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}

#include <fstream>
int main()
{
    int sz = 100000; /// 2*100000
    ofstream ou("out.txt");
    int n = rnd(1,sz);
    ou << n << endl;
    for(int i =0;i<n;++i){
        ou << rnd(1,1e8) << " ";
    }
    ou << endl;
    int m = rnd(1,sz);
    ou << m << endl;
    for(int i =0;i<m;++i){
        ou << rnd(1,1e8) << " ";
    }


    return 0;
}
