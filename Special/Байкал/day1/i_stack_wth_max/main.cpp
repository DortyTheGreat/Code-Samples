#include <iostream>

using namespace std;

/// 0 - val, 1 - maxptr
int arr[400000][2];

int main()
{
    int n;
    cin >> n;

    int carret = 0;
    int max_ = -9999;
    int max_index = -1;
    for(int i = 0;i < n; ++i){
        string r;
        cin >> r;
        if ( r == "push"){
            int val;
            cin >> val;
            if (carret == 0){

                arr[carret][0] = val;
                arr[carret][1] = -1;

                max_ = val;
                max_index = 0;
            }else{

                arr[carret][0] = val;
                arr[carret][1] = max_index;

                if (val > max_){
                    max_ = val;
                    max_index = carret;
                }
            }


            ++carret;
        }

        if (r == "max"){
            cout << max_ << endl;
        }


        if (r == "pop"){
            if (carret == 1){
                carret = 0;
            }else{

                if ( arr[ arr[carret-1][1] ][0] < arr[carret-1][0] ){
                    /// Значит указывает на предыдущий максимум
                    max_ = arr[ arr[carret-1][1] ][0];
                    max_index = arr[carret-1][1];
                }

                carret--;
            }
        }
    }

    return 0;
}
