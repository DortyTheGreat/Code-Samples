#include <iostream>
#include "../DortyLibs/DortyBuild.h"
#include "../DortyLibs/utility/min_max.h"
using namespace std;

int main()
{
    AppBuild();
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << min(a,b,c,d);
    return 0;
}
