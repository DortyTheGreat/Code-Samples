



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
    int state;
    sf::RectangleShape shape;
};

class Board :public sf::Drawable{
public:

    static const int H = 20;
    static const int W = 30;
    const int cellSize = 30;
    const int textSize = 20;
    const int space = 33;
    const int connect_to_win = 5;
    int winning = 0;

    Cell Field[H][W];
    sf::Vector2i VectorField[H*W];

    const double safe_dist = 3;
    bool GameStarted = false;

    bool autoZero = true;
    bool turn = 0;
    static sf::Font font;

    Board(){


        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){
                VectorField[i*W + j] = sf::Vector2i(j,i);
                sf::RectangleShape& shape = Field[i][j].shape;
                shape = sf::RectangleShape(sf::Vector2f(cellSize,cellSize));
                shape.setFillColor(sf::Color::White);
                shape.setPosition(sf::Vector2f(space * j, space * i));
                Field[i][j].state = 0;
            }
        }
    }



    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const sf::Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}
    inline Cell& get_cell(const sf::Vector2i& vc){return Field[vc.y][vc.x];}
    inline const Cell& get_cell_const(const sf::Vector2i& vc)const {return Field[vc.y][vc.x];}




    void check_winstate(){
        for(int y=  0;y<H-connect_to_win+1;y++){
            for(int x = 0;x<W;x++){

                    int FirstValue = Field[y][x].state;
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int Y_ = 0; Y_ < connect_to_win;Y_++){
                            if (Field[y+Y_][x].state != FirstValue){
                                break;
                            }
                            if( (++counter) == connect_to_win){ winning = FirstValue;}
                        }
                    }


            }

        }

        ///„еккер √оризонтальных полосок
        for(int y=  0;y<H;y++){
            for(int x = 0;x<W-connect_to_win+1;x++){

                    int FirstValue = Field[y][x].state;
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_ = 0; X_ < connect_to_win;X_++){
                            if (Field[y][x+X_].state != FirstValue){
                                break;
                            }
                            if( (++counter) == connect_to_win){ winning = FirstValue;}
                        }

                    }

            }

        }

        ///„еккер ƒиаг (\) полосок
        for(int y=  0;y<H-connect_to_win+1;y++){
            for(int x = 0;x<W-connect_to_win+1;x++){

                    int FirstValue = Field[y][x].state;
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_Y = 0; X_Y < connect_to_win;X_Y++){


                            if (Field[y+X_Y][x+X_Y].state != FirstValue){
                                break;
                            }
                            if( (++counter) == connect_to_win){ winning = FirstValue;}
                        }

                    }

            }

        }

        ///„еккер ƒиаг (/) полосок
        for(int y=  0;y<H-connect_to_win+1;y++){
            for(int x = connect_to_win-1;x<W;x++){

                    int FirstValue = Field[y][x].state;
                    int counter = 0;

                    if (FirstValue != 0){
                        for(int X_Y = 0; X_Y < connect_to_win;X_Y++){


                            if (Field[y+X_Y][x-X_Y].state != FirstValue){
                                break;
                            }
                            if( (++counter) == connect_to_win){ winning = FirstValue;}
                        }

                    }


            }

        }
    }


    void reveal(const sf::Vector2i& start){
        if (outOfBounds(start)) return;
        if (get_cell(start).state != 0) return;
        turn ^= 1;
        get_cell(start).state = turn*2 - 1;
        check_winstate();
    }



    void reveal_by_mouse(const sf::Vector2i& mousePos){


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        }else{
            reveal(mousePos / space);
        }

    }

    std::string num_to_str(int n) const{
        if (n == -1){return "Nolik";}
        if (n == 1){return "Krestik";}
        return "WTF";
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Text text;

        text.setFont(font); // font is a sf::Font

        if (winning != 0){
            text.setCharacterSize(textSize * 5);
            text.setString(num_to_str(winning) + "Win");
            target.draw(text);
            return;
        }
        text.setCharacterSize(textSize); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Red);

        for( const sf::Vector2i& vc : VectorField){
            target.draw(get_cell_const(vc).shape);
            if (get_cell_const(vc).state != 0){
                if (get_cell_const(vc).state == 1){text.setString('X');}
                if (get_cell_const(vc).state == -1){text.setString('0');}
                text.setPosition(space*vc.x, space*vc.y );
                target.draw(text);
            }


        }
    }
};

sf::Font Board::font;







void mouseEvent(const sf::RenderWindow& rw, Board& b, sf::Event &event)
{

    if (event.mouseButton.button != sf::Mouse::Left) return;
    sf::Vector2i winpos = sf::Mouse::getPosition(rw);

    b.reveal_by_mouse(winpos);

}

int main()
{
    if (!Board::font.loadFromFile("Arial.ttf"))
    {
        std::cout << "font load error" << std::endl;
    }

    Board MainBoard;


    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    window.setFramerateLimit(30);
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( int(event.type) ){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mouseEvent(window,MainBoard,event);
                    break;
            }
        }






        window.clear();

        window.draw(MainBoard);

        window.display();
    }

    return 0;
}
