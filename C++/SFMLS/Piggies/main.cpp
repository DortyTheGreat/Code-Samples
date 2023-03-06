


#define SFML_STATIC
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




const int LIMIT = 4;
const int CUBE_SIDES = 6;
const int CUBE_SIDES_SQR = 36;

///double PP[LIMIT][LIMIT][LIMIT];

std::vector<std::vector<std::vector<double>>> PP;

double P(int M, int Op, int C);

double N(int M, int Op, int C);


/// P, когда C=0
double F(int M, int Op);

double F(int M, int Op){
    std::cout << "F: " << " " << M <<" " << Op << std::endl;
    double ret = 0;

    ret += N(M,Op,0);
    ret -= N(Op,M,0)/CUBE_SIDES;
    ret += ((double)(1)) / CUBE_SIDES;
    ret -= ((double)(1)) / CUBE_SIDES_SQR;
    return ret*CUBE_SIDES_SQR/(CUBE_SIDES_SQR-1);
}

double N(int M, int Op, int C){
    std::cout << "N: " << " " << M <<" " << Op <<" " << C << std::endl;
    return (P(M,Op,C+2)+P(M,Op,C+3)+P(M,Op,C+4)+P(M,Op,C+5)+P(M,Op,C+6))/CUBE_SIDES;

}


int c = 0;

double P(int M, int Op, int C){

    if (C + M >= LIMIT) return 1; /// просто забанкуй!
    if (PP[M][Op][C] > -0.5) return PP[M][Op][C]; /// Отмемоизируй!

    c++;
    std::cout << c << std::endl;
    std::cout << "P: " << " " << M <<" " << Op << " " << C << std::endl;

    if (C == 0) return F(M,Op); /// Хотя бы 1 бросок

    double bank_prob = 1 - F(Op,M+C);
    double roll_prob = N(M,Op,C) + (1 - F(Op,M))/6;

    return PP[M][Op][C] = std::max(bank_prob,roll_prob);
}

sf::Color bankColor = sf::Color::Yellow;
sf::Color turnColor = sf::Color::Green;


sf::Color COLOR_ON_COORD(int M, int Op, int C){
    if (C + M >= LIMIT) return bankColor; /// просто забанкуй!


    if (C == 0) return turnColor; /// Хотя бы 1 бросок

    double bank_prob = 1 - F(Op,M+C);
    double roll_prob = N(M,Op,C) + (1 - F(Op,M))/6;

    if (bank_prob > roll_prob){
        return bankColor;
    }else{
        return turnColor;
    }
}

class Cell{
public:
    unsigned long long age; /// 0 - empty
    sf::RectangleShape shape;
};



class Board :public sf::Drawable{
public:

    static const int H = LIMIT;
    static const int W = LIMIT;
    const int cellSize = 10;
    const int textSize = 20;
    const int space = 10 + 1;

    int SLIDE = 0;

    Cell Field[H][W];
    sf::Vector2i VectorField[H*W];

    sf::Color emptyColor = sf::Color::Green;
    sf::Color snakeColor = sf::Color::Black;
    sf::Color appleColor = sf::Color::Red;

    unsigned long long age = 0;
    unsigned int size = 1;
    bool isAlive = true;

    static sf::Font font;





    Board(){
        SLIDE = 0;

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


    }



    inline bool outOfBounds(int x, int y) const{ return (x < 0 || y < 0 || x >= W || y >= H);}
    inline bool outOfBounds(const sf::Vector2i& vc) const{ return (vc.x < 0 || vc.y < 0 || vc.x >= W || vc.y >= H);}
    inline Cell& get_cell(const sf::Vector2i& vc){return Field[vc.y][vc.x];}
    inline const Cell& get_cell_const(const sf::Vector2i& vc)const {return Field[vc.y][vc.x];}


    void next_slide(){
        SLIDE += 1;
        for(int i = 0;i < H; ++i){
            for(int j = 0; j < W; ++j){


                Field[i][j].shape.setFillColor(COLOR_ON_COORD(i,SLIDE,j));


            }
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


int main()
{
    std::cout << "main started" << std::endl;
    std::cout.flush();

    PP.resize(LIMIT);
    for(int i = 0;i < LIMIT; ++i){
        PP[i].resize(LIMIT);
        for(int j = 0;j < LIMIT; ++j){
            PP[i][j].resize(LIMIT);
            for(int k = 0;k < LIMIT; ++k){
                PP[i][j][k] = -1;
            }
        }
    }



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
            MainBoard.next_slide();
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
                /*
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
                    */

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
