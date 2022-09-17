



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
    bool isBomb;
    bool isRevealed;
    bool isMarked;
    int next_bombs;
    int next_bombs2;
    sf::RectangleShape shape;
};

class Board :public sf::Drawable{
public:

    static const int H = 20;
    static const int W = 30;
    const int cellSize = 30;
    const int textSize = 20;
    const int space = 33;

    Cell Field[H][W];
    sf::Vector2i VectorField[H*W];

    sf::Vector2i CloseVectors[8];

    const double safe_dist = 3;
    bool GameStarted = false;

    bool autoZero = true;

    sf::Font font;

    Board(){

        if (!font.loadFromFile("Arial.ttf"))
        {
            std::cout << "font load error" << std::endl;
        }


        int size = 0;
        for(int dx = -1; dx <= 1; ++dx){
            for(int dy = -1; dy <= 1; ++dy){
                if (dx || dy) CloseVectors[size++] = sf::Vector2i(dx,dy);
            }
        }


        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                VectorField[i*W + j] = sf::Vector2i(j,i);
                sf::RectangleShape& shape = Field[i][j].shape;
                shape = sf::RectangleShape(sf::Vector2f(cellSize,cellSize));
                shape.setFillColor(sf::Color::White);
                shape.setPosition(sf::Vector2f(space * j, space * i));
                Field[i][j].isRevealed = Field[i][j].isMarked = false;
            }
        }
    }



    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const sf::Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}
    inline Cell& get_cell(const sf::Vector2i& vc){return Field[vc.y][vc.x];}

    typedef sf::Vector2i(&array8)[8];
    const array8 get_CloseVectors(const sf::Vector2i& vc) const{
        sf::Vector2i ret[8];
        int size = 0;
        for( const sf::Vector2i& delta : CloseVectors)
            ret[size++] = vc+delta;
        return ret;
    }

    inline const Cell& get_cell_const(const sf::Vector2i& vc)const {return Field[vc.y][vc.x];}

    void initField(const sf::Vector2i& start){
        uint64_t seed = time(0);
        srand(seed);
        std::cout << "seed : " << seed << ", coords: " << start.x << ", " << start.y << std::endl;

        for( const sf::Vector2i& vc : VectorField)
            get_cell(vc).isBomb = (dist(start,vc) <= safe_dist) ? false : Roll(20);



        for( const sf::Vector2i& vc : VectorField){
            int bombs = 0;
            for( const sf::Vector2i& delta : CloseVectors){
                if (outOfBounds(vc+delta)) continue;
                if (get_cell(vc+delta).isBomb) ++bombs;
            }
            get_cell(vc).next_bombs2 = get_cell(vc).next_bombs = bombs;


        }
    }

    void reveal(const sf::Vector2i& start){
        if (outOfBounds(start)) return;
        if (!GameStarted){
            GameStarted = true;
            initField(start);
        }
        get_cell(start).shape.setFillColor( (get_cell(start).isBomb) ? sf::Color::Red : sf::Color::Green );
        get_cell(start).isRevealed = true;

        if (get_cell(start).next_bombs != 0) return;

        for ( const sf::Vector2i& vc : CloseVectors ){
            sf::Vector2i offseted = vc + start;
            if (outOfBounds(offseted)) continue;

            if (!get_cell(offseted).isRevealed)reveal(offseted);
        }




    }

    void mark(const sf::Vector2i& start){
        if (get_cell(start).isRevealed) return;
        get_cell(start).shape.setFillColor( (get_cell(start).isMarked ^= 1) ? sf::Color::Black : sf::Color::White);
    }

    void reveal_by_mouse(const sf::Vector2i& mousePos){


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            mark(mousePos / space);
        }else{
            reveal(mousePos / space);
        }

    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Text text;

        text.setFont(font); // font is a sf::Font
        text.setCharacterSize(textSize); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Red);

        for( const sf::Vector2i& vc : VectorField){
            target.draw(get_cell_const(vc).shape);
            if (get_cell_const(vc).isRevealed){
                text.setString(to_str(get_cell_const(vc).next_bombs));
                text.setPosition(space*vc.x, space*vc.y );
                target.draw(text);
            }


        }
    }
};


void ai_turn(Board& board){
    if(!board.GameStarted) return;

    for( const sf::Vector2i& vc : board.VectorField){
        if (!board.get_cell(vc).isRevealed) continue;

        int neighs = 0;
        int bombs_marked = 0;

        for( const sf::Vector2i& delta : board.CloseVectors){
            if (board.outOfBounds(vc + delta)) continue;
            if (!board.get_cell(vc + delta).isRevealed) ++neighs;
            if (board.get_cell(vc + delta).isMarked) ++bombs_marked;
        }


        if (board.get_cell(vc).next_bombs == bombs_marked){
            /// reveal all non-marked
            for( const sf::Vector2i& delta : board.CloseVectors){
                if (board.outOfBounds(vc + delta)) continue;
                if (!board.get_cell(vc + delta).isMarked) board.reveal(vc + delta);
            }
        }

        if (board.get_cell(vc).next_bombs == neighs){
            /// mark all that are non-marked
            for( const sf::Vector2i& delta : board.CloseVectors){
                if (board.outOfBounds(vc + delta)) continue;
                if (!board.get_cell(vc + delta).isMarked) board.mark(vc + delta);
            }
        }



    }

}




void mouseEvent(const sf::RenderWindow& rw, Board& b, sf::Event &event)
{

    if (event.mouseButton.button != sf::Mouse::Left) return;
    sf::Vector2i winpos = sf::Mouse::getPosition(rw);

    b.reveal_by_mouse(winpos);

}

int main()
{


    Board MainBoard;


    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    unsigned long ticks = 0;
    while (window.isOpen())
    {
        if ( (++ticks) % 30 == 0){
            std::cout << "ai goes" << std::endl;
            ai_turn(MainBoard);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                mouseEvent(window,MainBoard,event);
        }






        window.clear();

        window.draw(MainBoard);

        window.display();
    }

    return 0;
}
