#include <iostream>

using namespace std;

uint64_t g(uint64_t arg){
    return arg * (arg+1) / 2;
}

int main()
{
    uint64_t a,b,c;
    uint64_t x,y,z;
    cin >> a >> b >> c >> x >> y >> z;
    cout << g(x/a + y/b + z/c + 1);

    return 0;
}
