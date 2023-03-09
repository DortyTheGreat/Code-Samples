#include <iostream>
#include <complex>
#include <cmath>

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <numbers>

using namespace std;

using namespace std::complex_literals;

int main()
{


    constexpr long double mag {1.0};
    int n;
    cin >> n;


    long double PI = acos(-1);
    std::complex<long double> z1 = 0;

    for(int i = 0; i < n;++i){
        bool is;
        cin >> is;
        if (is)
            z1 += std::polar(mag, 2 * PI * i / n);
    }

    if (abs(z1.real()) < 1e-5){
        if (abs(z1.imag()) < 1e-5){
            cout << "YES";
            return 0;
        }
    }


    cout << "NO" << endl;
    return 0;
}
