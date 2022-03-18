#include <iostream>

#include <windows.h>
#include <conio.h>

using namespace std;

void SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


string Field[9];


class Cell{
public:
    bool isOriginal = true;
    char value;

};

class SudokuGame{
public:
    Cell Cells[9][9];

    void read_from_Field(){
        for(int i =0;i<9;i++){
            for(int j =0;j<9;j++){
                Cells[i][j].value = Field[i][j];
                if (Field[i][j] == '0'){
                    Cells[i][j].isOriginal = false;
                }else{
                Cells[i][j].isOriginal = true;
                }
            }
        }
    }

    void PrintField(){
        for(int i =0;i<9;i++){
            for(int j =0;j<9;j++){

                if (Cells[i][j].isOriginal == true){
                    SetColor(4,0);
                }else{
                    SetColor(10,0);
                }

                cout << Cells[i][j].value;
            }
            cout << endl;
        }
    }
};



void initField(){
    Field[0] = string("020") + string("090") + string("810");
    Field[1] = string("300") + string("800") + string("962");
    Field[2] = string("000") + string("200") + string("037");

    Field[3] = string("000") + string("706") + string("090");
    Field[4] = string("100") + string("000") + string("740");
    Field[5] = string("400") + string("123") + string("008");

    Field[6] = string("013") + string("470") + string("500");
    Field[7] = string("007") + string("050") + string("300");
    Field[8] = string("254") + string("608") + string("170");
}



int main()
{
    /// 10 - зелёный (новые), 4 - красный (ориг)
    SetColor(10,0);
    initField();
    SudokuGame SG;
    SG.read_from_Field();
    SG.PrintField();
}
