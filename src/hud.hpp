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

        _spriteWind.setTexture(_gradient);
        _spriteWind.setPosition(650,100);
        _spriteWind.setTextureRect(sf::IntRect(0,0,100,100));
        _spriteWind.setScale(0.5,0.5);
        _r.setSize(sf::Vector2f(300, 50));
        _r.setPosition(500, 100);
        _r.setOutlineThickness(2);
        _r.setOutlineColor(sf::Color::Black);

        _rotated = false;
    }

    void setState(float tCharge) {
        _spritePower.setTextureRect(sf::IntRect(0,0, tCharge * 500, _spritePower.getTextureRect().height));
    }
    void setWind(int wind) {
        _spriteWind.setTextureRect(sf::IntRect(0,0, 3 * wind, _spriteWind.getTextureRect().height));
        if ((wind < 0 && !_rotated) || (wind > 0 && _rotated)) {
            _spriteWind.scale(-1, 1);
            _rotated = !_rotated;
        }

    }

    void drawPower(sf::RenderWindow &window) const {
        window.draw(_spritePower);
    }
    void drawWind(sf::RenderWindow &window) const {
        window.draw(_r);
        window.draw(_spriteWind);
    }
private:
    sf::Texture _gradient;
    sf::Sprite _spritePower;
    sf::Sprite _spriteWind;
    sf::RectangleShape _r;
    bool _rotated;
};

#endif
