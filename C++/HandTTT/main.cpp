#include <iostream>
#include "BasicWindowsLib.h"
#include <conio.h>
#include <utility>
using namespace std;
const int W = 40;
const int H = 10;
const int D = 5;


int Field[H][W];
/// 0 - empty, 1 - krestik, -1 - nolik

char to_char(int a){
    if (a == 0){return ' ';}
    if (a == -1){return '0';}
    return 'X';
}

void clear_field(){
    for(int i = 0;i<H;i++){
        for(int j = 0;j<W;j++){
            Field[i][j] = 0;
        }
    }
}

void print_field(){
    gotoxy(0,0);
    for(int i = 0;i<H;i++){
        for(int j = 0;j<W;j++){
            cout << to_char(Field[i][j]);
        }
        cout <<"$" << endl;
    }
    cout << "$" << endl;
}

/// 0 - ok, 1 - error
int place_element(int x, int y, int symbol){
    if (Field[y][x] != 0){return 1;}
    Field[y][x] = symbol;
    gotoxy(x,y);
    cout << to_char(symbol);
    return 0;
}

string player_decoder(int player){
    if (player == 1){return "Krestik";}
    if (player == -1){return "Nolik";}
    return "abobus";
}

void win(int player, string reason){
    gotoxy(0,H);
    cout << player_decoder(player) << " Won. Reason: " << reason << endl;
}

/// true - есть победа



bool check_win_state( int Field[][W] ){
    for(int i = 0;i<H-D+1;i++){
        for(int j = 0;j<W;j++){
            int flag = Field[i][j];
            for(int k = 1;k<D;k++){ if (flag != Field[i+k][j]){flag = 0;break;}}
            if (flag){return flag;}
        }
    }

    for(int i = 0;i<H;i++){
        for(int j = 0;j<W-D+1;j++){
            int flag = Field[i][j];
            for(int k = 1;k<D;k++){ if (flag != Field[i][j+k]){flag = 0;break;}}
            if (flag){return flag;}
        }
    }

    for(int i = 0;i<H-D+1;i++){
        for(int j = 0;j<W-D+1;j++){
            int flag = Field[i][j];
            for(int k = 1;k<D;k++){ if (flag != Field[i+k][j+k]){flag = 0;break;}}
            if (flag){return flag;}
        }
    }

    for(int i = D-1;i<H;i++){
        for(int j = 0;j<W-D+1;j++){
            int flag = Field[i][j];
            for(int k = 1;k<D;k++){ if (flag != Field[i-k][j+k]){flag = 0;break;}}
            if (flag){return flag;}
        }
    }


    return 0;
}

bool check_win_state(){
    return check_win_state(Field);
}

int get(int i, int j){
    if (i < 0 || j < 0 || i >= H || j >= W){
        return 2; /// Пределы поля
    }
    return Field[i][j];
}


int who_am_i = -1;
int who_is_my_enemy = 1;
int my_debug_row = H + 1;

void log(string str){
    gotoxy(0,my_debug_row);
    cout << str << endl;
}

int requrs(int Field[][W], int d){


    if (d == 0) return 0;
        for(int i = 0;i < H;i++){
            for(int j = 0;j < W; j++){

            }
        }
}

pair<int,int> kul_alg(){

    int T_Field[H][W];

    memcpy(T_Field,Field,sizeof(Field));

    for(int i = 0;i < H;i++){
        for(int j = 0;j < W; j++){
            if (Field[i][j] == 0){
                /// Оппоннет в теории может сюда поставить
                T_Field[i][j] = who_is_my_enemy;
                if (check_win_state(T_Field)){ /// Видимо оппонент так может победить
                    log("Ooh! You Could  Have Won, nice try though))))!");
                    return {i,j};
                }
                T_Field[i][j] = 0;
            }
        }
    }




    for(int i = 0;i<H;i++){
        for(int j = 0;j<W;j++){
            if (Field[i][j] == who_is_my_enemy && (get(i+1,j) == 0)){
                log("Placing Below your krestik for fun  ");
                return {i+1,j};
            }
        }
    }

    log("some kind of exception I guess...  ");
    return {H-1,W-1};

}

int main()
{
    clear_field();
    print_field();

    check_win_state();

    int XCar = 0;
    int YCar = 0;

    for(int turn = 1;true;turn *= -1){
        int X,Y;
        if (turn == 1){
            char input = -1;
            while (input != 13){
                    gotoxy(XCar,YCar);
                input = getch();
                if (input == -32){
                    /// extra input >
                    input = getch();
                    switch(int(input)){
                        case 72: YCar--; break; /// up
                        case 80: YCar++; break; /// down
                        case 77: XCar++; break; /// right
                        case 75: XCar--; break; /// left
                    }
                    gotoxy(XCar, YCar);
                }
            }
            X = XCar;
            Y = YCar;
        }else{
            pair<int,int> abobus = kul_alg();
            Y = abobus.first;
            X = abobus.second;
        }


        if (place_element(X,Y, turn)){win(turn*(-1), "auto lose due to illegal placement"); break;}

        if (check_win_state()){
            win(turn,"Normal Win");
            break;
        }


    }


    ///cout << "Hello world!" << endl;
    return 0;
}
