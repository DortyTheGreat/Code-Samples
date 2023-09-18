#include <iostream>
#include <vector>
#include <iostream>
#include <string_view>
#include <string>
using namespace std;

struct templ{
    string start_number;
    int x_ses;
    string name;
    string original_number;
};

int main()
{
    vector<string> numbers;
    int n;
    cin >> n;
    for(int i = 0; i < n + 1;++i){
        string s;
        getline(cin,s);
        if (s == "") continue;

        string clear_s = "";

        for(int i = 0; i < s.size();++i){
            if (s[i] >= '0' && s[i] <= '9')
                clear_s += s[i];
        }
        //cout << clear_s << endl;
        numbers.push_back(clear_s);
    }

    int m;
    cin >> m;


    vector<templ > templates;
    for(int i = 0; i < m + 1;++i){
        string s;
        getline(cin,s);
        if (s == "") continue;

        string name = s.substr(s.find('-'));
        string num = s.substr(0,s.find('-'));

        string new_num = "";
        int x_ses = 0;
        for(int i = 0; i < num.size(); ++i){
            if (num[i] >= '0' && num[i] <= '9')
                new_num += num[i];
            if (num[i] == 'X')
                x_ses++;
        }
        templates.push_back({new_num,x_ses,name,num});
        //cout << name << " " << num << endl;
    }

    for(int i = 0; i < numbers.size(); ++i){
        for(int j = 0; j < templates.size(); ++j){
            if ( (numbers[i].rfind(templates[j].start_number, 0) == 0 ) && (numbers[i].size() == templates[j].start_number.size() + templates[j].x_ses) ){

                string gen_num = templates[j].original_number;
                int c = templates[j].start_number.size();
                for(int k = 0; k < gen_num.size(); ++k){
                    if (gen_num[k] == 'X'){
                        gen_num[k] = numbers[i][c++];
                    }
                }

                cout << gen_num << templates[j].name << '\n';

            }
        }
    }

    return 0;
}
