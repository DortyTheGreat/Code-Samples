/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

#include <iostream>
#include "../DortyLibs/string/Levenshtein_distance.h"
#include "../DortyLibs/DortyBuild.h"
using namespace std;

int main()
{
    AppBuild();
    string a,b;
    getline(cin,a);
    getline(cin,b);
    cout << LevenshteinDistance(a,b) << endl;
    ///cout << "Hello world!" << endl;
    return 0;
}

*/
#include <iostream>
int LevenshteinDistance(const std::string& s, const std::string& t){


    const int n = s.size() + 1;
    const int m = t.size() + 1;
    int d[n][m];

    for(int i = 0;i < n;++i){
        for(int j = 0;j < m;++j){
            d[i][j] = 0;
        }
    }


    for(int i = 0;i < n;++i){
        d[i][0] = i;
    }


    for(int i = 0;i < m;++i){
        d[0][i] = i;
    }

    for(int i = 1;i < n;++i){
        for(int j = 1;j < m;++j){
            d[i][j] = std::min(d[i-1][j],d[i][j-1]) + 1;
            d[i][j] = std::min(d[i][j], d[i-1][j-1] + ((s[i-1] == t[j-1])? 0 : 1) );
        }
    }


    return d[n - 1][m - 1];
}

using namespace std;

int main()
{
     
    string a,b;
    getline(cin,a);
    getline(cin,b);
    cout << LevenshteinDistance(a,b) << endl;
    ///cout << "Hello world!" << endl;
    return 0;
}

