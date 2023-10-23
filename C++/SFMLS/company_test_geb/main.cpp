#include <iostream>
#include <set>
#include <fstream>
#include <algorithm>
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
    for(int64_t tests = 1; tests < 100; ++tests){

        ofstream fout("out" + to_str(tests) + ".txt");

        int64_t treshQ = 4 + pow(1.08,tests); /// 3 + 2199 (2 * 10^3)

        int64_t Q = rnd(2, treshQ);

        int64_t tresh_cost = 5 + pow(1.07,tests); /// 5 + 867

        int64_t tresh_id_next = treshQ;

        int64_t percent = rnd(1,99);

        vector<int> sotrs_in; int64_t h = 0;

        sotrs_in.push_back(0);

        vector<int> sotrs_out;

        sotrs_out.push_back(1);

        for(int i = 0; i < treshQ; ++i){
            sotrs_out.push_back(sotrs_out[i] + rnd(1,tresh_id_next));
        }

        random_shuffle(std::begin(sotrs_out), std::end(sotrs_out));

        fout << Q << endl;
        for(int i = 0; i < Q; ++i){
            if (rnd(0,99) < percent){
                fout << "check " << sotrs_in[rnd(0,sotrs_in.size() - 1)] << endl;
            }else{
                fout << "add " << sotrs_out[h] << " "<< sotrs_in[rnd(0,sotrs_in.size() - 1)] << " "<< rnd(1,tresh_cost) << endl;
                sotrs_in.push_back(sotrs_out[h]);
                ++h;
            }
        }









    }
    return 0;
}
