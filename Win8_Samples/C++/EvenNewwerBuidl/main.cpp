#include <iostream>

using namespace std;

#include "DortyBuild.h"
#include "DortyMatrix.h"
#include "DortyGeometry.h"
#include "DortyBigNum.h"


int main()
{
    AppBuild();

    int a,b,c,d;
    cin >> a >> b >> c >> d;
    Point P1(a,ToRad(b),1);
    Point P2(c,ToRad(d),1);
    Segment S(P1,P2);

    cout << fixed << setprecision(7)<< S.getLength() << endl;

    return 0;
}
