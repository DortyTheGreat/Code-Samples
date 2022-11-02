#include <iostream>

using namespace std;

#include <vector>
#include <cmath>

bool IsSquare(long long number){
    return (int)(sqrt( abs(number))) == sqrt( abs(number));
}

/// return all divisors
vector<long long> all_divisers(long long number){
    number = abs(number);
    vector<long long> ans;
    int sqrt_= sqrt( number );

    auto copy = number;

    for(int i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}

int requr_calc(int arg, int index, const vector<long long>& divs){
    int ret = 1;
    for(int i = index; arg / divs[i] >= divs[i] ;++i ){
        if (arg % divs[i] == 0) ret += requr_calc(arg/divs[i], i, divs);
    }
    return ret;

}

int A001055(int arg){
    if (arg < 4) return 1;

    auto v = all_divisers(arg);

    return requr_calc(arg,1,v);
}

int main()
{

    int max_ = -1;
    for(int i = 0;i<10000000;++i){
        auto v = A001055(i);
        if (v > max_){
            max_ = v;
            cout << i << " " << v << endl;
        }

    }


    return 0;
}
