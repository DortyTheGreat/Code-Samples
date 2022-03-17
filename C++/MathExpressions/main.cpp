#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

/// –егул€рное выражение (aka число, aka переменна€, aka что-то)
class Expression{
public:
    Expression *left, *right;

    Expression(){}

    Expression(Expression &left_){
        left = left_;
        right = new Expression();
    }
};

class addition{
public:
    Expression left,right;
};

int main()
{
    Expression a;
    string parsing;
    getline(cin,parsing);
    parsing += " ";
    vector<string> lexems;

    string seps = "+-*/()";


    string Carret = "";

    for(int i = 0;i<parsing.size();i++){
        if (parsing[i] == ' ' || (seps.find(parsing[i]) != -1)){

            if (!Carret.empty()){
                lexems.push_back(Carret);
                Carret = "";
            }
            if (parsing[i] != ' '){
                lexems.push_back( string(1,parsing[i]));
            }


        }else{
            Carret += parsing[i];
        }
    }



    for(int i = 0;i< lexems.size();i++){
        cout <<"" << lexems[i] <<""<< endl;
    }
    ///cout << "Hello world!" << endl;
    return 0;
}
