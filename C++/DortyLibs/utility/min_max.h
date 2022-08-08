

//int min_() { return 0; }


/**

Это быстро, но происходят проблемы с типами данных, так что не стал выбирать данный вариант

template<typename T, typename... Args>
T min_(T a, Args... args) {T res = min_(args...); return (a < res) ? a : res; }
*/
namespace DortyLibs{

    template<typename T>
    T multiple_arguements_min(const T& a){return a;}

    template<typename T, typename... Args>
    T multiple_arguements_min(const T& a, const Args&... args) {return (a < multiple_arguements_min(args...)) ? a : multiple_arguements_min(args...); }

}



template<typename T, typename... Args>
T min(const T& a, const Args&... args) {return DortyLibs::multiple_arguements_min(a,args...); }

template<typename T, typename K>
T min(const T& a, const K& b) {return (a < b) ? a : b; }
