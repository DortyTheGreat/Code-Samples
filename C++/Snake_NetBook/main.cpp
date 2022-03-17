#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include "../BasicWindowsLib.h"
#include <conio.h>
#include <thread>

using namespace std;

const int W = 30;
const int H = 20;

const char Snake_Body = '$';

class Screen{
public:
    void init(){
        for(int i = 0;i<H+2;i++){
            cout << "#";
            for(int j = 0;j<W;j++){
                if (i == 0 || i == (H+1)){
                    cout << "#";
                }else{
                    cout << " ";
                }
            }
            cout << "#"<<endl;
        }
    }


    void draw(pair<int,int> pr, char symbol){
        gotoxy(pr.first+1, pr.second+1);
        cout << symbol;
    }


};

Screen scr;

int Field[W][H];

queue<pair<int,int>> snake;

pair<int,int> apple;

int counter;
int size_;
int isAlive;

void add_element(int x, int y){
    snake.push({x, y});
    Field[x][y] = counter;
    counter++;
    scr.draw({x,y},Snake_Body);
}

void add_element(pair<int,int> pr){
    snake.push(pr);
    Field[pr.first][pr.second] = counter;
    counter++;
    scr.draw(pr,Snake_Body);
}

void init_snake(){
    isAlive = 1;
    size_ = 1;
    counter = 1;
    add_element(W/2,H/2);
}

bool isIllegalMove(pair<int,int> n_head){
    if (n_head.first >= W || n_head.first < 0 || n_head.second >= H || n_head.second < 0){
        return true;
    }
    return (Field[n_head.first][n_head.second]); /// Если пусто -> Field[x][y] = 0 -> false (в ином случае true aka illegal)
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
                    scr.draw(apple,'*');
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
        scr.draw(tail,' ');
        snake.pop();

        if (isIllegalMove(n_head)){
            isAlive = 0;
        }
        add_element(n_head);
    }
}


void ai(){

    gotoxy(0,H+3);
    queue<pair<int, int>> que;
    que.push(snake.back());
    vector<vector<int>> d(W, vector<int>(H));
    vector<vector<pair<int, int>>> p(W, vector<pair<int, int>>(H));
    const vector<pair<int, int>> neighs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };



    d[snake.back().first][snake.back().second] = 1;
    while(!que.empty()){
        pair<int, int> current_pos = que.front();
        que.pop();

        for (auto& neigh: neighs) {
            pair<int, int> t = { current_pos.first + neigh.first, current_pos.second + neigh.second };

            if (!isIllegalMove(t) && !d[t.first][t.second]) {
                d[t.first][t.second] = d[current_pos.first][current_pos.second] + 1;
                p[t.first][t.second] = current_pos;
                que.push(t);
            }
        }
    }


    vector<pair<int, int>> ans;
    for (pair<int, int> cur = apple; cur != snake.back(); cur = p[cur.first][cur.second]) ans.push_back(cur);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "    ";
    move(ans.front().first - snake.back().first, ans.front().second - snake.back().second);
}

#define human_input 0

int main()
{

    scr.init();
    init_snake();
    gen_apple();

    while(isAlive){
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
            ai();
            const int ms = 50;
            this_thread::sleep_for(chrono::milliseconds(ms));
        #endif // ai
    }

    ///cout << "Hello world!" << endl;
    return 0;
}
