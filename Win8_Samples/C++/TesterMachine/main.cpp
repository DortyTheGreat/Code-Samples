#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long ITTER = 10000;

    long long a,b,k;
    cin >> a >> b >> k;
    long long ans = 0;
    for (int i = 1; i < ITTER; i++) {


        long long SearchY = i * i * i;

        if (SearchY >= a && SearchY <= b){
            for (int j = 1; j < ITTER; j++) {

            long long SearchX = j * j;

            if (SearchX >= a && SearchX <= b){
                if (abs(SearchX - SearchY) <= k){
                ans++;
                //cout << i <<" " << j << endl;
            }
            }


        }

        }



    }

    cout << ans;
}
