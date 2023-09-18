#include <iostream>

using namespace std;

#define MOD 1000000007

// Extended Euclidean algorithm
int xGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (long long)(a / b) * y1;
    return gcd;
}

// factorial of n modulo MOD
int modfact(int n) {
    int result = 1;
    while (n > 1) {
        result = (long long)result * n % MOD;
        n -= 1;
    }
    return result;
}

// multiply a and b modulo MOD
int modmult(int a, int b) {
    return (long long)a * b % MOD;
}

int modsub(int a, int b){
    return (MOD + a - b) % MOD;
}

int modadd(int a, int b){
    return (a + b) % MOD;
}

// inverse of a modulo MOD
long long inverse(long long a, long long b = MOD){
 return 1<a ? b - inverse(b%a,a)*b/a : 1;
}

// binomial coefficient nCk modulo MOD
int bc(int n, int k)
{
    return modmult(modmult(modfact(n), inverse(modfact(k))), inverse(modfact(n - k)));
}

int n;
int arr[67];
int summ;

const int secret_number = -228;
int memo[100][100];



int get(int position, int offset){
    if (offset > n - position ) return 0;
    if (position == n) return (offset == 0);
    if (memo[position][offset] != secret_number) return memo[position][offset];

    int probablity_to_get_all;
    if (arr[position] > summ/2){
        /// число слишком больше, его возьмут оба обязательно
        probablity_to_get_all = 0;
    }else{
        cout << bc(summ - arr[position], summ/2 - arr[position]) << endl;
        cout << bc(summ,summ/2) << endl;
        cout << inverse(bc(summ,summ/2)) << endl;
        probablity_to_get_all = modmult(bc(summ - arr[position], summ/2 - arr[position]), inverse(bc(summ,summ/2))); /// fraction in modular space
    }
    cout << probablity_to_get_all << endl;

    return memo[position][offset] = modadd( modadd(modmult(get(position+1,abs(offset-1)),probablity_to_get_all),  modmult(get(position+1,abs(offset+1)),probablity_to_get_all)), \
    modmult(get(position+1,offset),modsub(1,modmult(2,probablity_to_get_all))));



}

int main()
{
    cout << bc(4,0) << endl;
    summ = 0;

    cout << inverse(2);

    cin >> n;
    for(int i =0; i < n; ++i){
        cin >> arr[i];
        summ += arr[i];
    }

    for(int i =0; i < 100; ++i){
        for(int j =0; j < 100; ++j){
            memo[i][j] = secret_number;
        }
    }

    cout << get(0,0) << endl;


    cout << "Hello world!" << endl;
    return 0;
}
