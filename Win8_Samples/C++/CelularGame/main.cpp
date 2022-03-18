#include <iostream>

using namespace std;


class Player{

};

class CelularGame{
public:
    int width;
    int Players;

    int ** Field;

    int GameWinnedBy = 0;
    /// 0 - Игра в процессе
    /// 1 - победил 1ый игрок
    /// 2 - победил второй игрок
    /// 3-  победил 3ий и т.д.

    void init_field(){


        Field = new int* [width];

        for(int i =0;i<width;i++){
            Field[i] = new int[width];
        }

        for(int i =0;i<width;i++){

            for(int j =0;j<width;j++){
                Field[i][j] = 0;
            }
        }

    }

    void print(){
        for(int i =0;i<width;i++){

            for(int j =0;j<width;j++){
                cout << Field[i][j] << " ";
            }
            cout << endl;
        }
    }




};



int main()
{
    CelularGame cg;
    cg.width = 5;
    cg.init_field();

    cg.print();

    //cg.ApplyVoidToAllFieldElements([](int a) {cout << a;});
}
