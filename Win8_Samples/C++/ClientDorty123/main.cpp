#include <iostream>

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <ctype.h>
using namespace std;

int main()
{
    // (Project > Build Options > Other Compile Options) compile options "-finput-charset=CP1251 -fexec-charset=CP866"

    //_setmode(_fileno(stdout), _O_U16TEXT);
    //_setmode(_fileno(stdin),  _O_U16TEXT);
    //_setmode(_fileno(stderr), _O_U16TEXT);

    //setlocale(LC_ALL,"");

    cout << "123123";;

    wstring RelieseTextRus = L"Добро пожаловать в DUC. v3.1.C++  Сделано 05.04.2021 в рамках проекта \"HeDog\" ";
    wstring AboutTextRus = L"";

    wcout << RelieseTextRus;

    wcout << endl << AboutTextRus;
    wcout << endl;
    wstring Karret = L"";
    while(1){
        wchar_t Bukva;
        //wcout << L"Create Request: ";
        Bukva = _getwch();
        //wcout << Bukva << " " << int(Bukva) << endl; // Enter - 13
        switch( (int)Bukva ){
            case 13: // Enter
                wcout << endl<<L"Request= {" <<Karret << "}" << endl;
                Karret = L"";
                break;
            case 8: // backSpace
                if (!Karret.empty()) {Karret.pop_back();}
                 wcout <<'\r';
                for(int i =0;i<Karret.size()+1;i++){
                   wcout   << L" ";
                }
                //wcout << L"CARROT: " << Karret.size() << endl;
                wcout  << '\r' << Karret;
                break;
            case 224: // special
                wchar_t Meta;
                Meta = _getwch();
                switch( (int)(Meta) ){
                    case 72:
                        wcout << L"//up";
                        break;
                    case 80:
                        wcout << L"//down"; //down
                        break;
                    case 75:
                       wcout << L"//left"; //left;
                        break;
                    case 77:
                       wcout << L"//right"; //right
                        break;
                    default:
                        wcout << L"ERROR";
                }
                // 72 - up, 80 - down, 75 - left, 77 - right
                break;
            default:
                Karret+= Bukva;
                wcout << '\r' << Karret;

        }


    }

}
