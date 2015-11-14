#ifndef B_AMMO_H
#define B_AMMO_H

#define PI 3.14 // For calculating projectile flight

#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include <cmath>

class BazookaAmmo: public Projectile
{
public:
    /**
     * BazookaAmmo constructor
     *
     * Initializes a new ammo. Sets location and sprite.
     * Flight parameters are set to zero and changed on fire.
     */
    BazookaAmmo ():_location(0,0), _angle(0), _velocity(0), _shot(false) {
        _texture.loadFromFile("resource/sprites/ammo.png");
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setPosition(_location);
        _sprite.setScale(-0.5,0.5);
        //updateLocation();
    };
    /**
     * @return the ammo sprite
     */
    sf::Sprite getSprite()
    {
        return _sprite;
    }
    /**
     * @return the time since firing
     */
    sf::Time getAirTime() const
    {
        return _airtime.getElapsedTime();
    }
    /**
     * Gets current location during flight
     */
    virtual void updateLocation() {
        if (_shot) {
            _sprite.setPosition(getX(), getY());
        }
    }
    /**
     * @return Whether ammo has been shot
     */
    bool shot() {
        return _shot;
    }
    /**
     * Fires the projectile
     * @param location Current weapon location
     * @param angle Weapon angle
     * @param velocity Initial velocity of the ammo
     */
    void fire(sf::Vector2f location, float angle, int velocity) {
        _location = location;
        _angle = angle;
        _velocity = velocity;
        _airtime.restart();
        _shot = true;
    }

private:
    sf::Vector2f _location;
    float _angle;
    int _velocity;
    sf::Clock _airtime;
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _shot;

    /**
     * Get X coordinate on fire
     * @return horizontal coordinate
     */
    float getX() {
        return _location.x + std::cos((180-_angle)*PI/180) * _velocity * (getAirTime().asMilliseconds() / 1000.0);
    }
    /**
     * Get Y coordinate on fire
     * @return vertical coordinate
     */
    float getY() {
        return _location.y - std::sin((180-_angle)*PI/180) *_velocity * (getAirTime().asMilliseconds() / 1000.0) + 0.5 * 999.81 * std::pow(getAirTime().asMilliseconds() / 1000.0, 2);
    }
};

#endif