#include "isPrime.h"
#include "polard_brent.h"
#include <map>
#include <vector>

template<typename T>
void factor(T n, std::map<T,int>& ans) {

    if (n == 1) return;
    if (isPrime(n)) { ++ans[n]; return; } /// got here n as a factor
    T divisor = pollard_brent_montgomery(n);
    factor(divisor, ans);
    factor(n / divisor, ans);
}

template<typename T>
std::vector<T> prime_factor(T n) {
    std::vector<T> ret;
    ret.push_back(n);
    for(size_t i = 0;i < ret.size(); ){
        if (isPrime(ret[i])) { ++i;continue; } /// got here n as a factor

        ret.push_back(pollard_brent_montgomery(ret[i]));

        ret[i] /= ret.back();


    }




    return ret;
}

