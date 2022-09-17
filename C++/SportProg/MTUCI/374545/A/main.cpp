/// https://codeforces.com/gym/374545/problem/A
#include <iostream>
#include "../../../../DortyLibs/STL++/vector.h"
#include "../../../../DortyLibs/STL++/pair.h"
#include "../../../../DortyLibs/sort/Sorted_Vector.h"
#include "../../../../DortyLibs/for_contests/input.h"
#include "../../../../DortyLibs/DortyBuild.h"


using namespace std;

int main()
{
    vector<int> n,m;
    cin >> n >> m;
    Sorted_Vector<int> sv(n);
    for(auto elem : m){
        cout << sv.count_elems_lower(elem+1) << endl;
    }
    return 0;
}
