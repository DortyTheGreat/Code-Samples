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

int main()
{
    int n;
    cin >> n;

    long double p;
    cin >> p;

    int loses = 0;
    for(int simulation = 0; simulation < 10 * 1001; simulation++){
        int val = n;
        for(int step = 0; step < 1000; step++){
            long double r = (long double)(rnd(0,1000 * 1000 * 1000)) / (1000 * 1000 * 1000);

            if (p > r){
                /// p proced
                val += 3;
            }else{
                 val -= 1;
            }

            if (val == 0){
                loses++;
                break;
            }
        }
    }

    cout << ((long double)(loses)) / (10 * 1001) << endl;
    return 0;
}
