#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int arr[100 + 5][6];
    int n;
    cin >> n;
    for(int i = 0;i < n; ++i){
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2] >> arr[i][3] >> arr[i][4] >> arr[i][5];
    }
    long double val = 0;
    for(int i = 0;i < n; ++i){

        for(int j = i+1;j < n; ++j){
            long double inc = 0;
            for(int k = 0;k < 6; ++k){
                for(int c = 0;c < 6; ++c){
                    inc += pow(arr[i][k] + arr[j][c],3);
                }
            }
            val += inc/36;
        }
    }

    val /= (n * (n-1) / 2);

    cout << fixed << setprecision(20) << val << endl;
    return 0;
}
