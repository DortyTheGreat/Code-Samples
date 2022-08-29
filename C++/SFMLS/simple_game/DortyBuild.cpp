/*
---------------------
This File was Build Automatically by DortyBuild v 1.4.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

#include <SFML/Graphics.hpp>
#include "../../DortyLibs/DortyString.h"
#include "../../DortyLibs/DortyBuild.h"
#include "Classes/Enemy.cpp"
using namespace sf;
/**

TO-DO:
https://www.geeksforgeeks.org/p2ppeer-to-peer-file-sharing/
https://github.com/mitrapinaki/PeerToPeer

*/



int main()
{

    ///Enemy::m_texture.loadFromFile("image.png");
    Enemy::m_texture.loadFromFile("enemy.png");


    Enemy e1;

    AppBuild();




    RenderWindow window(VideoMode(800, 500), "SFML works!");
    window.setFramerateLimit(60);
    CircleShape shape(100.f);

    shape.setPosition(Vector2f(100,200));
    shape.setFillColor(Color(0,0,100));

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display


    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    int frames = 0;
    while (window.isOpen())
    {
        frames++;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        Vector2f movement(0,0);

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            movement += Vector2f(-1,0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            movement += Vector2f(1,0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            movement += Vector2f(0,-1);
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            movement += Vector2f(0,1);
        }

        movement *= 3.f;
        shape.move(movement);


        window.clear(Color(50,200,200));
        text.setString(to_str(frames));

        //window.setPosition(Vector2i(rand() % 200 - 100, rand() % 200 - 100));


        Vector2f centre_pos = shape.getPosition() + Vector2f(shape.getRadius(),shape.getRadius()); /// get_Position - левый угол
        window.setView(View(FloatRect(-800/2 + centre_pos.x,-500/2 + centre_pos.y,800, 500)));

        window.draw(shape);
        window.draw(e1);
        window.draw(text);
        window.display();
    }

    return 0;
}

*/
#include <SFML/Graphics.hpp>
#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}


  template <typename T>
  std::basic_string<T> reverse( std::basic_string<T> str){
    std::basic_string<T> ret = "";
    size_t sz = str.size();
    for(size_t i = 0;i < sz;i++){
        ret += str[sz - i -1];
    }
    return ret;
  }

#include <fstream>
/// lovely BS: https://stackoverflow.com/questions/56978556/how-to-use-sfml-textures-as-static-data-members

class Enemy : public sf::Drawable
{
public:
    static sf::Texture m_texture;

    Enemy(){
        m_sprite.setTexture(m_texture);
    }

    void Update(){

    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }
    sf::Sprite m_sprite;


};

sf::Texture Enemy::m_texture;



using namespace sf;
/**

TO-DO:
https://www.geeksforgeeks.org/p2ppeer-to-peer-file-sharing/
https://github.com/mitrapinaki/PeerToPeer

*/



int main()
{

    ///Enemy::m_texture.loadFromFile("image.png");
    Enemy::m_texture.loadFromFile("enemy.png");


    Enemy e1;

     




    RenderWindow window(VideoMode(800, 500), "SFML works!");
    window.setFramerateLimit(60);
    CircleShape shape(100.f);

    shape.setPosition(Vector2f(100,200));
    shape.setFillColor(Color(0,0,100));

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display


    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    int frames = 0;
    while (window.isOpen())
    {
        frames++;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        Vector2f movement(0,0);

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            movement += Vector2f(-1,0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            movement += Vector2f(1,0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            movement += Vector2f(0,-1);
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            movement += Vector2f(0,1);
        }

        movement *= 3.f;
        shape.move(movement);


        window.clear(Color(50,200,200));
        text.setString(to_str(frames));

        //window.setPosition(Vector2i(rand() % 200 - 100, rand() % 200 - 100));


        Vector2f centre_pos = shape.getPosition() + Vector2f(shape.getRadius(),shape.getRadius()); /// get_Position - левый угол
        window.setView(View(FloatRect(-800/2 + centre_pos.x,-500/2 + centre_pos.y,800, 500)));

        window.draw(shape);
        window.draw(e1);
        window.draw(text);
        window.display();
    }

    return 0;
}

