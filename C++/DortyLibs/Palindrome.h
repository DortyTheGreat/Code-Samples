#include "algo.h"

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
