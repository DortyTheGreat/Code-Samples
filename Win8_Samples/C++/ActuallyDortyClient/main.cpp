// (Project > Build Options > Other Compile Options) compile options "-finput-charset=CP1251 -fexec-charset=CP866"

#include <iostream>

#include <stdio.h>
#include <stdlib.h> // atoi

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <ctype.h>

#include <windows.h>
#define SEVEN_NULLS L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""

#define HELP_TEXT_CMD L"Для перемещения по \"вкладкам\" используйте стрелочки клавиатуры(вниз-верх), после выбора категории нажмите стрелочку вправо.",\
                 L"Вы можете также вызвать вкладки методами, узнать все методы можно используя комманду /commands",\
                 L"Кустом текст",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""
#define MAIN_MENU_HELLO_TXT L"type /help for help",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""
#define MAIN_MENU_CONSTRUCTOR 4,L"HeDoG.Net",\
                 L"Ege-Project",\
                 L"Dorty Archive",\
                 L"123",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""
#define HeDoG_CONSTRUCTOR 2,L"Gosunov Talk",\
                 L"Chto-to",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""
#define Ege_CONSTRUCTOR 7,L"GameTheory",\
                 L"Prog2",\
                 L"Prog3",\
                 L"Prog4",\
                 L"Prog5",\
                 L"Prog6",\
                 L"Prog7",\
                 L"",\
                 L"",\
                 L""
#define Archives_CONSTRUCTOR 5,L"Archiv1",\
                 L"2",\
                 L"3",\
                 L"4",\
                 L"5",\
                 L"",\
                 L"",\
                 L"",\
                 L"",\
                 L""



using namespace std;


/*
void PseudoCls()
{
   SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {0, 0} );
    for(int i =0;i<5;i++){
        wcout << '\n' << L"                      ";
    }
    SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {0, 0} );
}
*/





class BasicScene{
private:
    int amountOfCollums = 3;
    wstring RelieseTextRus = L"Добро пожаловать в DUC. v3.6.C++  Сделано 05.04.2021 в рамках проекта \"HeDog\" ";
    wstring DebugText = L"Debug Text";

    int thiscollimn = 0;
    wstring Collumns[10];
    wstring Separator = L"-> ";
    wstring RevSeparator = L"   ";
    wstring SysErrorStr = L"SystemErrorStr(NoArgument)";
    wstring Karret = L"";
    int KarretXPos = 4;
    int AmountOfRequestDatas = 1;
    wstring RequestDatas[10];
    wstring FirstWord,Argument;
    bool ArgumentState = true;
    wstring Clear = L"";
public:
    BasicScene(int amount, wstring str0,wstring str1,wstring str2,wstring str3,wstring str4,wstring str5,wstring str6,wstring str7,wstring str8,wstring str9){

    //Collumns[0] =L"HeDoG.Net";
    amountOfCollums = amount;
    Collumns[0] =str0;
    Collumns[1] =str1;
    Collumns[2] =str2;
    Collumns[3] =str3;
    Collumns[4] =str4;
    Collumns[5] =str5;
    Collumns[6] =str6;
    Collumns[7] =str7;
    Collumns[8] =str8;
    Collumns[9] =str9;
    }

