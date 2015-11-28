#ifndef B_AMMO_H
#define B_AMMO_H

#define PI 3.14 // For calculating projectile flight
#define GRAVITY 900
#define WIND 0

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
        _sprite.setOrigin(32,32);
        _sprite.setScale(-0.2,0.2);
        //updateLocation();
    };
    /**
     * @return the ammo sprite
     */
    const sf::Sprite& getSprite() const {
        return _sprite;
    }
    /**
     * @return the time since firing
     */
    sf::Time getAirTime() const {
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
    bool shot() const {
        return _shot;
    }
    /**
     * Destroys the projectile
     */
    void destroy() {
        _shot=false;
    }
    /**
     * Fires the projectile
     * @param location Current weapon location
     * @param angle Weapon angle
     * @param velocity Initial velocity of the ammo
     */
    void fire(sf::Vector2f location, float angle, int velocity, int wind) {
        _location = location;
        _angle = angle;
        _velocity = velocity;
        _airtime.restart();
        _shot = true;
    }
    /**
     * @return ammo horizontal coordinate
     */
    float getX() const {
        return _location.x - std::cos((180-_angle)*PI/180) * _velocity * getAirTime().asSeconds() - getWind();
    }
    /**
     * @return ammo vertical coordinate
     */

    float getY() const {
        return _location.y + std::sin((180-_angle)*PI/180) *_velocity * getAirTime().asSeconds() + 0.5 * GRAVITY * std::pow(getAirTime().asSeconds(), 2);
    }
    /**
     * Checks if the ammo has left the screen. NOTE: going above the screen
     * does not count as leaving the screen as ammo falling back is a desired
     *  feature.
     * @return Whether ammo is still on screen.
     */
    bool onScreen() const {
        if (getY() > 720 || getX() > 1280 || getX() < 0)
            return false;
        else return true;
    }

private:

    float getWind() const {
        return std::pow(getAirTime().asSeconds(), 2) * WIND;
    }

    sf::Vector2f _location;
    float _angle;
    int _velocity;
    sf::Clock _airtime;
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _shot;

};

#endif
