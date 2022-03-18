#include <iostream>

using namespace std;
int to_int(char ch){
    if (islower(ch)){
        return 10 + (ch - 'a');
    }

    if (isupper(ch)){
        return 10 + 26 + (ch - 'A');
    }
}

bool test(string str){

int size_ = str.size();

for(int i =0;i<size_;i++){
    if (to_int(str[i]) <= (size_ - i)){
        return false;
    }
}

return true;
}

int main()
{
    int n;
    cin >> n;

    for(int i =0;i<n;i++){
        string temp;
        cin >> temp;
        if (test(temp)){
            cout << i + 1 << endl;
        }
    }

    //cout << to_int('Z') << endl;
    return 0;
}
