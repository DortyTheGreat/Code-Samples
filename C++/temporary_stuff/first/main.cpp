/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: РўРµСЃР»Р°#9030
---Original---Code---

#include <iostream>
#include "DortyLibs/DortyBuild.h"
#include "DortyLibs/DortyMath.h"
#include "DortyLibs/DortyString.h"

void YesNo(bool num){
    if (num){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

int main()
{
    AppBuild();

    string str,str2;
    cin >> str >> str2;
    cout<< all_string_matches(str,str2);
}

*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}

bool IsPrime(long long a){
    if(a < 2){return 0;}
    if(sqrt(a) == int(sqrt(a))){return 0;}
    for(int i=2;i<sqrt(a);i++){
        if(a%i == 0){return 0;}
    }
    return 1;
}

template <typename T>
T get_first_factor(T number){
    T sqrt_ = T(sqrt(number));
    for(int i=2;i<=sqrt_;i++){
        if(number%i==0){return i;}
    }
    return number;
}


template <typename T>
vector<T> all_prime_factors(T number){
    vector<T> returner;
    for(T factor = get_first_factor(number);number>=2;factor = get_first_factor(number)){
        returner.push_back(factor);
        number /= factor;
        ///cout << number << endl;
    }

    return returner;

}

bool IsSquare(long long number){
    return (int)(sqrt( abs(number))) == sqrt( abs(number));
}

long long modular_factorial(int n,int m){
    long long ans = 1;

    for(int i =1;i<=n;i++){
        ans = (ans*i)%m;
        if (ans == 0){
            return 0;
        }
    }

    return ans;

}


int int_power(int base, int power){
    long long return_value = 1;
    for(int i =0;i<power;i++){
        return_value *= base;
    }
    return return_value;
}


template <typename T>
ostream& operator<<(ostream &in, const vector<T> &vect) {
    int n = vect.size();



    for(int i =0;i<n;i++){

        in << vect[i] << " " ;

    }

    return in;
}

template <typename T>
istream& operator>>(istream& in, vector<T> &vect) {
    int size_;
    in >> size_;

    vect.resize(size_);

    for(int i = 0;i<size_;i++){
        in >> vect[i];
    }

    return in;
}


/// return all divisors
vector<long long> all_divisers(long long number){
    number = abs(number);
    vector<long long> ans;
    int sqrt_= sqrt( number );
    for(int i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}


/// Р В Р В°РЎРѓР С”Р В»Р В°Р Т‘РЎвЂ№Р Р†Р В°Р ВµРЎвЂљ РЎвЂЎР С‘РЎРѓР В»Р С• Р Р…Р В° Р Р†РЎРѓР Вµ Р Р†Р С•Р В·Р СР С•Р В¶Р Р…РЎвЂ№Р Вµ Р ВµР С–Р С• Р С—РЎР‚Р ВµР Т‘РЎРѓРЎвЂљР В°Р Р†Р В»Р ВµР Р…Р С‘РЎРЏ Р Р† Р Р†Р С‘Р Т‘Р Вµ Р С—РЎР‚Р С•Р С‘Р В·Р Р†Р ВµР Т‘Р ВµР Р…Р С‘РЎРЏ РЎвЂЎР С‘РЎРѓР ВµР В»-1. (Р В°Р С”Р В° 12 = 3*2*2 (2 1 1), 12 = 4*3(3,2), 12 = 12(11),Р Р…Р С•, maxi Р С•РЎвЂљР Р†Р ВµРЎвЂЎР В°Р ВµРЎвЂљ Р В·Р В° Р СР В°Р С”РЎРѓР С‘Р СР В°Р В»РЎРЉР Р…РЎвЂ№Р в„– Р Т‘Р ВµР В»Р С‘РЎвЂљР ВµР В»РЎРЉ, РЎвЂљ.Р Вµ. Р ВµРЎРѓР В»Р С‘ maxi=10, РЎвЂљР С• Р СР В°РЎРѓРЎРѓР С‘Р Р† РЎРѓ РЎвЂЎР С‘РЎРѓР В»Р С•Р С  11 Р С‘Р В»Р С‘ Р В±Р С•Р В»РЎРЉРЎв‚¬Р Вµ Р Р…Р Вµ Р Р†Р ВµРЎР‚Р Р…РЎвЂРЎвЂљРЎРѓРЎРЏ)
vector<vector<long long>> All_Multes(int maxi_,int number)
{
    //cout << "call: " << number << endl;
    vector<vector<long long>> returner;
    vector<long long> ab = all_divisers(number);
    if (ab.size() == 2) {
        if (ab[1] <= maxi_){
            returner.push_back({ab[1]-1});
        }
        return returner;
    }

    for (int i = 1; i < (int)ab.size() && ab[i] <= maxi_; i++)
    {

        //cout << "abi : "<<ab[i] << endl;
        vector<vector<long long>> the_rest = All_Multes(ab[i],number/ab[i]);
        for(int j = 0;j<the_rest.size();j++){
            the_rest[j].insert(the_rest[j].begin(),ab[i]-1);
            returner.push_back(the_rest[j]);
        }

        ///returner.insert(returner.begin(), ab[i])
    }

    return returner;
}

long long prime_factor_expansion(vector<long long> powers){
    long long returner = 1;
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

    int n = powers.size();

    for(int i =0;i<n;i++){
        returner *= int_power(primes[i],powers[i]);
    }
    return returner;
}

/// First Highle Composite Number
long long FHCN(int number){
    vector<vector<long long>> mlts = All_Multes(10,number);
    long long min_ = 10000000000;
    for(int i =0;i<mlts.size();i++){
        min_ = min(min_,prime_factor_expansion(mlts[i]));
    }

    return min_;
}

#include <sstream>
template <typename T>
std::string NumberToString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}


/// РР· СЃС‚СЂРѕРєРё РіРµРЅРµСЂРёСЂСѓРµС‚ РјР°СЃСЃРёРІ, Р·РЅР°С‡РµРЅРёРµ p[i] - РѕР·РЅР°С‡Р°РµС‚ СЃРєРѕР»СЊРєРѕ СЌР»РµРјРµРЅС‚РѕРІ РґРѕ СЌС‚РѕРіРѕ (РІРєР»СЋС‡Р°СЏ РґР°РЅРЅС‹Р№) \
СЃРѕРІРїР°РґР°СЋС‚ СЃ РЅР°С‡Р°Р»РѕРј(РїСЂРµС„РёРєСЃРѕРј) СЃС‚СЂРѕРєРё ("abracadabra" -> [0 0 0 1 0 1 0 1 2 3 4])
vector<int> Pi_Func(string str){
    vector<int> p;
    p.resize(str.size());
    p[0] = 0;
    for(int i =1;i<str.size();i++){
        int pref = p[i-1];
        while (pref > 0 && str[pref] != str[i]){
            pref = p[pref - 1];
        }
        if (str[pref] == str[i]){
            p[i] = pref + 1;
        }
    }
    return p;
}

int all_string_matches(string str, string find_){
    string str_ = find_ + "@" + str;
    vector<int> p = Pi_Func(str_);

    int returner = 0;

    for(int i =0;i<str_.size();i++){
        if (p[i] == find_.size()){
            returner++;
        }
    }
    return returner;

}




void YesNo(bool num){
    if (num){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

int main()
{


    string str,str2;
    cin >> str2 >> str;
    cout<< all_string_matches(str,str2);
}


