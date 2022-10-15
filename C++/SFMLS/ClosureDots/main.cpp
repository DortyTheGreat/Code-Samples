


#define SFML_STATIC
#include <SFML/Graphics.hpp>

#define WIDTH 1200
#define HEIGHT 800

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


#include <cmath>
/*
inline double dist(const sf::Vector2i& vc1,const sf::Vector2i& vc2){
    return std::max((abs(vc1.x - vc2.x)),(abs(vc1.y - vc2.y)) );
}
*/

bool Roll(double percent){
    return (rand() % 1000 < percent*10);
}



#include <vector>


class Plane : public sf::Drawable{
public:
    std::vector<sf::Vector2i> dots;
    void add_dot(const sf::Vector2i& mousePos){


        dots.push_back(mousePos);

    }



private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        sf::CircleShape cs_(2);
        double max_ = -1;
        double min_ = 100000;

        for( int x = 0; x < WIDTH;x += 5){
            for( int y = 0; y < HEIGHT; y += 5){
                double summ_dist = 0;
                for(auto vc : dots){
                    summ_dist += dist(vc,{x,y});
                }
                max_ = std::max(max_,summ_dist);
            }

        }

        for( int x = 0; x < WIDTH;x += 5){
            for( int y = 0; y < HEIGHT; y += 5){
                double summ_dist = 0;
                double max_dist = -1;
                for(auto vc : dots){
                    summ_dist += dist(vc,{x,y});
                    max_dist = std::max(max_dist,dist(vc,{x,y}));
                }
                min_ = std::min(min_,max_dist);
            }

        }

        std::cout << max_ << std::endl;
        for( int x = 0; x < WIDTH;x += 5){
            for( int y = 0; y < HEIGHT; y += 5){
                double summ_dist = 0;
                double max_dist = -1;
                for(auto vc : dots){
                    summ_dist += dist(vc,{x,y});
                    max_dist = std::max(max_dist,dist(vc,{x,y}));
                }
                long long d = pow(max_dist - min_,2);

                cs_.setFillColor(sf::Color(0,d % 256,d % 256));
                cs_.setPosition({x,y});
                target.draw(cs_);
            }

        }




        sf::CircleShape cs(10);
        cs.setFillColor(sf::Color::Red);

        for( const sf::Vector2i& vc : dots){

            cs.setPosition(sf::Vector2f(vc));
            target.draw(cs);

        }
    }
};








void mouseEvent(const sf::RenderWindow& rw, Plane& b, sf::Event &event)
{

    if (event.mouseButton.button != sf::Mouse::Left) return;
    sf::Vector2i winpos = sf::Mouse::getPosition(rw);

    b.add_dot(winpos);

}

int main()
{


    Plane MainBoard;


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
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
