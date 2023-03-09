#include <iostream>
#include <bitset>
using namespace std;

const int num = 1001 * 1001; /// 1001 * 1001

std::bitset< 6 * 11 * num / 2 > bst;

void fill_(int value, int index, int bits){
    for(int i = 0; i < bits; ++i){
        bst[index*bits + i] = ((value >> i) & 1);
        ///cout << ((num >> i) & 1) << endl;
    }
}

int get(int index, int bits){
    int val = 0;

    for(int i = bits - 1; i > -1; --i){
        val *= 2;
        val += bst[index*bits + i];
    }
    return val;
}


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int a;

    cin >> a;
    char t;
    int ans = 0;

    for(int i = 0;i < a/2;++i){
        cin >> t;
        int num = t - 'a';

        fill_(num,i,6);

    }

    if (a % 2 == 1){
        cin >> t;
    }

    for(int i = 0;i < a/2;++i){
        cin >> t;
        int num = t - 'a';
        ans += abs(num - get(a/2 - i - 1,6) );
    }

    cout << ans << endl;
    return 0;
}
