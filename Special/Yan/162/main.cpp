#include <iostream>
#include <iomanip>
using namespace std;

uint64_t tri(uint64_t n){
    return (n-1)*(n)/2;
}


int sumOfDigs(string s){
    int ret = 0;
    for(int i = 0; i < s.size(); ++i){
        ret += s[i] - '0';
    }
    return ret;
}

int main()
{
    string n;
    cin >> n;

    int s = n.size();

    int k;
    cin >> k;

    long double PROBABILITY_TO_STAY_IN_PLACE = (long double)(1) - ((long double)(s - 1) / tri(s));
    long double PROBABILITY_TO_COME_BACK = (long double)(1) / tri(s);

    long double _end_1 = 1; /// Вероятность того, что мы в конце

    for(int i = 0; i < k; ++i){
        //cout << fixed << setprecision(10) << _end_1 << endl;
        _end_1 = _end_1 * PROBABILITY_TO_STAY_IN_PLACE + ( (long double)(1) - _end_1) * PROBABILITY_TO_COME_BACK;
    }

    long double _end_0 = 0; /// Вероятность того, что мы в конце

    for(int i = 0; i < k; ++i){
        //cout << fixed << setprecision(10) << _end_0 << endl;
        _end_0 = _end_0 * PROBABILITY_TO_STAY_IN_PLACE + ( (long double)(1) - _end_0) * PROBABILITY_TO_COME_BACK;
    }

    if (k == 0){
        if (sumOfDigs(n) % 3 == 0 ){
            if ((n[n.size() - 1]-'0') % 2 == 0){
                cout << "1.000000000000000" << endl;
                return 0;
            }
        }

        if ((n[n.size() - 1]-'0') % 5 == 0){
            cout << "1.000000000000000" << endl;
            return 0;
        }

        cout << "0.000000000000000" << endl;
        return 0;
    }



    int candidates = 0;
    bool isDiv3 = (sumOfDigs(n) % 3 == 0);
    //cout << isDiv3 << endl;
    uint64_t t = tri(n.size());

    for(int i = 0; i < n.size() - 1; ++i){
        if ((n[i]-'0') == 5 || (isDiv3 && ((n[i]-'0') % 2 == 0)) ) candidates++;
    }


    long double prob = candidates * _end_0;
    //cout << candidates << " " << prob << endl;
    if ((n[n.size() - 1]-'0') == 5 || (isDiv3 && ((n[n.size() - 1]-'0') % 2 == 0)) ){
        prob += _end_1;
    }

    cout << fixed << setprecision(12) << prob;


    return 0;
}
