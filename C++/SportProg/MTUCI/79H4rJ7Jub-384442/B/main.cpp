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
