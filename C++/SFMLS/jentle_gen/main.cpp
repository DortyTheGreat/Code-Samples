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
    for(int64_t tests = 1; tests < 100; ++tests){

        int64_t treshN = 4 + pow(1.06,tests); /// 3 + 339

        int64_t treshQ = 5 + pow(1.12,tests); /// 4 + 0.835 * 10^5


        int64_t N = rnd(3,treshN);
        int64_t M = rnd(3,treshN);

        int64_t Q = rnd(4,treshQ);

        ofstream fout("out" + to_str(tests) + ".txt");

        fout << N << " " << M << " " << Q << endl;

        fout << rnd(0,N-1) << " " << rnd(0,M-1) << endl;

        vector<vector<int> > vcc;

        vcc.resize(M);

        for(int i = 0; i < M; ++i){
            vector<int> a(N);

            for(int j = 0; j < N;++j){
                a[j] = j + N*i;
            }

            vcc[i] = a;
        }


        for(int i = 0; i < 1001 * 1001; ++i){
            swap(vcc[rnd(0,M-1)][rnd(0,N-1)],vcc[rnd(0,M-1)][rnd(0,N-1)]);
        }

        for(int i = 0; i < M; ++i){

            for(int j = 0; j < N;++j){
                fout << vcc[i][j] << " ";
            }
            fout << endl;


        }

        for(int i = 0; i < Q; ++i){


            fout << rnd(0,N-1) << " " << rnd(0,M-1)<< endl;


        }




    }
    return 0;
}
