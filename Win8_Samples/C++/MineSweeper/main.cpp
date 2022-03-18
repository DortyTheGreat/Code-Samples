#include <iostream>

using namespace std;

int width = 32; /// Размер поля
int W2 = 30;
int GenField[32][32]; /// Поле Генерирующиеся
int BombChance = 20; /// Шанс на появление бомбы (в процентах)


int GetNearBombCount(int y, int x){
    int cou = 0;

    for(int i = y-1; i< y+2;i++){
        for(int j = x-1; j< x+2; j++){
            if(GenField[i][j] == -1){
                cou++;
            }
        }
    }
    return cou;
}

int main()
{


    for(int i = 0; i < width; i++){
        for(int j = 0; j < width; j++){
            GenField[i][j] = 0;
        }
    }

    for(int i = 1; i < W2+1; i++){
        for(int j = 1; j < W2+1; j++){
            if (rand() % 100 < BombChance){
                GenField[i][j] = -1;
            }else{
                GenField[i][j] = 0;
            }
        }
    }

    for(int i = 1; i < W2+1; i++){
        for(int j = 1; j < W2+1; j++){
            if (GenField[i][j] != -1){
                GenField[i][j] = GetNearBombCount(i,j);
            }
        }
    }

    for(int i = 0; i < width; i++){
        for(int j = 0; j < width; j++){
                if(GenField[i][j] == -1){
                    cout << "B ";
                }else{
                    cout << GenField[i][j] << " ";
                }
        }
        cout << endl;
    }

}
