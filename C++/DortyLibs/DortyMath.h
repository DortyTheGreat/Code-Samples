#include <cmath>
#include <vector>

using namespace std;

# if defined(NOD)
/// already definded, pass
#else
long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}
# endif // NOD



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


/// Раскладывает число на все возможные его представления в виде произведения чисел-1. (ака 12 = 3*2*2 (2 1 1), 12 = 4*3(3,2), 12 = 12(11),но, maxi отвечает за максимальный делитель, т.е. если maxi=10, то массив с числом  11 или больше не вернётся)
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
