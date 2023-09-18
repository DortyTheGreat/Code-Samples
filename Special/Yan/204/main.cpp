#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;
    uint64_t arr1[100];

    uint64_t summ = 0;

    for(int i = 0;i < n;++i){
        int a,b;
        cin >> a >> b;
        arr1[i] = a*b;
        summ += a*b;
    }

    for(int i = 0;i < n;++i){
        cout << fixed << setprecision(12) << (long double)(arr1[i]) / summ << endl;
    }
}
