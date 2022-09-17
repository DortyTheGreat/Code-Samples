/// https://codeforces.com/gym/374545/problem/C
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
