/*
---------------------
This File was Build Automatically by DortyBuild v 1.4.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

/// https://codeforces.com/gym/374545/problem/B
#include <iostream>
#include "../../../../DortyLibs/for_contests/YesNo.h"
#include "../../../../DortyLibs/STL++/vector.h"
#include "../../../../DortyLibs/STL++/pair.h"


#include "../../../../DortyLibs/DortyBuild.h"


using namespace std;

int main()
{
    vector<int > n;
    cin >> n;
    for(auto elem : n){
        YesNo(elem % 4 == 0);
    }
    return 0;
}

*/
/// https://codeforces.com/gym/374545/problem/B
#include <iostream>
#include <vector>

void YesNo(bool arg){
    if (arg){
        std::cout << "YES" << std::endl;
    }else{
        std::cout << "NO" << std::endl;
    }
}

#include <vector>

#ifdef _GLIBCXX_IOSTREAM
template <typename T>
std::ostream& operator<<(std::ostream &in, const std::vector<T> &vect) {
    int n = vect.size();



    for(int i =0;i<n;i++){

        in << vect[i] << " " ;

    }

    return in;
}

template <typename T>
std::istream& operator>>(std::istream& in, std::vector<T> &vect) {
    int size_;
    in >> size_;

    vect.resize(size_);

    for(int i = 0;i<size_;i++){
        in >> vect[i];
    }

    return in;
}

/// ifdef iostream
template <typename T>
void read(std::vector<T> &vc, int sz){
    vc.resize(sz);
    for(int i =0;i<sz;++i){
        std::cin >> vc[i];
    }
}
#endif

template <typename T>
void operator += (std::vector<T> &vect,T number) {
    vect.push_back(number);
}

template <typename T>
std::vector<T> get_all_sub_strings(T &vect){

    std::vector<T> ret;

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
T sum(std::vector<T> &vect){
    T ret = 0;
    int sz = vect.size();
    for(int l = 0;l<sz;l++){
        ret += vect[l];
    }
    return ret;
}

template <typename T>
T min(std::vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = std::min(ret,vect[i]);
    }
    return ret;
}

template <typename T>
T max(std::vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = std::max(ret,vect[i]);
    }
    return ret;
}

#ifdef _GLIBCXX_STRING
template <typename T>
std::vector<T> list(std::basic_string<T> str){
    std::vector<T> ret;
    ret.resize(str.size());
    for(size_t i = 0;i<str.size();i++){
        ret[i] = str[i];
    }
    return ret;
}
#endif // _GLIBCXX_STRING
template <typename T>
inline T first(std::vector<T> &vect){
    return vect[0];
}

template <typename T>
inline T last(std::vector<T> &vect){
    return vect[vect.size() - 1];
}


#include <utility>

#ifdef _GLIBCXX_IOSTREAM
template <typename T, typename F>
std::ostream& operator<<(std::ostream &in, const std::pair<T,F> &p) {
    return (in << p.first <<' ' << p.second);
}

template <typename T, typename F>
std::istream& operator>>(std::istream& in, std::pair<T,F> &p) {
    return (in >> p.first >> p.second);
}

#endif



#include <fstream>


using namespace std;

int main()
{
    vector<int > n;
    cin >> n;
    for(auto elem : n){
        YesNo(elem % 4 == 0);
    }
    return 0;
}

