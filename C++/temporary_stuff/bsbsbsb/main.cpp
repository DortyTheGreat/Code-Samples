#include<iostream>

using namespace std;

int main(){
    string n;
    int j = 1;
    cin >> n;
    if (n[n.size()-1] - '0' + 1 == 10) {

        for(int i = n.size(); i >=0; i--){
            if (n[n.size()-1] - '0' + j == 10){

            }
        }
    }
    else{
        n[n.size()-1] = n[n.size()-1] - '0' + 1 + '0';
        cout<<n;
    }

}
