/// lovely BS: https://stackoverflow.com/questions/56978556/how-to-use-sfml-textures-as-static-data-members

class Player : public sf::Drawable
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

sf::Texture Player::m_texture;


