#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

/**
 * Class for the wind and shot power indicators
 */
class Hud
{
public:
    /**
     * Constructor sets indicators and their positions
     */
    Hud(std::string s) {
        _gradient.loadFromFile(s);
        _spritePower.setTexture(_gradient);
        _spritePower.setPosition(480,650);
        _spritePower.setTextureRect(sf::IntRect(0,0,0,100));
        _spritePower.setScale(0.40,0.5);

        _spriteWind.setTexture(_gradient);
        _spriteWind.setPosition(630,600);
        _spriteWind.setTextureRect(sf::IntRect(0,0,100,100));
        _spriteWind.setScale(0.5,0.5);
        _r.setSize(sf::Vector2f(300, 50));
        _r.setPosition(480, 600);
        _r.setOutlineThickness(2);
        _r.setOutlineColor(sf::Color::Black);

        _rotated = false;
    }

    /**
     * Sets charge amount
     * @param tCharge how much power has been charged
     */
    void setState(float tCharge) {
        _spritePower.setTextureRect(sf::IntRect(0,0, tCharge * 500, _spritePower.getTextureRect().height));
    }
    /**
     * Sets wind amount
     * @param wind wind speed
     */
    void setWind(int wind) {
        _spriteWind.setTextureRect(sf::IntRect(0,0, 3 * wind, _spriteWind.getTextureRect().height));
        if ((wind < 0 && !_rotated) || (wind > 0 && _rotated)) {
            _spriteWind.scale(-1, 1);
            _rotated = !_rotated;
        }

    }

    /**
     * Draws the shot power indicator
     * @param window render window
     */
    void drawPower(sf::RenderWindow &window) const {
        window.draw(_spritePower);
    }
    /**
     * Draws the wind indicator
     * @param window render window
     */
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
