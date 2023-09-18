#include <iostream>

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

using namespace std;

int main()
{

    for(int i = 1; i < 1000; ++i){
        auto vc = all_divisers(i);

        int summ = 0;
        double val = 0;
        for(const auto& it : vc){
            summ += it;
            val += 1.0 / it;
        }

        val = vc.size() / val;

        if (summ % vc.size() == 0 && abs(round(val) - val) < 0.001 ){
            cout << i << " " <<summ / vc.size() << " " << round(val) << endl;
        }
    }

    cout << "Hello world!" << endl;
    return 0;
}
