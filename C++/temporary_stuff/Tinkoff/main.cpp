#include <iostream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{

    string name;
    getline(cin,name);
    getline(cin,name);
    string pattern;
    cin >> pattern;
    ///cout <<"b" <<name << "b" << endl;
    int ans = 0;
    bool nice = 1; /// по умолчанию - красивое
    int j = 0;
    char prev_color = 'N'; /// нейтральный цвет
    for(int i = 0;i < name.size();++i){
        if (name[i] == ' '){
            /// пробел -> новое слово
            ans += !nice;
            nice = 1;
            prev_color = 'N';
        }else{
            if (prev_color == pattern[j]){
                nice = 0;/// цвета повторяются
            }
            prev_color = pattern[j];
            ++j;
        }

    }

    ans += !nice; /// exceptcion (типо)

    cout << ans << endl;
    return 0;
}
