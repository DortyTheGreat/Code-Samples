#include <iostream>

using namespace std;

int main()
{

    uint64_t b = 0;
    uint64_t m;
    cin >> m;
    char c;



    while (cin >> c, 47 < c && c < 58){

        b = (b*10 + (c - '0')) % m;
    }


    cout << b%9 << endl;

    return 0;
}
