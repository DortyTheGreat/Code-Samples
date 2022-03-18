#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a,b,c,d,e;
    cin >> a >> b >> c >> d >> e;
    float A = min(min(a,b),c);
    float B= min(min(max(a,b),max(c,b)), max(a,c));

    float E = max(d,e);
    float D = min(d,e);
    float dg = sqrt(A*A + B*B);
    float x1 = (D - sqrt(dg*dg - E*E))/2;
float x2 = (E - sqrt(dg*dg - D*D))/2;
float poten = sqrt(x1*x1 + x2*x2);
if((poten >= A) || (A <= D && B <= E)){
    cout << "YES";

}else{
cout << "NO";
}
}
//1231
