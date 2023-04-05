#include <iostream>

using namespace std;

int main()
{
    uint64_t a,b;
    cin >> a >> b;
    uint64_t res = a * b;

    cout << &res << endl;

    cout << &res + 1 << endl;
    cout << (uint32_t*)(&res) + 1 << endl;
    cout << *(&res) << endl;

    cout << *( (uint32_t*)(&res) + 1 ) << endl;

    return 0;
}
