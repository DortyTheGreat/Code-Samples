#include <iostream>
#include <queue>


#include <utility>


using namespace std;

template <typename A, typename B>
pair<A,B> operator+(pair<A,B> &a, pair<A,B> &b){return {a.first+b.first,a.second+b.second};}


#include <algorithm>

#include <conio.h>
#include <thread>
#include "../DortyLibs/Screen.h"




const int W = 10;
const int H = 10;

const char Snake_Body = '$';

Screen scr(W,H);

int Field[W][H];

class Snake{
private:
    /// Контейнер со змеей
    queue<pair<int,int>> snake;


    /// Отдельно храним координаты яблока
    pair<int,int> apple;

    /// Счётчик ходов
    int counter;

public:

    /// Размер змеи
    int size_;
    /// Жива ли змея
    int isAlive;

    void init_snake(){
        isAlive = 1;
        size_ = 1;
        counter = 1;
        add_element(W/2,H/2);
        gen_apple();
    }

    Snake(){
        init_snake();
    }

    void add_element(int x, int y){
        snake.push({x, y});
        Field[x][y] = counter;
        counter++;
        scr.draw(x,y,Snake_Body);
    }

    void add_element(pair<int,int> pr){
        snake.push(pr);
        Field[pr.first][pr.second] = counter;
        counter++;
        scr.draw(pr.first, pr.second,Snake_Body);
    }

    void gen_apple(){
        int amount_of_empty = 0;
        for(int i = 0;i<W;i++){
            for(int j = 0;j<H;j++){
                amount_of_empty += !(Field[i][j]);
            }
        }

        int rand_tile = rand() % amount_of_empty;
        amount_of_empty = 0;
        for(int i = 0;i<W;i++){
            for(int j = 0;j<H;j++){
                if (!Field[i][j]){
                    amount_of_empty ++;
                    if (amount_of_empty == rand_tile){
                        apple.first = i;
                        apple.second = j;
                        scr.draw(apple.first, apple.second,'*');
                    }
                }
            }
        }

    }

    void move(int dx, int dy){
        pair<int,int> n_head = snake.back();
        n_head = {n_head.first+dx,n_head.second+dy};
        if (n_head == apple){
            /// Собрано яблоко
            size_++;
            add_element(n_head);

            /// Gen Apple
            gen_apple();
            ///
        }else{
            /// Не собрано яблоко
            pair<int,int>tail =  snake.front();

            Field[tail.first][tail.second] = 0;
            scr.draw(tail.first, tail.second,' ');
            snake.pop();

            if (isIllegalMove(n_head)){
                isAlive = 0;
            }
            add_element(n_head);
        }
    }

    #include "ai_snake.h"
};















#define human_input 0

int main()
{
    srand(time(0));
    scr.init();
    Snake snk;

    while(snk.isAlive){
        #if human_input
        char input = getch();
        if (input == -32){
            /// extra input >
            input = getch();
            switch(int(input)){
                case 72: move(0,-1); break; /// up
                case 80: move(0,1); break; /// down
                case 77: move(1,0); break; /// right
                case 75: move(-1,0); break; /// left
            }


        }
        #else
            snk.ai();
            const int ms = 40;
            this_thread::sleep_for(chrono::milliseconds(ms));
        #endif // ai
    }

    return 0;
}