    void ClearThisStr(int numOfString,wstring Spaces,int XReturnTo){
CONSOLE_SCREEN_BUFFER_INFO cbsi;
COORD OriginalCursorPosition = cbsi.dwCursorPosition;
SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {0, numOfString} );
wcout << Spaces;
SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {XReturnTo,3+amountOfCollums} );
}

    void RequestPrint(wstring str0,wstring str1,wstring str2,wstring str3,wstring str4,wstring str5,wstring str6,wstring str7,wstring str8,wstring str9){
    wstring Clear_Request;
    for(int i =0;i<10;i++){
        Clear_Request=L"";
        for(int j=0;j<RequestDatas[i].size();j++){
            Clear_Request+= L"  ";
        }
        ClearThisStr(5+amountOfCollums+i,Clear_Request,KarretXPos);

        if(i == 0){ClearThisStr(5+amountOfCollums+i,str0,KarretXPos);RequestDatas[i] = str0;}
        if(i == 1){ClearThisStr(5+amountOfCollums+i,str1,KarretXPos);RequestDatas[i] = str1;}
        if(i == 2){ClearThisStr(5+amountOfCollums+i,str2,KarretXPos);RequestDatas[i] = str2;}
        if(i == 3){ClearThisStr(5+amountOfCollums+i,str3,KarretXPos);RequestDatas[i] = str3;}
        if(i == 4){ClearThisStr(5+amountOfCollums+i,str4,KarretXPos);RequestDatas[i] = str4;}
        if(i == 5){ClearThisStr(5+amountOfCollums+i,str5,KarretXPos);RequestDatas[i] = str5;}
        if(i == 6){ClearThisStr(5+amountOfCollums+i,str6,KarretXPos);RequestDatas[i] = str6;}
        if(i == 7){ClearThisStr(5+amountOfCollums+i,str7,KarretXPos);RequestDatas[i] = str7;}
        if(i == 8){ClearThisStr(5+amountOfCollums+i,str8,KarretXPos);RequestDatas[i] = str8;}
        if(i == 9){ClearThisStr(5+amountOfCollums+i,str9,KarretXPos);RequestDatas[i] = str9;}

    }
}

    int run(){
        system("cls");
    wcout << RelieseTextRus << endl; wcout << DebugText << endl;
        for(int i =0;i<amountOfCollums;i++){
            if(i == thiscollimn){wcout << Separator; }else{wcout << RevSeparator;}
            wcout << Collumns[i] << endl;
        }
        wcout << endl;

        wcout << "cmd:" << Karret;

        RequestPrint(MAIN_MENU_HELLO_TXT);
    while(1){
        wchar_t Bukva;
        //wcout << L"Create Request: ";
        Bukva = _getwch();
        //wcout << Bukva << " " << int(Bukva) << endl; // Enter - 13
        switch( (int)Bukva ){
            case 13: // Enter
                FirstWord = Karret.substr(0,Karret.find(L' '));
                if(Karret.find(L' ') != -1){Argument = Karret.substr(Karret.find(L' ')+1,Karret.size());ArgumentState=true;}else{
                    Argument = SysErrorStr;ArgumentState=false;
                }

                if(FirstWord == L"/help"){ ///RequestData+=L"\n" + HelpMessage;
                RequestPrint(HELP_TEXT_CMD);
                }else{
                RequestPrint(L"Неизвестная Комманда: " + FirstWord ,
                 L"Аргумент для комманды:{" + Argument + L"}",
                 L"Проверьте написание комманды",SEVEN_NULLS);
                }


                Clear = L"";
                for(int i=0;i<Karret.size();i++){
                    Clear+= L" ";
                }
                Karret = L"";
                KarretXPos=4;

                ClearThisStr(3+amountOfCollums,L"cmd:"+Karret+Clear,KarretXPos);
                break;
            case 8: // backSpace
                if (!Karret.empty()) {Karret.pop_back();}
                 KarretXPos=Karret.size() + 4;
                ClearThisStr(3+amountOfCollums,L"cmd:"+Karret+L"  ",KarretXPos);

                break;
            case 224: // special
                wchar_t Meta;
                Meta = _getwch();
                switch( (int)(Meta) ){
                    case 72: // up
                         ClearThisStr(2+thiscollimn,RevSeparator,KarretXPos);
                         thiscollimn= (thiscollimn-1)%amountOfCollums; if(thiscollimn < 0){thiscollimn = amountOfCollums+thiscollimn;}
                         ClearThisStr(2+thiscollimn,Separator,KarretXPos);
                        break;
                    case 80: // down
                        ClearThisStr(2+thiscollimn,RevSeparator,KarretXPos);
                         thiscollimn= (thiscollimn+1)%amountOfCollums;
                        ClearThisStr(2+thiscollimn,Separator,KarretXPos);
                        break;
                    case 75: // left
                        return -1;
                        break;
                    case 77: //right
                        return thiscollimn;
                        break;
                    default: //Error with Meta Data
                        wcout << L"ERROR";
                }
                // 72 - up, 80 - down, 75 - left, 77 - right
                break;
            default:
                Karret+= Bukva;
                KarretXPos=Karret.size() + 4;
                ClearThisStr(3+amountOfCollums,L"cmd:"+Karret+L"  ",KarretXPos);
                //wcout << '\r' << Karret;

        }
        //cls();
        //system("cls");
        //PseudoCls();






    }
    }
    //Static

};


void GosunovTalk(){
    system("cls");
wcout << L"Ку, Гей!" << endl;
wstring Arg;
wcin >> Arg;
wcout << L"Только что ввёл: " << Arg << endl << L"Программа сама закроется, через 3 секунды";
Sleep(3000);
return;
}

void FirstEge(){
system("cls");
wcout << L"Это первая программа, для решения Егэ." << endl;
wcout << L"Бип-Буп, закрываюьс(((";
Sleep(2000);
return;
}

