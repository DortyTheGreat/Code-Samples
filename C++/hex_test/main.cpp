#include <iostream>

using namespace std;

static const std::string base64_chars = \
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
             abcdefghijklmnopqrstuvwxyz\
             0123456789+\";
vector<string> bubliki;

void proper(string str){
    int sz = str.size();
    for(int i = 0;i<sz;i++){
        cout << base64_chars.find(str[i]) << endl;
    }
}

int main()
{
    string str;
    cin >> str;

    cout << "Hello world!" << endl;
    return 0;
}
