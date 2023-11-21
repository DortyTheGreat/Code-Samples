#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    /// sum of floor(sqrt(n*(2*r-n))) for n = 1 to (r - 1 - floor(sqrt((r^2 - (floor(sqrt(2)/2 * r))^2))))
    for(int r = 5; r < 300; ++r){

        int summ = 0;
        for(int i = 1; i <= (r - 1 - floor(sqrt((r*r - pow((floor(sqrt(2)/2 * r)), 2) )))); ++ i){
            summ += floor(sqrt(i*(2*r-i)));
        }
        cout << summ << " " << r << endl;

    }
    return 0;
}
