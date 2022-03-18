#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

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

/// MATH

/// VECTOR

template <typename T>
void print(vector<T> vector_){
    int n = vector_.size();
    for(int i =0;i<n;i++){
        cout << vector_[i] << " ";
    }
    cout << endl;
}

/// Вызывать request(1) - int, request(true) - bool, request("123") - string, request("")
template <typename T>
vector<T> request_vector(T dummy){
    vector<T> returner;
    int n;
    cin >> n;
    for(int i =0;i<n;i++){
        T temp;
        cin >> temp;
        returner.push_back(temp);
    }
    return returner;
}

/// Вызывать request(1) - int, request(true) - bool, request("123") - string, request("")
template <typename T>
vector<T> form_vector(int size_,T dummy, const function<int(int)> &fn){
    vector<T> returner;

    for(int i =0;i<size_;i++){
        returner.push_back(fn(i));
    }

    return returner;
}

template <typename T>
T input(T dummy){
    T returner;
    cin >> returner;
    return returner;
}

template <typename T>
T summ_(vector<T> vector_){
    T return_value = 0;
    for(int i =0;i<vector_.size();i++){
        return_value += vector_[i];
    }
    return return_value;
}



template <typename T>
void request(vector<T> &vector_){

    int n;
    cin >> n;
    for(int i =0;i<n;i++){
        T temp;
        cin >> temp;
        vector_.push_back(temp);
    }

}

template <typename T>
vector<T> NOP(vector<T> A, vector<T> B){

     int n = A.size();
     int m = B.size();

    vector<vector<T> > F(n + 1, vector<T>(m + 1));

     for (int i =1;i<=n;i++){
        for (int j =1;j<=m;j++){
            if (A[i-1] == B[j-1]){
                F[i][j] = F[i - 1][j - 1] + 1;
            }else{
                F[i][j] = max(F[i - 1][j], F[i][j - 1]);
            }
        }
     }


     vector<T> Ans;
     int i = n;
     int j = m;
     while (i > 0 && j > 0){
        if (A[i - 1] == B[j - 1]){
            Ans.push_back(A[i - 1]);
            i -= 1;
            j -= 1;
        }else{
        if (F[i - 1][j] == F[i][j]){
            i--;

        }else{
            j--;
        }
        }
     }
     reverse(Ans.begin(),Ans.end());

    return Ans;
}




template <typename T>
vector<T> NVP(vector<T> A){

    int m = A.size();
    /// orriginal -> A

    vector<T> pointers(m);

    int tempt=0;
    int maxi=-1, index=0;
    for(int i=m-1;i>-1;i--){
    tempt=0;
    for(int j=i;j<m;j++){
         if(pointers[j] > tempt && A[i] < A[j] ){
            tempt=pointers[j];
         }
    }
    tempt++;
    pointers[i]= tempt;
    if(maxi < tempt){maxi=tempt;index= i;}
    }



    vector<T> Ans;

    for(int i=index;i<m;i++){
        if(pointers[i] == maxi){
            Ans.push_back(A[i]);maxi-=1;
        }
    }

    return Ans;

}

vector<long long> all_divisers(long long number){
    vector<long long> ans;

    number=abs(number);
    for(int i=1;i<=sqrt( abs(number) );i++){
        if(number%i==0){ans.push_back(i);}
    }

    int counter = ans.size() - IsSquare(number);
    int requr = number/ans[--counter];

    while(counter != (-1)){
        ans.push_back(requr);
        requr = number/ans[--counter];
    }

    return ans;

}



signed main()
{
    cout << summ_(form_vector(input(1)+1,1,[](int i){return int_power(2,i);}));
    return 0;
}
