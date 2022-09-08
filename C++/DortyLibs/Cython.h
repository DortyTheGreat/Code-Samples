#include <vector>

void YesNo(bool arg){
    if (arg){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

string input(){
    string returner;
    cin >> returner;
    return returner;
}

template <typename T>
T input(T ab){
    T returner;
    cin >> returner;
    return returner;
}

template<typename T>
T input(){
    T x;
    std::cin >> x;
    return x;
}

long long to_int(string str){
    long long mask = 1;
    size_t start_index = 0;
    long long returner = 0;
    if (str[0] == '-'){
        mask = -1;
        start_index = 1;
    }

    for(size_t i =start_index;i<str.size();i++){
        returner *= 10;
        returner += (str[i] - '0');
    }
    return returner * mask;
}

long long intput(){
    return to_int(input());
}

template <typename T, typename F>
void print(T a, F b){
    cout << a << " " << b << endl;
}

template <typename T>
T max(const vector<T> &vect){
    if (vect.size() < 1){
        return -1;
    }
    T max_ = vect[0];
    for (auto i : vect){
        max_ = max(max_,i);
    }
    return max_;
}

template <typename T>
T indexOf(const vector<T> &vect, T element){
    size_t size_ = vect.size();
    for (int i =0;i<size_;++i){
        if (vect[i] == element){
            return i;
        }
    }
    return -1;
}

template <typename T>
vector<T> slice(const vector<T> &vect, size_t elements){

    vector<T> returner;

    size_t size_ = min(vect.size(),elements);

    for (int i =0;i<size_;++i){
        returner.push_back(vect[i]);
    }
    return returner;
}

void print(string data){
    cout << data << endl;
}


