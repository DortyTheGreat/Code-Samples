#include <iostream>

#define int uint64_t

using namespace std;

const uint64_t mod = 998244353;

signed main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    uint32_t arr[3 * 100 * 1001];

    cin >> n;

    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    uint64_t summ = 0;

    for(int b = 0; b < 32; ++b){

        int zeros = 0;
        int ones = 0;


        int zero_count = 0;
        int one_count = 0;
        for(int i = 0; i < n; ++i){
            int v = (arr[i] >> b) & 1;
            if (v){
                swap(zero_count, one_count);
                one_count++;
                swap(zeros, ones);
            }else{
                zero_count++;
            }

            zeros += zero_count;
            ones += one_count;

            uint64_t p_add = (1 << b);
            p_add *= ones;
            p_add %= mod;
            ///cout << p_add << endl;
            summ += p_add;
            summ %= mod;

        }

    }


    cout << summ;

    return 0;
}
