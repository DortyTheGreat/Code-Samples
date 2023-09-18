#include <iostream>
#include <vector>
using namespace std;

#include <iomanip>

/// [a;b]


int main()
{
    int n;
    cin >> n;

    long double p;
    cin >> p;

    vector<long double> prob(2000,0);
    prob[n] = 1;

    long double ans = 0;

    for(int simulation = 0; simulation < 20 * 1001; simulation++){


        vector<long double> new_prob(2010,0);

        for(int i = 1; i < 2000; ++i){
            new_prob[i-1] += prob[i] * (1 - p);
            new_prob[i+3] += prob[i] * (p);
            if (i == 1){
                ans += new_prob[i-1];
                ///cout <<
            }

        }

        new_prob.resize(2000);
        prob = new_prob;


        ///cout << endl;


    }

    cout << fixed << setprecision(11) << ans << endl;
    return 0;
}
