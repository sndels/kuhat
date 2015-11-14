#ifndef CHAR_H
#define CHAR_H

#include <SFML/Graphics.hpp>
#include <string>

//class for the main logo, facilitates animation
class Character
{
public:
    Character (std::string t) {
        _texture.loadFromFile(t);
        _sprite.setTexture(_texture);
        _sprite.setPosition(820,350);
        _sprite.setScale(0.5,0.5);
    }

    sf::Sprite getSprite() const
    {
        return _sprite;
    }

    void move(float x, float y)
    {
        _sprite.move(x,y);
    }
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif
