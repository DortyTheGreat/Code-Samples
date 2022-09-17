/// https://codeforces.com/gym/374545/problem/B
#include <iostream>
#include "../../../../DortyLibs\\for_contests\\input.h"
#include "../../../../DortyLibs/STL++/vector.h"
#include "../../../../DortyLibs/STL++/pair.h"


#include "../../../../DortyLibs/DortyBuild.h"


using namespace std;

int main()
{
    vector<pair<int, int> > n;
    cin >> n;
    for(auto elem : n){
        cout << min((elem.first+elem.second)/4,min(elem.first,elem.second)) << endl;
    }
    return 0;
}
