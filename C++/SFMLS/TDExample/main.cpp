

#include <SFML/Graphics.hpp>
#include <functional>
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

template<typename vc>
inline double dist(const vc& vc1,const vc& vc2){
    return sqrt(sqr(vc1.x - vc2.x) + sqr(vc1.y - vc2.y) );
}

bool Roll(double percent){
    return (rand() % 1000 < percent*10);
}


bool collision(const sf::CircleShape& s1, const sf::CircleShape& s2){
    return dist(s1.getPosition(),s2.getPosition()) <= s1.getRadius() + s2.getRadius();
}


class Enemy;
class Projectile;
class Game{
};


class Enemy : public sf::CircleShape{
    float speed = 30;
    double Hp = 1;

    sf::CircleShape sp = sf::CircleShape(10);

    std::function<void()>* OnDeath;
    //std::function<int(int)>* OnDeath;

public:

    void update(float time){
        sp.setPosition( sp.getPosition() + sf::Vector2f(0.1, 1)* time * speed );

    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sp);
    }
};

class Projectile{
    sf::CircleShape sprite = sf::CircleShape(2);

    Projectile(){
        sprite.setFillColor(sf::Color::Red);
    }
};



class Tower{
    float FireRate = 1; /// lower -> more shoots
    float reloading = 0;

    float attack_radius = 100;

    sf::CircleShape tower_sprite = sf::CircleShape(5);



    void update(double time, const Game& gm){
        if ((reloading += time) >= FireRate){ Shoot(gm); }
    }

    void Shoot(const Game& gm){
        sf::CircleShape Attack_sprite = tower_sprite;
        Attack_sprite.setRadius(attack_radius);

        for(const auto& e: gm.enemies){
            if (collision(e,Attack_sprite)){
                reloading = 0;
                create_projectile();
                break;
            }
        }
    }
};

class Game : public sf::CircleShape{
public:
    std::vector<Enemy> enemies;
    int frames = 0;

    void update(double time){

        if (++frames % 30 == 0){
            enemies.push_back(Enemy());
        }

        for(auto& e: enemies){
            e.update(1.f/30.f);
        }
    }

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(auto& e: enemies){
            target.draw(e);
        }
    }



};

void mouseEvent(const sf::RenderWindow& rw, sf::Event &event)
{

    if (event.mouseButton.button != sf::Mouse::Left) return;
    sf::Vector2i winpos = sf::Mouse::getPosition(rw);

    //b.reveal_by_mouse(winpos);

}

int main()
{
    /*
    if (!Board::font.loadFromFile("Arial.ttf"))
    {
        std::cout << "font load error" << std::endl;
    }
    */



    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    window.setFramerateLimit(30);

    Game gm;

    while (window.isOpen())
    {

        gm.update(1.f/30.f);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( int(event.type) ){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    //mouseEvent(window,MainBoard,event);
                    break;
            }
        }






        window.clear();

        window.draw(gm);

        window.display();
    }

    return 0;
}
