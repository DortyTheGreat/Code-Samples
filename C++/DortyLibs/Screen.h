#include <iostream>

#include "BasicWindowsLib.h"
COORD operator+(COORD &a, COORD &b){return {a.X+b.X,a.Y+b.Y};}

class Screen{
public:

    int H;
    int W;

    char** Field;

    COORD start_pos;
    const char zero = ' ';
    Screen(){}

    Screen(int H_, int W_) : H(H_),W(W_) {
        Field = new char*[W];
        for(int i = 0; i < W; ++i)
            Field[i] = new char[H];
    }

    void init(){
        gotoxy(start_pos);

        for(int i = 0;i<W;i++){
            for(int j = 0; j < H; j++){
                Field[i][j] = zero;
            }
        }
    }

    void force_draw(COORD pos, char symbol){
        gotoxy(pos + start_pos);
        Field[pos.Y][pos.X] = symbol;
        std::cout << symbol;
    }

    void draw(COORD pos, char symbol){
        if (Field[pos.Y][pos.X] != symbol){
            force_draw(pos,symbol);
        }
    }

};
