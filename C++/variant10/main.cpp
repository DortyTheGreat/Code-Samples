#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int ans = -1;

void update(string str){
    int a = str.size();
    ans = max(ans,a);
}


int main()
{
    map<char,int> mp;

    ifstream fin("input.txt");
    string str;
    cin >> str;

    string Carret = "";


    for(int i = 0;i<str.size();i++){
        if (str[i] == '.'){
            update(Carret);
            Carret = "";


        }else{
            if (str[i] == 'A' || str[i] == 'E'|| str[i] == 'I'|| str[i] == 'O'|| str[i] == 'U'|| str[i] == 'Y'){
                Carret += "G";

                int num = count(Carret.begin(),)

            }else{
                Carret += "S";
            }

        }
    }

    update(Carret);

    cout << ans << endl;

    ///cout << "Hello world!" << endl;
    return 0;
}
