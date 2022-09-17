/*
---------------------
This File was Build Automatically by DortyBuild v 1.4.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

/// https://codeforces.com/group/79H4rJ7Jub/contest/384442/problem/A
/// http://codeforces.com/contestInvitation/e1180f0bb5d1bfed72d2801e3764ae9614abb71e

#include <iostream>
#include "../../../../DortyLibs/STL++/vector.h"
#include "../../../../DortyLibs/STL++/pair.h"
#include "../../../../DortyLibs/string/splits.h"
#include "../../../../DortyLibs/for_contests/input.h"
#include "../../../../DortyLibs/DortyBuild.h"

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        string a;
        cin >> a;
        a = 'R' + a + 'R';
        int maxi = 0;
        for(auto clump : split_by_repeting_symbols(a)){
            if (clump[0] == 'L')
                maxi = max(maxi,int(clump.size()));
        }
        cout << maxi+1 << endl;
    }

    return 0;
}

*/
/// https://codeforces.com/group/79H4rJ7Jub/contest/384442/problem/A
/// http://codeforces.com/contestInvitation/e1180f0bb5d1bfed72d2801e3764ae9614abb71e

#include <iostream>
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

/**
ex:
"abbbbaaaaccdddee" ->
["a","bbbb", "aaaa", "cc", "ddd", "ee"]
*/

#include <vector>


std::vector<std::string> split_by_repeting_symbols(const std::string& a){

    std::vector<std::string> ret;
    if (a.empty()) return ret;
    ret.push_back(std::string(1,a[0]));

    for(int i = 1;i< a.size();++i){
        if (a[i] != ret.back().back() ){
            ret.push_back(std::string(1,a[i]));
        }else{
            ret.back() += a[i];
        }
    }
    return ret;


}

#include <iostream>

template<typename T>
T input(){
    T x;
    std::cin >> x;
    return x;
}

#include <fstream>

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        string a;
        cin >> a;
        a = 'R' + a + 'R';
        int maxi = 0;
        for(auto clump : split_by_repeting_symbols(a)){
            if (clump[0] == 'L')
                maxi = max(maxi,int(clump.size()));
        }
        cout << maxi+1 << endl;
    }

    return 0;
}

