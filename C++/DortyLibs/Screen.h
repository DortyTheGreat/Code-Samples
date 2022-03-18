#include <iostream>

#include "BasicWindowsLib.h"

COORD operator+(COORD &a, COORD &b){return {a.X+b.X,a.Y+b.Y};}

class Screen{
public:

    int H;
    int W;

    char** Field;


    /// Где начало экрана
    COORD start_pos;

    Screen(){}

    Screen(int H_, int W_) : H(H_),W(W_) {
        Field = new char*[W];
        for(int i = 0; i < W; ++i)
            Field[i] = new char[H];
    }

    void init(){
        gotoxy(start_pos);

        for(int i = 0;i<H+2;i++){
            std::cout << "#";
            for(int j = 0;j<W;j++){
                if (i == 0 || i == (H+1)){
                    std::cout << "#";
                }else{
                    std::cout << " ";
                }
            }
            std::cout << "#\n";
        }

        std::cout.flush();
    }



    void draw(int x, int y, char symbol){
        gotoxy(x+1, y+1);
        std::cout << symbol;
    }

    void draw(COORD pos, char symbol){
        gotoxy(pos + start_pos);
        std::cout << symbol;
    }

};
