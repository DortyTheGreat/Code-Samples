/// https://informatics.msk.ru/mod/statements/view.php?chapterid=623#1

#include <algorithm>
#include <cstdio>
#include <iostream>
#include "../../../DortyLibs/DortyBuild.h"
#include "../../../DortyLibs/prime/factor.h"


using namespace std;

int main()
{

    AppBuild();
    unsigned int n;
    cin >> n;

    auto v = prime_factor(n);
    sort(v.begin(),v.end());
    cout << v[0];
    for(int i = 1;i < v.size();++i){
        cout <<'*' <<v[i];
    }
    return 0;
}
