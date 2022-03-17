#include <iostream>
#include <windows.h>
#include <utility>
#include <sstream>
#include <string>       // std::string

#include "KulAi.h"
#include "LexaAi.h"
#include "DortyLogs.h"

using namespace std;


/// 0 - nichego, 1 - crestik, 2 - nolik


bool DoLogging = 1;

string GameId;
const int W = 15;
const int connect_to_win = 5; /// Сколько в ряд клеточек, чтобы победить

bool PunishIllegalPlacement = 1;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void CLS(){
    gotoxy(0,0);
}

string fromIntToString(int type){
    switch (type){
    case 0: return "Empty";
    case 1: return "Krestik";
    case 2: return "Nolik";
    default: return "ERROR";
    }
}

char fromIntToChar(int type){
    switch (type){
    case 0: return '.';
    case 1: return 'X';
    case 2: return '0';
    default: return '?';
    }
}
class TicTacToe{

public:

    int GameFinishedState = 0;
    int turns = 0;
    /// 0 - игра в процессе, 1 - победа крестиков, 2 - победа ноликов

    string AgentNames[2];

    int Field[W][W];

    void initField(){
        turns = 0;
        GameFinishedState = 0;
        for(int y=  0;y<W;y++){
            for(int x = 0;x<W;x++){
                Field[y][x] = 0;
            }

        }
    }

    void drawField(){
        CLS();
        for(int y=  0;y<W;y++){
            for(int x = 0;x<W;x++){
                cout << fromIntToChar(Field[y][x]);
            }
            cout << endl;
        }

        ///LogString("Logs\\" + GameId + "_FrameLogs.txt",FieldToStr());
    }



    void WinGame(int WinnerType, string Reason, int turn){

        if (GameFinishedState != 0) return; /// обход двойного выигрыша, при 6+ в ряд

        GameFinishedState = WinnerType;
        string EndText = fromIntToString(WinnerType) + " Win. Turn: " + NumberToString(turn) + ", Reason: " + Reason;
        cout << EndText << endl;
        LogString("Logs\\" + GameId + "_TurnLogs.txt",EndText);

    }

    void LoseGame(int LoserType, string Reason, int turn){
        WinGame(!(LoserType-1) + 1,  Reason,  turn);

    }

    void CheckGameState(){


        ///Чеккер ВертиКАЛЬных полосок
        for(int y=  0;y<W-connect_to_win+1;y++){
            for(int x = 0;x<W;x++){

                    int FirstValue = Field[y][x];
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int Y_ = 0; Y_ < connect_to_win;Y_++){
                            if (Field[y+Y_][x] != FirstValue){
                                break;
                            }
                            counter++;
                            ///cout << "First Value - " << FirstValue << " - " << Field[y+Y_][x]  << endl;
                            if(counter == connect_to_win){ WinGame(FirstValue,"NormalWin1: " + NumberToString(x) + " - " + NumberToString(y),turns);}
                        }
                    }


            }

        }

        ///Чеккер Горизонтальных полосок
        for(int y=  0;y<W;y++){
            for(int x = 0;x<W-connect_to_win+1;x++){

                    int FirstValue = Field[y][x];
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_ = 0; X_ < connect_to_win;X_++){
                            if (Field[y][x+X_] != FirstValue){
                                break;
                            }
                            counter++;
                            if(counter == connect_to_win){WinGame(FirstValue,"NormalWin2: " + NumberToString(x) + " - " + NumberToString(y),turns);}
                        }

                    }

            }

        }

        ///Чеккер Диаг (\) полосок
        for(int y=  0;y<W-connect_to_win+1;y++){
            for(int x = 0;x<W-connect_to_win+1;x++){

                    int FirstValue = Field[y][x];
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_Y = 0; X_Y < connect_to_win;X_Y++){


                            if (Field[y+X_Y][x+X_Y] != FirstValue){
                                break;
                            }
                            counter++;

                            if(counter == connect_to_win){WinGame(FirstValue,"NormalWin3: " + NumberToString(x) + " - " + NumberToString(y),turns);}
                        }

                    }

            }

        }

        ///Чеккер Диаг (/) полосок
        for(int y=  0;y<W-connect_to_win+1;y++){
            for(int x = connect_to_win-1;x<W;x++){

                    int FirstValue = Field[y][x];
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_Y = 0; X_Y < connect_to_win;X_Y++){


                            if (Field[y+X_Y][x-X_Y] != FirstValue){
                                break;
                            }
                            counter++;
                            if(counter == connect_to_win){WinGame(FirstValue,"NormalWin4: " + NumberToString(x) + " - " + NumberToString(y) ,turns);}
                        }

                    }


            }

        }

        ///Чек на норм победу.

    }


    void place(int type, pair<int,int> location){
        if (Field[location.second][location.first] == 0){
            Field[location.second][location.first] = type;

            CheckGameState();

        }else{
            ///cout << "INVALID TURN MADE BY: " << fromIntToString(type) << "     ";
            if (PunishIllegalPlacement){
                LoseGame(type,"Auto Loss Due to illegal placement",turns);
            }
        }
    }



    string FieldToStr(){
        string str;
        for(int y=  0;y<W;y++){
            for(int x = 0;x<W;x++){
                str+= fromIntToChar(Field[y][x]);
            }

        }

        return str;

    }

    void SimulateAiEnviroment(int TickDelay, bool RenderFrames, bool RenderLastFrame, int FirstPlayer){

        initField();

        while( !GameFinishedState ){
            turns++;


            pair<int,int> testPair;

            string algoritmName = "PLACEHOLDER";

            if ((turns+FirstPlayer)%2){

                testPair = KulAi(FieldToStr(),W);
                algoritmName = KulAiName;
            }else{

                testPair = LexaAi(FieldToStr(),W);
                algoritmName = LexaAiName;
            }
            place (turns%2 + 1,testPair);
            if (RenderFrames){drawField();}

            Sleep(TickDelay);



            if (DoLogging){


                string TurnStr = fromIntToString(turns%2 + 1) + " Made a turn, algoritmName: " + algoritmName + ", placed at (" + NumberToString(testPair.first) + ", " + NumberToString(testPair.second)  + " )";

                LogString("Logs\\" + GameId + "_FrameLogs.txt",FieldToStr());
                LogString("Logs\\" + GameId + "_TurnLogs.txt",TurnStr);
            }
        }

        if(RenderLastFrame){
            cout << endl;
            for(int y=  0;y<W;y++){
                for(int x = 0;x<W;x++){
                    cout << fromIntToChar(Field[y][x]);
                }
                cout << endl;
            }
        }

    }
};





void PlayAutoGame(bool RenderLastFrame, int SessionId ){
    GameId = NumberToString(std::time(0)) + "_" + NumberToString(SessionId);
    string StartGame = "Started new Game #" + GameId + " - ";
    cout << StartGame;
    if (DoLogging){
        StartLogging("Logs\\" + GameId + "_FrameLogs.txt");
        StartLogging("Logs\\" + GameId + "_TurnLogs.txt");
    }

    TicTacToe TTT;

    TTT.SimulateAiEnviroment(0, 0, RenderLastFrame, SessionId);

}

void StartSession(int pairs){

for(int GAMES = 0; GAMES < pairs*2;GAMES++){
    PlayAutoGame(0,GAMES);
}

}



int main()
{
    DoLogging = true;
    srand ( time(NULL) );

    StartSession(10);

    ///PlayAutoGame(1);




}
