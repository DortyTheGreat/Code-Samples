#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("input.txt");

    string str;
    fin >> str;
    cout << str.size() << endl;
    string Carret = "ASAEESSECC";
    int ans = -1;


    size_t n = count(Carret.begin(),Carret.end(),'E');

    cout << n << endl;

    Carret = "";


    for(int i =0;i<str.size();i++){
        if (str[i] == 'A'){

            size_t n = count(Carret.begin(),Carret.end(),'E');
            if (n >= 3){
                int num = Carret.size();
                ans = max(ans,num);
            }
            Carret = "";
        }else{
            Carret += str[i];
        }
    }

    cout << ans << endl;
    return 0;
}
