
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>


using namespace std;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

bool IsPrime(long long a){
    if(a < 2){return 0;}
    if(sqrt(a) == int(sqrt(a))){return 0;}
    for(int i=2;i<sqrt(a);i++){
        if(a%i == 0){return 0;}
    }
    return 1;
}

bool isCool(long long a){
    if (a == 0){return 0;}
    if (a == 1){return 0;}
    return !IsPrime(a);
}

void check(string str){
    if (isCool(atoi(str.c_str()))){
        cout << str;
        exit(0);
    }
}

string randNum(){
    return NumberToString(rand() % 10);
}

string rpl(string a){

    while(1){
        if (a.find("*") != -1){
            a.replace(a.find("*"),1,randNum());
        }else{
            break;
        }
    }

    return a;

}

int main()
{
    string abc;
    cin >> abc;
    //srand(time(NULL));
    ///cout << NumberToString(0) << endl;

    for(int i = 0;i<10000;i++){
        check(rpl(abc));
    }


    cout << -1;

    return 0;
}
