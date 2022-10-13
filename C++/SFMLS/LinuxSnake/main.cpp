


///#define SFML_STATIC
#include <SFML/Graphics.hpp>

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

inline double dist(const sf::Vector2i& vc1,const sf::Vector2i& vc2){
    return sqrt(sqr(vc1.x - vc2.x) + sqr(vc1.y - vc2.y) );
}

bool Roll(double percent){
    return (rand() % 1000 < percent*10);
}

class Cell{
public:
    unsigned long long age; /// 0 - empty
    sf::RectangleShape shape;
};

class Board :public sf::Drawable{
public:

    static const int H = 20;
    static const int W = 20;
    const int cellSize = 30;
    const int textSize = 20;
    const int space = 33;

    Cell Field[H][W];
    sf::Vector2i VectorField[H*W];

    sf::Vector2i head;
    sf::Vector2i tail;
    sf::Vector2i apple;

    sf::Color emptyColor = sf::Color::Green;
    sf::Color snakeColor = sf::Color::Black;
    sf::Color appleColor = sf::Color::Red;

    unsigned long long age = 0;
    unsigned int size = 1;
    bool isAlive = true;

    static sf::Font font;

    void add_segment(const sf::Vector2i& vc){
        get_cell(vc).age = ++age;
        get_cell(vc).shape.setFillColor(snakeColor);
    }

    void delete_segment(const sf::Vector2i& vc){
        get_cell(vc).age = 0;
        get_cell(vc).shape.setFillColor(emptyColor);
    }

    void find_new_tail(){
        for( const sf::Vector2i& vc : { sf::Vector2i(-1,0),{1,0},{0,1},{0,-1}, }){
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
                VectorField[i*W + j] = sf::Vector2i(j,i);
                Field[i][j].age = 0;
                sf::RectangleShape& shape = Field[i][j].shape;
                shape = sf::RectangleShape(sf::Vector2f(cellSize,cellSize));
                shape.setFillColor(emptyColor);
                shape.setPosition(sf::Vector2f(space * j, space * i));
            }
        }

        add_segment(head = tail = sf::Vector2i(W/2,H/2));


