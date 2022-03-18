#include <iostream>
#include <map>
using namespace std;
#define int long long
const int modul = 1000000007;

class PrimeExpansion{
public:
    map<int,int> Data; /// prime, amount of that primes


    void operator+=(PrimeExpansion second){
        for (auto i : second.Data){
            Data[i.first] += i.second;
        }
    }

    PrimeExpansion(){}
    PrimeExpansion(int number){
        for(int i = 2;i*i<=number;i++){
            while(number%i == 0){
                Data[i]++;
                number/= i;
            }
        }
        if (number != 1){
            Data[number]+= 1;
        }
    }

    int mult(){
        int returner = 1;
        for (auto i : Data){
            returner *= (i.second+1);
            returner %= modul;
        }
        return returner;
    }

};


signed main()
{

    PrimeExpansion ab(121);

    for (auto i : ab.Data){
        cout << i.first << " " << i.second << endl;
    }

    PrimeExpansion Suffixes[10000];

    int true_suff[10000];

    int n,q;
    cin >> n >> q;

    int number;
    cin >> number;

    Suffixes[0] = PrimeExpansion(number);
    true_suff[0] = Suffixes[0].mult();
    for(int i = 1;i<n;i++){

        cin >> number;
        Suffixes[i] = Suffixes[i-1];
        Suffixes[i] += PrimeExpansion(number);
        true_suff[i] = Suffixes[i].mult();
    }

    for(int i = 0;i<q;i++){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        int sudo_ans;
        if (a == 0){
            sudo_ans = true_suff[b];
        }else{
            sudo_ans = true_suff[b]/true_suff[a-1];
        }
        cout << sudo_ans << endl;
    }


    for(int i =0;i<n;i++){
        for (auto j : Suffixes[i].Data){
            cout << j.first << " " << j.second << endl;
        }
        cout << endl;
    }


    for(int i =0;i<n;i++){
        cout << true_suff[i] << endl;
    }


    ///cout << "Hello world!" << endl;
    return 0;
}
