#include <iostream>
#include <cmath>
using namespace std;

int main()
{




    int n;
    cin >> n;
    for(int i = 2; i * i <= n; ++i ){
        if (n % i == 0){
            /// n делится на i
            cout << n/i << " " << n - n/i;
            return 0;
        }
    }

    /// Число простое -> Ответ:
    cout << 1 << " " << n-1 << endl;


    return 0;
}
