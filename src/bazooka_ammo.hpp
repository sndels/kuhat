#ifndef B_AMMO_H
#define B_AMMO_H

#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include <cmath>

class BazookaAmmo: public Projectile
{
public:
    BazookaAmmo (sf::Vector2f location, float angle, int force):
    _location(location), _angle(angle), _force(force) {
        _texture.loadFromFile("resource/sprites/ammo.png");
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setPosition(_location);
        //updateLocation();
    };

    sf::Sprite getSprite() const
    {
        return _sprite;
    }

    sf::Time getAirTime() const
    {
        return _airtime.getElapsedTime();
    }

    virtual void updateLocation() {

        sf::Vector2f newPosition = getSprite().getPosition();
        newPosition.x = getX();
        newPosition.y = getY();
        _sprite.setPosition(newPosition);
    }


private:
    sf::Vector2f _location;
    float _angle;
    int _force;
    sf::Clock _airtime;
    sf::Texture _texture;
    sf::Sprite _sprite;


    float getX() {
        return _location.x + std::cos(_angle) * _force * getAirTime().asMilliseconds() / 1000;;
    }
    float getY() {
        return _location.y - std::sin(_angle) *_force * getAirTime().asMilliseconds() / 1000 + 0.5 * 9.81 * std::pow(getAirTime().asMilliseconds() / 1000, 2);
    }
};


#endif