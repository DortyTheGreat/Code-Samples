#include "tcp_client.h"
#include "tcp_server.h"

#include <SFML/Graphics.hpp>
#include "Classes/Player.cpp"

#include "movement_handle.h"


#include "../../DortyLibs/DortyString.h"
///#include "../../DortyLibs/DortyBuild.h"
#include "Classes/Enemy.cpp"
using namespace sf;


#include <thread>

/**

TO-DO:
https://www.geeksforgeeks.org/p2ppeer-to-peer-file-sharing/
https://github.com/mitrapinaki/PeerToPeer

*/



Player Players[30];

const int TPS = 30;
void ServerLaunch()
{
    int ticks = 0;
    Server GameServer(100);
    RenderWindow window(VideoMode(600, 300), "Server-Side");
    window.setFramerateLimit(TPS);

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font


    /// Server-loop
    while(window.isOpen()){

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        text.setString(to_str(++ticks));
        window.clear(Color(50,200,200));
        window.draw(text);
        window.display();


        std::vector<std::pair<int,std::string> > responses = GameServer.process_updates();
        for(auto resp : responses){
            if (resp.first < 0){

            }
        }



    }
}


int main()
{
    std::thread first (ServerLaunch);
    ///AppBuild();
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


        Vector2f movement = get_key_movement();



        movement *= 3.f;
        shape.move(movement);


        window.clear(Color(50,200,200));
        text.setString(to_str(frames));

        //window.setPosition(Vector2i(rand() % 200 - 100, rand() % 200 - 100));


        ///Vector2f centre_pos = shape.getPosition() + Vector2f(shape.getRadius(),shape.getRadius()); /// get_Position - левый угол
        ///window.setView(View(FloatRect(-800/2 + centre_pos.x,-500/2 + centre_pos.y,800, 500)));

        window.draw(shape);
        window.draw(e1);
        window.draw(text);
        window.display();
    }

    return 0;
}
