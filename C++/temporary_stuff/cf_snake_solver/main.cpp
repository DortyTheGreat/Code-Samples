#include <iostream>

using namespace std;

#include <ctime>
#include <cmath>

#include <iostream>
#include <vector>

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

#define pure __attribute__((always_inline))

struct LCM{
    uint64_t mult, incr, mod;
    uint64_t old_rand;
    pure uint64_t step(const uint64_t& arg){ return (arg*mult + incr) % mod; }

    pure uint64_t get(const uint64_t& arg){ return (old_rand = step(old_rand)) % arg; }

    ///pure void step(uint64_t& arg){ arg = (arg*mult + incr) % mod; }
};

LCM rrd;

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


class Cell{
public:
    uint64_t age; /// 0 - empty
};

template<typename T>
class Array2D{
    T** Field;
public:

    size_t H,W;
    Array2D() = default;


    Array2D(const size_t& _H, const size_t& _W, const T& val = 0) : H(_H), W(_W){
        Field = new T*[H];
        for(int i = 0;i < H; ++i){
            Field[i] = new T[W];
            for(int j = 0; j < W; ++j){
                Field[i][j] = val;
            }
        }
    }

    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}

    inline Cell& operator[](const Vector2i& vc){return Field[vc.y][vc.x];}
    inline const Cell& operator[](const Vector2i& vc)const {return Field[vc.y][vc.x];}
    inline const T* operator[](const size_t& index) const {return Field[index];}
};

class Board{
public:
    Array2D<Cell> Field;
    std::vector<Vector2i> VectorField;

    Vector2i head, tail, apple;

    uint64_t age = 0;
    uint16_t size = 1;
    bool isAlive = true;

    void add_segment(const Vector2i& vc){
        Field[vc].age = ++age;
    }

    void delete_segment(const Vector2i& vc){
        Field[vc].age = 0;
    }

    void find_new_tail(){
        for( const Vector2i& vc : { Vector2i(-1,0),{1,0},{0,1},{0,-1}, }){
            if (Field.outOfBounds(vc + tail) ) continue;
            if (Field[vc + tail].age == (age-size+1 )){
                tail = vc + tail; break;
            }
        }
    }

    Board(int _n = 20, int _m = 20) : Field(_n,_m,{0}){
        add_segment(head = tail = Vector2i(0,0));
        gen_apple();
    }









    void gen_apple(){

        if (size != Field.H*Field.W){cin >> apple.x >> apple.y;}else{
            exit(0);

        }

        /*
        if (size != H*W){
            int amount_of_empty = 0;
            for( const Vector2i& vc : VectorField){
                amount_of_empty += !(get_cell(vc).age);
            }
            if (amount_of_empty == 0){

                ///finish();
            }
            int rand_tile = rrd.get(amount_of_empty);
            amount_of_empty = 0;
            for( const Vector2i& vc : VectorField){
                if (get_cell(vc).age) continue;
                if ((amount_of_empty++) == rand_tile){
                    apple = vc;
                    std::cout << apple.x << " " << apple.y << std::endl;
                    break;
                }
            }


        }else{
            exit(0);

        }
        */

    }

    void end_game(){
        isAlive = false;
    }


    void move(const Vector2i& mv){



        if (abs(mv.x) + abs(mv.y) != 1){end_game(); return;}

        if (mv.x == -1){std::cout << "l";}
        if (mv.x == 1){std::cout << "r";}

        if (mv.y == -1){std::cout << "u";}
        if (mv.y == 1){std::cout << "d";}


        if (Field.outOfBounds(head += mv)){end_game(); return;}

        if (head == apple){
            add_segment(head);
            ++size;
            gen_apple();
        }else{
            delete_segment(tail);
            if (Field[head].age){end_game(); return;}
            add_segment(head);
            find_new_tail();
        }
    }

    void draw() const{

        if (!isAlive){

            std::cout << ("GAME OVER!");

            return;
        }

        for(int i = 0;i<Field.H;i++){
            for(int j = 0;j<Field.W;j++){
                if (apple == Vector2i(j,i) ){std::cout << "* "; continue;}
                std::cout << "# "[Field[i][j].age == 0] << " ";
            }
            std::cout << std::endl;
        }
    }
};



void hamilton_basic(Board& b){
    if((b.head.x == 0) && (b.head.y == 0)){b.move({0,1});return;}
    if((b.head.x == (b.Field.W-1) ) && (b.head.y == 1)){b.move({0,-1});return;}

    if( (b.head.y == (b.Field.W-1)) && (b.head.x %2 == 0) ){b.move({1,0}); return;}
    if( (b.head.y == 1) && (b.head.x %2 == 1 )){b.move({1,0}); return;}

    ///Работает только для SIZE_ кратного четырём

    if(b.head.y == (0) ){ b.move({-1,0});return;}

    if(b.head.x %2 == 1 ){b.move({0,-1});return;}
    if(b.head.x %2 == 0 ){b.move({0,1});return;}
}