        gen_apple();
    }



    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const sf::Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}
    inline Cell& get_cell(const sf::Vector2i& vc){return Field[vc.y][vc.x];}
    inline const Cell& get_cell_const(const sf::Vector2i& vc)const {return Field[vc.y][vc.x];}




    void gen_apple(){
        int amount_of_empty = 0;
        for( const sf::Vector2i& vc : VectorField){
            amount_of_empty += !(get_cell(vc).age);
        }

        int rand_tile = rand() % amount_of_empty;
        amount_of_empty = 0;
        for( const sf::Vector2i& vc : VectorField){
            if (get_cell(vc).age) continue;
            if ((amount_of_empty++) == rand_tile){
                get_cell(apple = vc).shape.setFillColor(appleColor);
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

    void move(const sf::Vector2i& mv){
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

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        sf::Text text;

            text.setFont(font); // font is a sf::Font
            text.setCharacterSize(textSize); // in pixels, not points!

            // set the color
            text.setFillColor(sf::Color::Blue);
        if (!isAlive){
            sf::Text text;

            text.setFont(font); // font is a sf::Font
            text.setCharacterSize(textSize * 4); // in pixels, not points!

            // set the color
            text.setFillColor(sf::Color::Red);
            text.setString("GAME OVER!");
            target.draw(text);
            return;
        }

        for( const sf::Vector2i& vc : VectorField){
            target.draw(get_cell_const(vc).shape);
            if (get_cell_const(vc).age){
                text.setString(to_str(get_cell_const(vc).age));
                text.setPosition(space*vc.x, space*vc.y );
                ///target.draw(text);
            }



        }
    }
};

sf::Font Board::font;


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

bool isIllegalMove(const Board& b,const sf::Vector2i& n_head){
    if (b.outOfBounds(n_head)) return true;

    return (b.get_cell_const(n_head).age);
}
#include <iomanip>
void BFS(Board& b){

    for(int i = 0;i<b.H;i++){
        for(int j = 0;j<b.W;j++){
            std::cout << std::setw(5) << b.Field[i][j].age << " ";
        }
        std::cout << std::endl;
    }

    std::queue<sf::Vector2i> que;
    que.push(b.head);
    std::vector<std::vector<int> > d(b.W, std::vector<int>(b.H));
    std::vector<std::vector<sf::Vector2i> > p(b.W, std::vector<sf::Vector2i>(b.H));
    static const std::vector<sf::Vector2i> neighs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };


    std::cout << "here" << std::endl;
    d[b.head.y][b.head.x] = 1;
    while(!que.empty()){
        sf::Vector2i current_pos = que.front();
        que.pop();

        for (auto& neigh: neighs) {
            sf::Vector2i t = current_pos + neigh;

            if (!isIllegalMove(b,t) && !d[t.y][t.x]) {
                d[t.y][t.x] = d[current_pos.y][current_pos.x] + 1;
                p[t.y][t.x] = current_pos;
                que.push(t);
            }
        }
    }
    std::cout << "here" << std::endl;


    std::vector<sf::Vector2i> ans;
    for (sf::Vector2i cur = b.apple; cur != b.head; cur = p[cur.y][cur.x]) ans.push_back(cur);
    reverse(ans.begin(), ans.end());
    ///cout << ans.size() << "    ";
    b.move(ans.front() - b.head);
}

void ai_turn(Board& b){

    BFS(b);

}

/*
void ai_turn(Board& board){
    if(!board.GameStarted) return;

    for( const sf::Vector2i& vc : board.VectorField){
        if (!board.get_cell(vc).isRevealed) continue;

        int neighs = 0;
        int bombs_marked = 0;

        for( const sf::Vector2i& delted : board.get_CloseVectors(vc)){

            ++neighs;
            if (board.get_cell(delted).isMarked) ++bombs_marked;
        }


        if (board.get_cell(vc).next_bombs == bombs_marked){
            /// reveal all non-marked
            for( const sf::Vector2i& delted : board.get_CloseVectors(vc)){
                if (!board.get_cell(delted).isMarked) board.reveal(delted);
            }
        }

        if (board.get_cell(vc).next_bombs == neighs){
            /// mark all that are non-marked
            for( const sf::Vector2i& delted : board.get_CloseVectors(vc)){
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
    sf::Vector2i winpos = sf::Mouse::getPosition(rw);

    b.reveal_by_mouse(winpos);

}
*/
#include <bitset>
int main()
{
    double a = -125.8825;
    unsigned long long bits = *reinterpret_cast<unsigned long long*>(&a);
    std::bitset<64> b = bits;
    std::cout << b << std::endl;
    std::cout << 2 << std::endl;
    if (!Board::font.loadFromFile("Arial.ttf"))
    {
        std::cout << "font load error" << std::endl;
    }

    Board MainBoard;


    sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML works!");
    window.setFramerateLimit(120);
    unsigned long ticks = 0;
    while (window.isOpen())
    {
        if ( (++ticks) % 30 == 0){
            ///std::cout << "ai goes" << std::endl;
            ai_turn(MainBoard);
        }
        sf::Event event;
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
                    MainBoard.move(sf::Vector2i(-1,0));
                    break;
                case sf::Keyboard::Right:
                    MainBoard.move(sf::Vector2i(1,0));
                    break;
                case sf::Keyboard::Up:
                    MainBoard.move(sf::Vector2i(0,-1));
                    break;
                case sf::Keyboard::Down:
                    MainBoard.move(sf::Vector2i(0,1));
                    break;

                }

            break;
            }
        }


        window.clear();
        window.draw(MainBoard);
        window.display();
    }

    return 0;
}
