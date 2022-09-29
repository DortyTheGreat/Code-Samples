


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

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

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


    SlingShot MainShot;


    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    window.setFramerateLimit(120);
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
                MainShot.Relocate(sf::Vector2f(sf::Mouse::getPosition(window)));
                break;



            case sf::Event::MouseButtonPressed:
                MainShot.release();
                break;

            }

        }


        MainShot.Update(0.1);
        window.clear();
        window.draw(MainShot);
        window.display();
    }

    return 0;
}
