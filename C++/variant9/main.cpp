#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

int main()
{


    ifstream fin("input.txt");
    string str;
    int index = -1;
    int maxi_ = -1;
    int cri =0;
    string bubliki[1000];
    while (fin >> str){
        int n =count(str.begin(),str.end(),'Q');
        if (n >= maxi_){
            maxi_ = n;
            index = cri;
        }
        bubliki[cri] = str;
        cri++;
    }

    map<char,int> mp;

    for(int i =0;i<bubliki[index].size();i++){
        mp[bubliki[index][i]]++;
    }

    for(auto i : mp){
        cout << i.first << " " << i.second << endl;
    }

    /// C нашли
    int ans = 0;

    for(int i =0;i<cri;i++){
        for(int j =0;j<bubliki[i].size();j++){
            if (bubliki[i][j] == 'C'){
                ans++;
            }
        }
    }

    cout << " C "  << ans;

    ///cout << "Hello world!" << endl;
    return 0;
}
