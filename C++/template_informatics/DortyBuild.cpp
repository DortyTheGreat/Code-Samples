/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

#include <iostream>
#include "../DortyLibs/DortyBuild.h"
#include "../DortyLibs/utility/min_max.h"
using namespace std;

int main()
{
    AppBuild();
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << min(a,b,c,d);
    return 0;
}

*/
#include <iostream>


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

using namespace std;

int main()
{
     
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << min(a,b,c,d);
    return 0;
}

