#include <ctime>
#include <cmath>

#include <iostream>

#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

template<typename T>
inline T sqr(const T& a){return a * a;}

struct Vector2i{
    int x,y;
    Vector2i() = default;
    Vector2i(int _x, int _y): x(_x), y(_y){}
    Vector2i operator+ (const Vector2i& other) const {return {x+other.x,y+other.y}; }
    Vector2i operator- (const Vector2i& other) const {return {x-other.x,y-other.y}; }
    Vector2i& operator+= (const Vector2i& other) {x+= other.x; y += other.y; return (*this); }
    bool operator== (const Vector2i& other) const{return (x==other.x && y==other.y); }
    bool operator!= (const Vector2i& other) const{return !((*this) == other); }
};

inline double dist(const Vector2i& vc1,const Vector2i& vc2){
    return sqrt(sqr(vc1.x - vc2.x) + sqr(vc1.y - vc2.y) );
}

bool Roll(double percent){
    return (rand() % 1000 < percent*10);
}

class Cell{
public:
    uint64_t age; /// 0 - empty
};

class Board{
public:

    static const int H = 20;
    static const int W = 20;
    const int cellSize = 30;
    const int textSize = 20;
    const int space = 33;

    Cell Field[H][W];
    Vector2i VectorField[H*W];

    Vector2i head;
    Vector2i tail;
    Vector2i apple;

    uint64_t age = 0;
    unsigned int size = 1;
    bool isAlive = true;

    void add_segment(const Vector2i& vc){
        get_cell(vc).age = ++age;
    }

    void delete_segment(const Vector2i& vc){
        get_cell(vc).age = 0;
    }

    void find_new_tail(){
        for( const Vector2i& vc : { Vector2i(-1,0),{1,0},{0,1},{0,-1}, }){
            if (outOfBounds(vc + tail) ) continue;
            if (get_cell(vc + tail).age == (age-size+1 )){
                tail = vc + tail; break;
            }
        }
    }

    Board(){
        uint64_t seed = time(0);
        srand(seed);
        std::cout << "seed : " << seed << std::endl;

        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                VectorField[i*W + j] = Vector2i(j,i);
                Field[i][j].age = 0;
            }
        }

        add_segment(head = tail = Vector2i(W/2,H/2));


        gen_apple();
    }



    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}
    inline Cell& get_cell(const Vector2i& vc){return Field[vc.y][vc.x];}
    inline const Cell& get_cell_const(const Vector2i& vc)const {return Field[vc.y][vc.x];}




    void gen_apple(){
        std::cout << "generating apple" << std::endl;
        int amount_of_empty = 0;
        for( const Vector2i& vc : VectorField){
            amount_of_empty += !(get_cell(vc).age);
        }

        int rand_tile = rand() % amount_of_empty;
        amount_of_empty = 0;
        for( const Vector2i& vc : VectorField){
            if (get_cell(vc).age) continue;
            if ((amount_of_empty++) == rand_tile){
                apple = vc;
                break;
            }
        }

    }

    void end_game(){
        isAlive = false;
        std::cout << "Game is Ended" << std::endl;
    }

    void warn(){
        ///isAlive = false;
        std::cout << "WARN" << std::endl;
    }

    void move(const Vector2i& mv){
        std::cout << mv.x << " " << mv.y << std::endl;
        if (abs(mv.x) + abs(mv.y) != 1){end_game(); return;}
        if (outOfBounds(head + mv)){end_game(); return;}

        if (head + mv == apple){
            add_segment(head += mv);
            ++size;
            gen_apple();
        }else{
            delete_segment(tail);
            if (get_cell(head += mv).age){end_game(); return;}
            add_segment(head);
            find_new_tail();
        }
    }

    void draw() const{

        if (!isAlive){

            std::cout << ("GAME OVER!");

            return;
        }

        for(int i = 0;i<H;i++){
            for(int j = 0;j<W;j++){
                if (apple == Vector2i(j,i) ){std::cout << "* "; continue;}
                std::cout << "# "[Field[i][j].age == 0] << " ";
            }
            std::cout << std::endl;
        }
    }
};



void hamilton_basic(Board& b){
    if((b.head.x == 0) && (b.head.y == 0)){b.move({0,1});return;}
    if((b.head.x == (b.W-1) ) && (b.head.y == 1)){b.move({0,-1});return;}

    if( (b.head.y == (b.W-1)) && (b.head.x %2 == 0) ){b.move({1,0}); return;}
    if( (b.head.y == 1) && (b.head.x %2 == 1 )){b.move({1,0}); return;}

    ///Работает только для SIZE_ кратного четырём

    if(b.head.y == (0) ){ b.move({-1,0});return;}

    if(b.head.x %2 == 1 ){b.move({0,-1});return;}
    if(b.head.x %2 == 0 ){b.move({0,1});return;}
}

