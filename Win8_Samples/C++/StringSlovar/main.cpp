#include <iostream>
#include <vector>


using namespace std;



const int p = 211, SIZE = 1000001, MOD = 1870010071;
vector<int> p_power(SIZE);

vector<int> makeHashArray(const string& s) {
    int n = s.size();
    vector<int> H(n);
    H[0] = s[0];
    for (int i = 1; i < n; ++i)
        H[i] = ((H[i - 1] * p) % MOD + s[i]) % MOD;
    return H;
}

int getSubHash(int l, int r, const vector<int>& H) {                   // [l..r]
    int big = H[r];                                                    // ....r]
    int small = ((l == 0 ? 0 : H[l - 1]) * p_power[r - l + 1]) % MOD;  // ....l-1[l....r]
    return (big + MOD - small) % MOD;
}

void init() {
    p_power[0] = 1;
    for (int i = 1; i < SIZE; ++i)
        p_power[i] = (p_power[i - 1] * p) % MOD;
}


int main(){

    init();

    string str;
    cin >> str;

    for(int i =0;i<str.size();i++){
        cout << p_power[i] << " ";
    }

    cout << endl;

    int n;
    cin >> n;

    for(int i =0;i<n;i++){
        int l,r;

        cin >> l >> r;

        l--;
        r--;

        ////cout << str.substr(l,r-l+1) << endl;;

        cout << "HASH: " << getSubHash(l,r,makeHashArray(str)) << endl;;

    }

}
