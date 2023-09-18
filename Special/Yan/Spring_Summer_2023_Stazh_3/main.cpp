#include <iostream>
#include <vector>
using namespace std;

signed main()
{
    int n;
    cin >> n;

    long double ruble0 = 1;

    long double akci1 = -1;
    vector<int> akci1_v;

    long double ruble1 = -1;
    vector<int> ruble1_v;

    long double akci2 = -1;
    vector<int> akci2_v;

    long double ruble2 = -1;
    vector<int> ruble2_v;

    for(int i = 0; i < n; ++i){
        long double v;
        cin >> v;

        if (akci2 != -1){
            if (ruble2 < akci2 * v){
                ruble2 = akci2 * v;
                ruble2_v = akci2_v;
                ruble2_v.push_back(i+1);
            }
        }

        if (ruble1 != -1){
            if (akci2 < ruble1 / v){
                akci2 = ruble1 / v;
                akci2_v = ruble1_v;
                akci2_v.push_back(i+1);
            }
        }

        if (akci1 != -1){
            if (ruble1 < akci1 * v){
                ruble1 = akci1 * v;
                ruble1_v = akci1_v;
                ruble1_v.push_back(i+1);
            }
        }

        if (ruble0 != -1){
            if (akci1 < ruble0 / v){
                akci1 = ruble0 / v;
                akci1_v = {i+1};
            }
        }
    }


    if (ruble2 > ruble0 && ruble2 > ruble1){
        cout << 2 << endl;
        cout << ruble2_v[0] << " " << ruble2_v[1] << endl;
        cout << ruble2_v[2] << " " << ruble2_v[3] << endl;
        return 0;
    }

    if (ruble1 > ruble0){
        cout << 1 << endl;
        cout << ruble1_v[0] << " " << ruble1_v[1] << endl;
        return 0;
    }

    cout << 0 << endl;

    return 0;
}