class RelaxRequest{
public:
    int x,y,depth;

     RelaxRequest(int y_,int x_,int depth_){
        x = x_;
        y = y_;
        depth = depth_;
    }
};

class RevRelaxRequest{
public:
    int x,y,depth,walls;

     RevRelaxRequest(int y_,int x_,int depth_,int walls_){
        x = x_;
        y = y_;
        depth = depth_;
        walls = walls_;
    }
};
#include <queue>
#include <vector>

bool isIllegalMove(const Board& b,const Vector2i& n_head){
    if (n_head.x >= b.W || n_head.x < 0 || n_head.y >= b.H || n_head.y < 0){
        return true;
    }
    return (b.Field[n_head.y][n_head.x].age);
}


#include <algorithm>
void BFS(Board& b){
    /*
    for(int i = 0;i<b.H;i++){
        for(int j = 0;j<b.W;j++){
            std::cout << b.Field[i][j].age << " ";
        }
        std::cout << std::endl;
    }
    */

    std::queue<Vector2i> que;
    que.push(b.head);
    std::vector<std::vector<int> > d(b.W, std::vector<int>(b.H));
    std::vector<std::vector<Vector2i> > p(b.W, std::vector<Vector2i>(b.H));
    const std::vector<Vector2i> neighs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };

    d[b.head.x][b.head.y] = 1;
    while(!que.empty()){
        Vector2i current_pos = que.front();
        que.pop();

        for (auto& neigh: neighs) {
            Vector2i t = { current_pos.x + neigh.x, current_pos.y + neigh.y };

            if (!isIllegalMove(b,t) && !d[t.x][t.y]) {
                d[t.x][t.y] = d[current_pos.x][current_pos.y] + 1;
                p[t.x][t.y] = current_pos;
                que.push(t);
            }
        }
    }



    std::vector<Vector2i> ans;
    for (Vector2i cur = b.apple; cur != b.head; cur = p[cur.x][cur.y]) ans.push_back(cur);
    std::reverse(ans.begin(), ans.end());
    ///cout << ans.size() << "    ";
    std::cout << ans.size() << std::endl;
    b.move(ans.front() - b.head);
}

void ai_turn(Board& b){

    BFS(b);

}

/*
void ai_turn(Board& board){
    if(!board.GameStarted) return;

    for( const Vector2i& vc : board.VectorField){
        if (!board.get_cell(vc).isRevealed) continue;

        int neighs = 0;
        int bombs_marked = 0;

        for( const Vector2i& delted : board.get_CloseVectors(vc)){

            ++neighs;
            if (board.get_cell(delted).isMarked) ++bombs_marked;
        }


        if (board.get_cell(vc).next_bombs == bombs_marked){
            /// reveal all non-marked
            for( const Vector2i& delted : board.get_CloseVectors(vc)){
                if (!board.get_cell(delted).isMarked) board.reveal(delted);
            }
        }

        if (board.get_cell(vc).next_bombs == neighs){
            /// mark all that are non-marked
            for( const Vector2i& delted : board.get_CloseVectors(vc)){
                if (!board.get_cell(delted).isMarked) board.mark(delted);
            }
        }



    }

}

*/

/*
void mouseEvent(const sf::RenderWindow& rw, Board& b, sf::Event &event)
{

    if (event.mouseButton.button != sf::Mouse::Left) return;
    Vector2i winpos = sf::Mouse::getPosition(rw);

    b.reveal_by_mouse(winpos);

}
*/

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::cout << 2 << std::endl;


    Board MainBoard;



    unsigned long ticks = 0;
    while (MainBoard.isAlive)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if ( (++ticks) % 1 == 0){
            ///std::cout << "ai goes" << std::endl;
            ai_turn(MainBoard);
            MainBoard.draw();
        }
        /*
        while (window.pollEvent(event))
        {
            switch( int(event.type) ){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                ///mouseEvent(window,MainBoard,event);

                switch( int(event.key.code)){
                case sf::Keyboard::Left:
                    MainBoard.move(Vector2i(-1,0));
                    break;
                case sf::Keyboard::Right:
                    MainBoard.move(Vector2i(1,0));
                    break;
                case sf::Keyboard::Up:
                    MainBoard.move(Vector2i(0,-1));
                    break;
                case sf::Keyboard::Down:
                    MainBoard.move(Vector2i(0,1));
                    break;

                }

            break;
            }
        }
        */



    }

    MainBoard.draw();

    return 0;
}
