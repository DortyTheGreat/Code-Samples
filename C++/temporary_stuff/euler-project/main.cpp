#include <iostream>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

const uint64_t mod = 993353399;

map<uint64_t, uint64_t> phi_precalc;

uint64_t phi(uint64_t n) {

    if (phi_precalc.find(n) != phi_precalc.end()) return phi_precalc[n];

    uint64_t orig_n = n;
    uint64_t result = n;
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return phi_precalc[orig_n] = result;
}

bool IsSquare(uint64_t number){
    return (uint64_t)(sqrtl( number)) == sqrtl( number);
}

/// return all divisors
vector<uint64_t> all_divisers(uint64_t number){
    vector<uint64_t> ans;
    uint64_t sqrt_= sqrtl( number );
    for(uint64_t i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(uint64_t counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}



uint64_t f(uint64_t n){

    auto vc = all_divisers(n);
    uint64_t summ = 0;
    for(auto elem : vc){
        auto vc2 = all_divisers(elem);

        uint64_t summ_inside = 0;

        for(auto elem2 : vc2){
            uint64_t add = elem2;
            /// gcd = elem2
            add *= phi(n/elem2);
            add %= mod;
            summ_inside += add;
            summ_inside %= mod;
        }

        //cout << n/elem << endl;
        //cout << phi(n/elem) << endl;
        //cout << phi(n) << " " << phi(n/elem) << " " << phi(elem) << " " << elem << endl;

        uint64_t mult = phi(n/elem);

        summ_inside *= summ_inside;
        summ_inside %= mod;

        summ_inside *= mult;
        summ_inside %= mod;


        //cout << elem << " " << summ_inside << " " << mult << endl;

        summ += summ_inside;
        summ %= mod;
    }

    uint64_t zeros = n;
    zeros *= zeros;
    zeros %= mod;
    summ += zeros;
    summ %= mod;

    return summ;

}

bool IsPrime(uint64_t a){
    if(a < 2){return 0;}
    uint64_t limit = sqrtl(a);
    for(uint64_t i=2;i<=limit;i++){
        if(a%i == 0){return 0;}
    }
    return 1;
}

int main()
{
    uint64_t num_10_16 = 10000000000000000;
    uint64_t num_10_6 = 1000000;

    uint64_t BIG_BOY = 0;

    for(uint64_t i = num_10_16; i <= num_10_16 + num_10_6; ++i){
        if (IsPrime(i)){
            cout << i << endl;
            BIG_BOY += f(i-1);
            BIG_BOY %= mod;
        }
        ///cout << i << endl;
    }
    cout << BIG_BOY;

    ///cout << "Hello world!" << endl;
    return 0;
}
