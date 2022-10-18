

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <ctime>
#include <cmath>
#include <iostream>




sf::Vector2f keyboard_status(){
    sf::Vector2f ret = {0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ret.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ret.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ret.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ret.y += 1;

    return ret;
}

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




sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length == 0) return source;
    return sf::Vector2f(source.x / length, source.y / length);

}

#include <cmath>
const auto PI = acos( -1 );

/*
 * Converts degrees to radian
 */
template <typename T>
inline double degToRad( T degree )
{
    return degree / 180.0 * PI;
}


/*
 * Returns a vector rotated with a given angle in degrees
 */
template <typename T>
inline T getRotated( const T& vec, double angle )
{
    const double angleRad = degToRad( -angle );
    const double newX     = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
    const double newY     = vec.x * sin( angleRad ) + vec.y * cos( angleRad );

    return T( newX, newY );
}

class PhysicsObject : public sf::Drawable{
public:
    float mass;
    sf::Vector2f Speed;
    sf::Vector2f Acceleration;
    sf::RectangleShape rect;
    /// Отрабатывает обмен скоростями в соответствии с ЗСЭ и ЗСИ
    void collide(PhysicsObject& other){

    }

    /// Перемещает по оси вращения
    void move(float dist){
        rect.move(dist * getRotated(sf::Vector2f(0,1),-rect.getRotation() ));
    }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(rect);
    }
};

class Projectile : PhysicsObject{

};

class Game;
class Projectile;

class Game{
    static std::vector<Projectile> objects;

    static void mk_projectile(){
        objects.push_back(PhysicsObject());
    }
};



class Player : PhysicsObject{

    float Energy = 100;
    float MaxEnergy = 1000;
    float EnergyGain = 10;


    void fire(){

        if (Energy > 50){
            Energy -= 50;
            Game::mk_projectile(rect.getRotation());
        }

    }

};


class Bird{
public:
    sf::CircleShape shape;
    sf::Vector2f Gravity;
    sf::Vector2f Velocity;

    float Radius = 30;
    sf::Vector2f R;

    Bird(){
        shape.setRadius(Radius);
        shape.setFillColor(sf::Color::Red);
        Gravity = sf::Vector2f(0,9.8);

         R = sf::Vector2f(Radius,Radius);
    }



    inline void setPosition(const sf::Vector2f& vc){
        shape.setPosition(vc);
    }

    inline sf::Vector2f getPosition() const{
        return shape.getPosition();
    }

    inline void move(const sf::Vector2f& vc){
        setPosition(getPosition() + vc);
    }

    void Update(float dt){
        move(Velocity * dt);
        Velocity += Gravity * dt;
    }


};

class SlingShot : public sf::Drawable{
public:
    sf::Vector2f Centre;
    Bird bird;
    sf::Vector2f delta;
    bool released = false;


    float delta_len;

    float dist = 100;





    SlingShot(){

        Centre = {300,400};

    }

    void Relocate(const sf::Vector2f& new_pos){
        if (released) return;
        delta = (new_pos - Centre);
        delta_len = sqrt(sqr(delta.x) + sqr(delta.y));
        if (delta_len > dist){
            delta = delta * (dist/delta_len);
            delta_len = dist;
        }
        bird.setPosition(Centre + delta - bird.R);
    }

    float Speed(float length) const{
        return length*0.01;
    }

    void release(){
        if (! (released ^= 1)){
            Centre = bird.getPosition() + bird.R;
        }

    }

    void Update(float dt = 0.3){
        if (released){bird.Update(dt); return;}
        bird.Velocity = -delta * Speed(delta_len);

    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(bird.shape);
        sf::CircleShape Sling(10);
        Sling.setFillColor(sf::Color::White);
        Sling.setPosition(Centre);
        target.draw(Sling);

        sf::CircleShape Path(5);
        Path.setFillColor(sf::Color::Blue);


        for(float time = 0; time < 5;time += 0.3){
            Path.setPosition(bird.getPosition() + bird.R + bird.Velocity * time + bird.Gravity * sqr(time)/2.0f );
            target.draw(Path);
        }

    }



};


int main()
{





    PhysicsObject SpaceShip;
    SpaceShip.rect.setFillColor(sf::Color::Red);
    SpaceShip.rect.setSize({10,50});
    SpaceShip.rect.setPosition({100,100});

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    window.setFramerateLimit(30);
    unsigned long ticks = 0;
    while (window.isOpen())
    {
        if ( (++ticks) % 30 == 0){
            ///std::cout << "ai goes" << std::endl;
            ///ai_turn(MainBoard);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( int(event.type) ){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:

                break;

            // key pressed
            case sf::Event::KeyPressed:

                switch ( int(event.key.code) ){

                }

                break;

            case sf::Event::MouseButtonPressed:

                break;

            }

        }

        auto k = keyboard_status();
        SpaceShip.rect.rotate(k.x * 7.0f);
        SpaceShip.move(k.y * 5.0f);
        window.clear();
        window.draw(SpaceShip);
        window.display();
    }

    return 0;
}
