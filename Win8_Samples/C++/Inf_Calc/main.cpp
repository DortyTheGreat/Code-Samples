#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

int main()
{
    //setlocale(LC_ALL, "Russian");

    //system("chcp 1251");
    string ALPH_INPUT;
    char ALPH_ACTUAL[100]; int h=0;
    cout << "Insert the Alphabet symbols(rus. lang) (with or without the spaces)" << endl << ">>> ";
    getline(cin,ALPH_INPUT);
    for(int i=0;i<ALPH_INPUT.size();i++){
        if(ALPH_INPUT[i] != ' '){
            int _true=1;
            for(int j=0;j<h;j++){
                if(ALPH_ACTUAL[j] == ALPH_INPUT[i]){_true=0;}

            }
            if(_true){ALPH_ACTUAL[h]=ALPH_INPUT[i];h++;}

        }
    }

    for(int i=0;i<h;i++){
        cout << ALPH_ACTUAL[i] << " ";
    }
    int _size=5;
    int cou=0;
    int answer=0;
    while(1){
            string _this="";
        for(int i=0;i<_size;i++){
            _this+=ALPH_ACTUAL[((int)(cou / pow(h,i)  )) % h];
        }
        cout << _this << endl;
        bool config=1;
        if(config){answer++;}

    cou++;
    if(cou == (int)(pow(h,_size)) ){break;}
    }
    cout << answer;
}
