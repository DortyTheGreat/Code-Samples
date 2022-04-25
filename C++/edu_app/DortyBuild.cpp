/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

#include <iostream>
#include "../DortyLibs/AdvancedStream.h"

#include <cmath>
using namespace std;
#include <stdio.h>
#include "../DortyLibs/BetterVector.h"
#include "../DortyLibs/Palindrome.h"

#include "../DortyLibs/DortyBuild.h"
using namespace std;

int main()
{
    AppBuild();

    vector<int> a;
    cin >> a;
    cout << max_palindrome_as_subsequence(a).size();
    return 0;
}

*/
#include <iostream>
#include <iostream>
#include <fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");


#include <cmath>
using namespace std;
#include <stdio.h>
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


/// ifdef iostream
template <typename T>
void read(vector<T> &vc, int sz){
    vc.resize(sz);
    for(int i =0;i<sz;++i){
        cin >> vc[i];
    }
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


#include <algorithm>


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



vector<long long> vector_generator(int n, int a1, int k, int b, int m){
    vector<long long> ret(n);
    ret[0] = a1;

    for(int i = 1;i<n;++i){
        ret[i] = (k*ret[i-1] + b) % m;
    }
    return ret;
}




/// Можно быстрее ... https://neerc.ifmo.ru/wiki/index.php?title=%D0%91%D1%8B%D1%81%D1%82%D1%80%D1%8B%D0%B9_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D0%B2%D0%BE%D0%B7%D1%80%D0%B0%D1%81%D1%82%D0%B0%D1%8E%D1%89%D0%B5%D0%B9_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8

/// from wiki https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA%D0%B0_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D1%83%D0%B2%D0%B5%D0%BB%D0%B8%D1%87%D0%B8%D0%B2%D0%B0%D1%8E%D1%89%D0%B5%D0%B9%D1%81%D1%8F_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8
template <typename T>
vector<T> NVP(vector<T> A){

    int N = A.size();

    /*
    int n = A.size();

    vector<int> d;
    d.resize(n+1);
    d[0] = -100000;
    for (int i=1; i<=n; ++i)
        d[i] = 1000000;

    for (int i=0; i<n; i++) {
        int j = int (upper_bound (d.begin(), d.end(), A[i]) - d.begin());
        if (d[j-1] < A[i] && A[i] < d[j])
            d[j] = A[i];
    }

    return d;
    */


    vector<T> P(N);
    vector<T> M(N + 1);
    int L = 0;
    for (int i=0; i< N;i++){
      int lo = 1;
      int hi = L;
      while (lo <= hi){
        int mid = ((lo+hi + 1)/2);
        if (A[M[mid]] < A[i]){
          lo = mid+1;
        }else{
          hi = mid-1;
        }
      }
      int newL = lo;
      P[i] = M[newL-1];
      M[newL] = i;
      if (newL > L){
        L = newL;
      }
    }
    vector<T> S(L);
    int k = M[L];
    for (int i= L-1;i>-1;i--){
      S[i] = A[k];
      k = P[k];
    }
    return S;

}





/// Подряд идущие палиндромы
template <typename T>
vector<T> max_palindrome(const vector<T>& s){
    vector<char> s2(s.size() * 2 + 1, '#');
    //создаем псевдостроку с границами в виде символа '#'
    for(int i = 0; i != (int)(s.size()); ++i){
        s2[i*2 + 1] = s[i];
    }

    int p[s2.size()];
    int r, c, index, i_mir;
    int maxLen = 1;
    i_mir = index = r = c = 0;

    for(int i = 1; i != (int)(s2.size()) - 1; ++i){
        i_mir = 2*c-i;

        //Если мы попадаем в пределы радиуса прошлого результата,
        //то начальное значение текущего радиуса можно взять из зеркального результата
        p[i] = r > i ? min(p[i_mir], r-i) : 0;

        while(i > p[i] && (i + p[i] + 1) < (int)(s2.size()) && s2[i - p[i] - 1] == s2[i + p[i] + 1])
            ++p[i];

        if(p[i] + i > r){
            c = i;
            r = i + p[i];
        }

        if(maxLen < p[i]){
            maxLen = p[i];
            index = i;
        }
    }
    vector<T> ret;

    for(int i = (index-maxLen)/2; i < (index-maxLen)/2 + maxLen; ++i){
        ret.push_back(s[i]);
    }

    //Отображаем найденные позиции на оригинальную строку
    return ret;
}



/** Максимальный палиндром, такой, что его можно получить вычёркиванием символов из оригинальной строки

O(n^2), n - длина массива.
Алгоритм вкратце: Найти НОП от оригинальной строки и обратной к оригинальной

ref : https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2051/5062.htm

*/
template <typename T>
vector<T> max_palindrome_as_subsequence(const vector<T>& s){
    vector<T> r = s;
    reverse(r.begin(),r.end());
    return NOP(r,s);
}


using namespace std;

int main()
{
     

    vector<int> a;
    cin >> a;
    cout << max_palindrome_as_subsequence(a).size();
    return 0;
}

