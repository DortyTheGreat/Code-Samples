#include <iostream>
#include <vector>

using namespace std;

/*
vector<string> split(string s, const string& delimiter=" "){
    vector<string> ret;

    std::string token;
    for (size_t pos = 0;(pos = s.find(delimiter)) != std::string::npos;s.erase(0, pos + delimiter.length())) {
        ret.push_back(s.substr(0, pos));

    }
    ret.push_back(s);
    return ret;
}
*/

#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> split (const std::string &s, char delim=' ') {
    std::vector<std::string> result;
    std::string item = "";

    for(int i = 0; i < s.size();++i){
        if (s[i] == delim){
            result.push_back(item);
            item = "";
        }else{
            item += s[i];
        }
    }
    result.push_back(item);
    return result;
}

#include <unordered_set>
#include <set>


vector<int16_t> to_vc(const string& s){
    vector<int16_t> ret;
    for(int i =0; i < s.size() - 1; ++i){
        int16_t d = s[i+1] - s[i];
        if (d < 0) d += 26;
        ret.push_back(d);
    }
    return ret;
}

#include <map>
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    string sss;
    getline(cin,sss);
    auto vc = split(sss);
    map<vector<int16_t>, string> st;
    //st.reserve(1000 * 1000 * 10);
    //st.max_load_factor(0.25);

    for( const auto& s : vc){
        st[to_vc(s)] = s;
    }


    int n;
    cin >> n;

    for(int i =0;i < n; ++i){
        string sgt;
        cin >> sgt;


        cout << st[to_vc(sgt)];





    }

    return 0;
}
