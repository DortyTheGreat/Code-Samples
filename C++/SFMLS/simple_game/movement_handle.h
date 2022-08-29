
sf::Vector2f get_key_movement(){
    sf::Vector2f movement(0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movement += sf::Vector2f(-1,0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movement += sf::Vector2f(1,0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movement += sf::Vector2f(0,-1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        movement += sf::Vector2f(0,1);
    }
    return movement;
}

