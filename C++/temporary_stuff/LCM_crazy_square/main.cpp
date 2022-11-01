#include <iostream>
#include <ctime>
using namespace std;

struct LCM{
    uint64_t mult, incr, mod;
    uint64_t step(uint64_t arg){ return (arg*mult + incr) % mod; }
};

int main()
{
    LCM L1, L2;
    cin >> L1.mult >> L1.incr >> L1.mod;
    cin >> L2.mult >> L2.incr >> L2.mod;

    uint64_t start, end;

    cin >> start >> end;


    srand(time(0));



    cout << "Hello world!" << endl;
    return 0;
}
