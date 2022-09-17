/// https://codeforces.com/gym/374545/problem/C
#include <iostream>
#include "../../../../DortyLibs/for_contests/YesNo.h"
#include "../../../../DortyLibs/STL++/vector.h"
#include "../../../../DortyLibs/STL++/pair.h"


#include "../../../../DortyLibs/DortyBuild.h"
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        vector<long long > n;
        cin >> n;
        std::sort(n.begin(), n.end());
        long long low_summ= 0, high_summ = 0;

        for(int i =0;i< (n.size()+1)/2;++i)
            low_summ += n[i];

        for(int i =n.size() - 1;i> n.size() - (n.size()+1)/2 ;--i)
            high_summ += n[i];

        YesNo(low_summ < high_summ);
    }
    return 0;

}
