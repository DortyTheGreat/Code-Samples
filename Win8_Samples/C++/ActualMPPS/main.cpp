#include <iostream>
#include <fstream>

using namespace std;

string Variables[100]; int vars = 0;



string Separators = " ,;.()[]{}<>#+-=%*\\/\"\';?!\|&^:";
string AbbandonedWords[100]; int AmountOfAbbandonedWords;



void initDictionary(){

    ifstream fin("Dictionary.txt");


    string Carret;
    int cou = 0;

    for(int i =0;i<100;i++){
        AbbandonedWords[i] = "int";
    }


    while(!fin.eof()){
        getline(fin,Carret);
        if (Carret.size() != 0){
            if (Carret[0] != '='){
                AbbandonedWords[cou] = Carret;cou++;
                cout << "Dict: " << Carret << endl;
            }else{
                cout << "Comment: " << Carret << endl;
            }
        }

    }





    AmountOfAbbandonedWords = 100;
}


bool isWordLegal(string word){

    for(int i =0;i<AmountOfAbbandonedWords;i++){
        if (AbbandonedWords[i] == word){
            return 0;
        }
    }
    return 1;

}


bool CharIsSeparator(char CHARR){
    for(int i =0;i<Separators.size();i++){
        if (Separators[i] == CHARR){
            return 1;
        }
    }
    return 0;
}

void FindVars(string LineOfCode){
string Word="";

for(int i = 0 ;i<LineOfCode.size();i++){
    if (CharIsSeparator(LineOfCode[i]) ){
        /// Сепаратор

        if (Word.size() != 0){
            ///cout << "Word: " <<Word;
            if (isWordLegal(Word)){cout << " = Var: " << Word;}
            cout << endl;
        }

        Word = "";
    }else{
    Word+= LineOfCode[i];
    }
}

}

int main()
{

    initDictionary();

    ifstream fin("code.txt");


    int ab12;

    cout << Separators << endl;

    string Carret;

    while(!fin.eof()){
        getline(fin,Carret);
        ///cout << Carret << endl;
        FindVars(Carret);
    }

    cout << "finito";

}
