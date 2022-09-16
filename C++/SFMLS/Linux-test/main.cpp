



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
    const int size = 30;
    const int textSize = 20;
    const int space = 3;
    Cell Field[H][W];
    const double safe_dist = 3;
    bool GameStarted = false;

    bool autoZero = true;

    sf::Font font;

    Board(){

        if (!font.loadFromFile("Arial.ttf"))
        {
            std::cout << "font load error" << std::endl;
        }





        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                sf::RectangleShape& shape = Field[i][j].shape;
                shape = sf::RectangleShape(sf::Vector2f(size,size));
                shape.setFillColor(sf::Color::White);
                shape.setPosition(sf::Vector2f((size + space) * j, (size + space) * i));
                Field[i][j].isRevealed = Field[i][j].isMarked = false;
            }
        }
    }

    inline bool outOfBounds(int x, int y){ return (x < 0 || y < 0 || x >= W || y >= H);}

    void initField(int x, int y){
        uint64_t seed = time(0);
        srand(seed);
        std::cout << "seed : " << seed << ", coords: " << x << ", " << y << std::endl;

        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                double dist = sqrt(sqr(x - j) + sqr(y - i));
                if (dist <= safe_dist){
                    Field[i][j].isBomb = false;
                }else{
                    Field[i][j].isBomb = Roll(20);
                }
            }
        }

        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                int bombs = 0;
                for(int dx = -1; dx <= 1; ++dx){
                    for(int dy = -1; dy <= 1; ++dy){
                        if (outOfBounds(j+dx,i+dy)) continue;
                        if (Field[i+dy][j+dx].isBomb) ++bombs;
                    }
                }
                Field[i][j].next_bombs2 = Field[i][j].next_bombs = bombs;

            }
        }
    }

    void reveal(int x, int y){
        if (outOfBounds(x,y)) return; // out of bounds
        if (!GameStarted){
            GameStarted = true;
            initField(x,y);
        }

        if (Field[y][x].isBomb){
            Field[y][x].shape.setFillColor(sf::Color::Red);
        }else{
            Field[y][x].shape.setFillColor(sf::Color::Green);
        }
        Field[y][x].isRevealed = true;
        if (Field[y][x].next_bombs == 0){
            for(int dx = -1; dx <= 1; ++dx){
                for(int dy = -1; dy <= 1; ++dy){
                    if (!Field[y+dy][x+dx].isRevealed)reveal(x+dx,y+dy);
                }
            }
        }

    }

    void mark(int x,int y){
        if (Field[y][x].isRevealed) return;
        if (Field[y][x].isMarked ^= 1){
            Field[y][x].shape.setFillColor(sf::Color::Black);
        }else{
            Field[y][x].shape.setFillColor(sf::Color::White);
        }
    }

    void reveal_by_mouse(const sf::Vector2i mousePos){
        int _X = mousePos.x / (size + space);
        int _Y = mousePos.y / (size + space);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            mark(_X,_Y);
        }else{
            reveal(_X,_Y);
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

        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                target.draw(Field[i][j].shape);
                if (Field[i][j].isRevealed){
                    text.setString(to_str(Field[i][j].next_bombs));
                    text.setPosition((size + space)*j, (size + space)*i );
                    target.draw(text);
                }

            }
        }
    }
};



bool first_click = true;
void try_to_click(int x, int y){


}



int main()
{


    Board MainBoard;


    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i winpos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            MainBoard.reveal_by_mouse(winpos);
        }


        window.clear();

        window.draw(MainBoard);

        window.display();
    }

    return 0;
}
