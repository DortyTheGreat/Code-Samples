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

#include <iostream>


#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}



int main()
{
    for(int tests = 1; tests <= 55; ++tests){
        ofstream fout("out" + to_str(tests) + ".txt");
        int sz = pow(1.35, tests);
        fout << sz << endl;
        for(int i = 0;i < sz; ++i){
            fout << (char)('a' + rnd(0,25));
        }


    }
    return 0;
}
