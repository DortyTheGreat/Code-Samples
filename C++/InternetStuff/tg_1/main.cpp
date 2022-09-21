#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const long long &a, const long long &b) {
    long long a_sum = 0, b_sum = 0;
    long long a_tmp = a, b_tmp = b;
    while (a_tmp) {
        a_sum += a_tmp % 10;
        a_tmp /= 10;
    }

    while (b_tmp) {
        b_sum += b_tmp % 10;
        b_tmp /= 10;
    }

    return a_sum > b_sum;
}

int main() {
    long long n;
    cin >> n;

    vector<long long> arr;
    arr.reserve(n);

    for (long long i = 0; i < n; ++i) {
        long long tmp;
        cin >> tmp;

        arr.push_back(tmp);
    }

    stable_sort(arr.begin(), arr.end(), cmp);

    for (const auto &elem : arr)
        cout << elem << ' ';

    return 0;
}
