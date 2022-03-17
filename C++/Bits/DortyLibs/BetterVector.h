#include <vector>


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

template <typename T>
void operator += (vector<T> &vect,T number) {
    vect.push_back(number);
}

template <typename T>
vector<T> get_all_sub_strings(T &vect){

    vector<T> ret;

    int sz = vect.size();

    for(int l = 0;l<sz;l++){
        for(int r = l+1;r<sz+1;r++){
            T obj;
            for(int cou = l;cou < r;cou ++){
                obj += vect[cou];
            }
            ret.push_back(obj);

        }
    }

    return ret;
}

template <typename T>
T sum(vector<T> &vect){
    T ret = 0;
    int sz = vect.size();
    for(int l = 0;l<sz;l++){
        ret += vect[l];
    }
    return ret;
}

template <typename T>
T min(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = min(ret,vect[i]);
    }
    return ret;
}

template <typename T>
T max(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = max(ret,vect[i]);
    }
    return ret;
}

template <typename T>
vector<T> list(basic_string<T> str){
    vector<T> ret;
    ret.resize(str.size());
    for(size_t i = 0;i<str.size();i++){
        ret[i] = str[i];
    }
    return ret;
}

template <typename T>
inline T first(vector<T> &vect){
    return vect[0];
}

template <typename T>
inline T last(vector<T> &vect){
    return vect[vect.size() - 1];
}