void hamilton_better(Board& b) {
    //int skip = 1;

    if ((b.head.x == 0) && (b.head.y == 0)) { /// самая контактная точка
        b.move({0, 1});
        return;
    }
    if ((b.head.x == (b.Field.W - 1)) && (b.head.y == 1)) {
        b.move({0, -1});
        return;
    }
    if (b.head.x != (b.Field.W - 1)){
        bool NewReighn = (b.Field[b.Field.H - 1][b.head.x+1].age == 0) && (b.Field[1][b.head.x+1].age == 0);
        if( (b.size - 1) > (b.Field.H*b.Field.W/2) ){NewReighn = 0;}
        if (NewReighn){ /// Вся механика скипов
            ///cout << "trying to skip" << endl;
            if ((b.head.y == (b.Field.H - 1))) { /// Скип в самой нижней строчке
                ///cout << "in the lowest" << endl;
                if (b.head.x < (b.apple.x -  1 )){ /// Условие скипа # 1 (Яблоко справа)
                    b.move({1, 0});
                    return;
                }

                if ( (b.head.x > (b.apple.x)) ){ /// Условие скипа # 2 (Яблоко слева)
                    if(b.head.x < (b.Field.W - 1)){ /// Проверка для того, чтобы змейка не врезалась в стену
                        b.move({1, 0});
                        return;
                    }
                }

            }

            if ((b.head.y == (1))) { /// Скип в самой(предсамой) ВЕРХНЕЙ строчке
                if (b.head.x < (b.apple.x - 1 )){ /// Условие скипа # 1 (Яблоко справа)
                    b.move({1, 0});
                    return;
                }

                if ( (b.head.x > (b.apple.x)) ){ /// Условие скипа # 2 (Яблоко слева)
                    if(b.head.x < (b.Field.W - 1)){ /// Проверка для того, чтобы змейка не врезалась в стену
                        b.move({1, 0});
                        return;
                    }
                }

            }
        }
    }

    if (b.head.y == (0)) { /// Возврат в самой САМОЙ верхней полоске
        b.move({-1, 0});
        return;
    }


    if ((b.head.y == (b.Field.H - 1)) && (b.head.x % 2 == 0)) { /// В самом низу
        b.move({1, 0});
        return;
    }
    if ((b.head.y == 1) && (b.head.x % 2 == 1)) {
        b.move({1, 0});
        return;
    }

    if (b.head.x % 2 == 1) {
        b.move({0, -1});
        return;
    }

    if (b.head.x % 2 == 0) {
        b.move({0, 1});
        return;
    }
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
    if (n_head.x >= b.Field.W || n_head.x < 0 || n_head.y >= b.Field.H || n_head.y < 0){
        return true;
    }
    return (b.Field[n_head.y][n_head.x].age);
}


#include <algorithm>
void BFS(Board& b){

    std::queue<Vector2i> que;
    que.push(b.head);
    std::vector<std::vector<int> > d(b.Field.W, std::vector<int>(b.Field.H));
    std::vector<std::vector<Vector2i> > p(b.Field.W, std::vector<Vector2i>(b.Field.H));
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



#include <iostream>
#include <chrono>
#include <thread>

int sign(int a){
    if (a == 0) return 0;
    if (a < 0) return -1;
    return 1;
}

int main(int argc, char* argv[])
{

    ///setName("Interactor Snake");
    ///registerInteraction(argc, argv);

    /// input file



    /// n m
    /// seed

    int n,m;
    cin >> n >> m;

    rrd.mult = 1000002449;
    rrd.incr = 1000000411;
    rrd.mod = 1000010029;
    rrd.old_rand = 13;

    /// n - x; m - y
    Board MainBoard(n,m);




    unsigned long ticks = 0;
    while (MainBoard.isAlive)
    {
        /*
        if (MainBoard.head.x != MainBoard.apple.x){
            int dx = -sign(MainBoard.head.x - MainBoard.apple.x);



            MainBoard.move({dx,0});

        }else{
            int dy = -sign(MainBoard.head.y - MainBoard.apple.y);



            MainBoard.move({0,dy});

        }
        */

        hamilton_better(MainBoard);

        if ( (++ticks) % 1 == 0){
            ///MainBoard.draw();
        }
        ///this_thread::sleep_for(chrono::milliseconds(30));




    }


    return 0;
}