void GameTheory()
{
    system("cls");
    wcout << L"Code By Dorty(Mod By Dorty). Made At 31.03.2021. For Ege-Project" << endl << endl;
    int SizeX=100;
    int SizeY=80;
    int start;
    int ans1 = -1;
    int mult = 2;
    int add = 2;
    int limit = 62;
    int itter = 4;
    wcout << L"input start: "; wcin >> start; wcout << endl;
    wcout << L"input add: "; wcin >> add; wcout << endl;
    wcout << L"input mult: "; wcin >> mult; wcout << endl;
    wcout << L"input limit( >= ): "; wcin >> limit; wcout << endl;

    wcout << L"ANS1 - Известно, что Ваня выиграл своим первым ходом после неудачного первого хода Пети. Укажите минимальное значение S, когда такая ситуация возможна." << endl << endl;
    wcout << L"ANS2 - Петя не может выиграть за один ход;\n— Петя может выиграть своим вторым ходом независимо от того, как будет ходить Ваня." << endl << endl;
    wcout << L"ANS3 - у Вани есть выигрышная стратегия, позволяющая ему выиграть первым или вторым ходом при любой игре Пети;\n— у Вани нет стратегии, которая позволит ему гарантированно выиграть первым ходом." << endl << endl;

    wcout  <<  (limit-start)/mult/mult + (bool)(((limit-start)%(mult*mult))) << " OR ";
    wcout << limit - mult*mult*start << " |MIN = " << endl << endl;
    wcout << L"ANS1 - " << min((limit-start)/mult/mult + (bool)(((limit-start)%(mult*mult))),limit - mult*mult*start);
    char Mat[300][300];


    for(int i = 1;i<300;i++){
        for(int j = 1;j<300;j++){
            if(i+j >= limit){
                Mat[i][j] = 'L';
            }else{
            Mat[i][j] = 'U';
            }
        }
    }

    for(int Itter = 0; Itter < itter;Itter++){
    for(int i = start;i<SizeX;i++){
        for(int j = 1;j<SizeY;j++){
                if(i+j >= limit){continue;}
            char A1 = Mat[i][j+add];
            char A2 = Mat[i][j*mult];
            char A3 = Mat[i+add][j];
            char A4 = Mat[i*mult][j];
            if(A1 == 'L' || A2 == 'L' || A3 == 'L' || A4 == 'L'){
                Mat[i][j] = 'W'; continue;
            }
            if(A1 == 'U' || A2 == 'U' || A3 == 'U' || A4 == 'U'){
                continue;
            }
            if(A1 == 'W' && A2 == 'W' && A3 == 'W' && A4 == 'W'){
                Mat[i][j] = 'L'; continue;
            }
        }
    }
    }
    int Wins=0; int Loses=0;
    wcout << endl << L"W2: ";
    for(int i=1;i<(limit-start)/mult + (bool)(((limit-start)%(mult)));i++){
        if(Mat[start][i] == 'W'){wcout << i << L" "; }
    }

    wcout << endl << L"L2: ";
    for(int i=1;i<(limit-start)/mult + (bool)(((limit-start)%(mult)));i++){
        if(Mat[start][i] == 'L'){wcout << i << L" "; }
    }

    wcout <<endl << L"Нажмите На любую Клавишу, чтобы продолжить...";
    _getwch();
}

void Archive_First(){
system("cls");
wcout << L"Это первый Архив, в котором ничего НЕТ))))" << endl;
wcout << L"Бип-Буп, закрываюсь...";
Sleep(2000);
return;
}


void ExceptionFunctionScene(){
system("cls");
wcout << L"Бип-Буп, кажется данная функция недоступна..." << endl;
wcout << L"Произвожу автоматическое закрытие...";
Sleep(2000);
}


int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    BasicScene MainMenu2(MAIN_MENU_CONSTRUCTOR);
    BasicScene HeDoGScene(HeDoG_CONSTRUCTOR);
    BasicScene EgeSolver(Ege_CONSTRUCTOR);
    BasicScene DortyArchives(Archives_CONSTRUCTOR);

    int ExitState;
    //MainMenu2.declare();
    while(ExitState != -1){

    system("cls");
    wcout   <<L" Innied  ";
    ExitState = MainMenu2.run();

    /* BasicScene
    ExitState = ThisScene.run();
    switch(ExitState){
    case 0: while(ExitState != -1){
    ...
    } ExitState = -2; break;

    case 1: while(ExitState != -1){
    ...
    } ExitState = -2; break;

    case 2: while(ExitState != -1){
    ...
    } ExitState = -2; break;

    ...
    ...
    ...

    }


    */
    switch(ExitState){
    case 0:
        while(ExitState != -1 ){ExitState = HeDoGScene.run();
        switch(ExitState){
        case -2: break;
        case -1: break;

        case 0: GosunovTalk(); break;

        default: ExceptionFunctionScene();


        }
        } ExitState = -2; break; // HeDoG

    case 1:
        while(ExitState != -1 ){ExitState = EgeSolver.run();
        switch(ExitState){
        case -2: break;
        case -1: break;

        case 0: GameTheory(); break;

        default: ExceptionFunctionScene();

        }
        } ExitState = -2; break; // Ege

    case 2:
        while(ExitState != -1 ){ExitState = DortyArchives.run();
        switch(ExitState){
        case -2: break;
        case -1: break;

        case 0: Archive_First(); break;

        default: ExceptionFunctionScene();

        }

        } ExitState = -2; break; // Ege
    }

    //MainMenu();
    system("cls");
    //wcout << stoi(L"-123") + stoi(L"333") << endl << L":";
     //wchar_t b = _getwch();
    //wcin >> b;

    }

    return 0;
}

