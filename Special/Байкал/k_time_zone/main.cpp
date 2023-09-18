#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        int h,m;
        cin >> h >> m;
        char tt;
        cin >> tt >> tt >> tt;
        double time;
        cin >> time;

        time -= 8;

        double signum = 1;
        if (time < 0){
            signum = -1;
        }

        time = abs(time);

        h += signum*floor(time);
        m += signum* round( (time - floor(time))*60 );

        if (m < 0){
            m += 60;
            h -= 1;
        }
        if (m >= 60){
            m -= 60;
            h += 1;
        }

        if (h < 0){
            h += 24;
        }

        if (h >= 24){
            h -= 24;
        }


        if (m < 0){
            m += 60;
            h -= 1;
        }
        if (m >= 60){
            m -= 60;
            h += 1;
        }

        if (h < 0){
            h += 24;
        }

        if (h >= 24){
            h -= 24;
        }

        cout << setfill('0') << setw(2) << h;
        cout <<":";
        cout << setfill('0') << setw(2) << m;
        cout << '\n';

    }
    cout << endl;

    return 0;
}
