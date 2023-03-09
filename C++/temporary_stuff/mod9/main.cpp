#include <iostream>

using namespace std;

typedef   uint32_t    u32;

unsigned int in_u32(void) { u32 c, x = 0; while (c = _getchar_nolock(), c < 48 || c > 57); while (47 < c && c < 58) { x = x * 10 + c - 48; c = _getchar_nolock(); } return x; }


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    uint64_t b = 0;
    uint64_t m = in_u32();
    char c;



    while (c = _getchar_nolock(), 47 < c && c < 58){
        b = (b*10 + (c - '0')) % m;
    }


    cout << b << endl;

    return 0;
}
