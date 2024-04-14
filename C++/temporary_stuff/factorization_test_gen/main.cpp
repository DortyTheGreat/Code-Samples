#include <iostream>
#include <set>
#include <fstream>
using namespace std;

#include <chrono>
#include <random>
int64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937_64 mt(seed);
/// [a;b]
int64_t rnd(int64_t a, int64_t b) {
    return a + mt() % (b - a + 1);
}

#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

using namespace std;

int main()
{
    for(int64_t tests = 1; tests < 200; ++tests){
        ofstream fout("out" + to_str(tests) + ".txt");
        int numbers = min(1000000ll, tests * tests * tests);

        fout << numbers << endl;

        for(int i = 0; i < numbers; ++i){
            fout << rnd(3, int64_t(pow(1.225, tests)) + 1234) << " ";
        }

    }
    return 0;
}
