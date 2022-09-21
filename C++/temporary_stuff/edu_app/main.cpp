#include <iostream>
#include "../DortyLibs/AdvancedStream.h"

#include <cmath>
using namespace std;
#include <stdio.h>
#include "../DortyLibs/BetterVector.h"
#include "../DortyLibs/Palindrome.h"

#include "../DortyLibs/DortyBuild.h"
using namespace std;

int main()
{
    AppBuild();

    vector<int> a;
    cin >> a;
    cout << max_palindrome_as_subsequence(a).size();
    return 0;
}
