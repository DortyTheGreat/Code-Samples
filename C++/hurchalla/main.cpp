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
