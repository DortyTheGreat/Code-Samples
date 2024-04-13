#include <iostream>

using namespace std;

int main()
{
    string a;
    cin >> a;
    //getline(cin,a);
    string upr;
    cin >> upr;
    //getline(cin,upr);

    string cur = "";
    int mode = 0;
    int carr = 0;
    string log_str = "";
    for(int i = 0; i < upr.size(); ++i){
        if (mode == 0){
            char c = upr[i];
            if (c == '<'){
                mode = 1;
                continue;
            }
            cur = cur.substr(0, carr) + c + cur.substr(carr);
            carr++;
        }

        if (mode == 1){
            if (upr[i] != '>'){
                log_str += upr[i];
                continue;
            }

            if (log_str == "bspace"){
                cur = cur.substr(0, max(carr-1,0)) + cur.substr(carr);
                carr = max(carr-1,0);
            }

            if (log_str == "delete"){
                cur = cur.substr(0, carr) + cur.substr(min(carr+1,int(cur.size()) ));
            }

            if (log_str == "left"){
                carr = max(carr-1,0);
            }

            if (log_str == "right"){
                carr = min(carr+1,int(cur.size()) );
            }

            log_str = "";
            mode = 0;

        }


    }

    if (cur == a){
        cout << "Yes";
    }else{
        cout << "No";
    }

    ///cout << endl << cur;

    return 0;
}
