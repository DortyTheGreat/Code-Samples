#include <iostream>
#include <iomanip>
using namespace std;
//Clock MainClock;
#include "../DortyLibs/DortyBuild.h"

#include "../DortyLibs/DortyGeometry.h"


using namespace std;

int main()
{
    AppBuild();
    Triangle A;
    cin >> A;
    cout << fixed << setprecision(9) << A.getMedianCross();




    return 0;
}
