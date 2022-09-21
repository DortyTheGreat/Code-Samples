#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    string str;
    fin >> str;

    int ans = -1;
    int cou = 1;

    for(int i =0;i<str.size();i++){
        if (str[i] > str[i-1]){
            cou++;
        }else{
            ans = max(cou,ans);
            cou = 1;
        }
    }

    cout << ans << endl;
    return 0;
}
