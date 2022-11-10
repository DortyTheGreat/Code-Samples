#include <iostream>

using namespace std;
#include <bitset>
int main()
{
    double a = 642.1875 - 9.375;
    ///cout << (bitset<64>) (reinterpret_cast<long>(&b)) << endl;

    bitset<64> b = *(reinterpret_cast<long long*>(&a));
    cout << b << endl;
    cout << "Hello world!" << endl;
    return 0;
}
