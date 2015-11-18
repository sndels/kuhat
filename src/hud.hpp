#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class Hud
{
public:
    Hud(std::string s) {
        _gradient.loadFromFile(s);
        _spritePower.setTexture(_gradient);
        _spritePower.setPosition(500,450);
        _spritePower.setTextureRect(sf::IntRect(0,0,0,100));
        _spritePower.setScale(0.5,0.5);
    }

    void setState(float tCharge) {
        _spritePower.setTextureRect(sf::IntRect(0,0, tCharge * 500, _spritePower.getTextureRect().height));
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(_spritePower);
    }
private:
    sf::Texture _gradient;
    sf::Sprite _spritePower;
};

#endif
