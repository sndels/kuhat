#ifndef S_AMMO_H
#define S_AMMO_H

#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include <vector>
#include <cmath>
#define VELOCITY 2000;

class ShotgunAmmo: public Projectile
{
public:
    /**
     * ShotgunAmmo constructor
     *
     * Initializes a new ammo. Sets location, sprite and velocity.
     * Flight parameters are set to zero and changed on fire.
     */
    ShotgunAmmo () {
        _velocity = VELOCITY;
        _location = sf::Vector2f(0,0);
        _angle = 0;
        _shot = false;
        _texture.loadFromFile("resource/sprites/kuula.png");
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setPosition(_location);
        _sprite.setOrigin(4,4);
        //updateLocation();
        sf::Image temp;
        temp.loadFromFile("resource/sprites/kuula.png");
        std::vector<bool> v;
        for (unsigned int i = 0; i < temp.getSize().x; ++i) {
            v.clear();
            for (unsigned int  j = 0; j < temp.getSize().y; ++j) {
                if (temp.getPixel(i,j).a == 0)
                    v.push_back(false);
                else
                    v.push_back(true);
            }
            _mask.push_back(v);
        }
    };

    /**
     * Fires the projectile, disregards wind and velocity
     * @param location Current weapon location
     * @param Weapon angle
     *
     */
    void fireShotty(sf::Vector2f location, float angle) {
        _location = location;
        _angle = angle;
        _airtime.restart();
        _shot = true;
    }

    /**
     * Checks if the ammo has left the screen. NOTE: with shotgun going above the screen
     * counts as leaving the screen.
     * @return Whether ammo is still on screen.
     */
    bool onScreen() const {
        if (getY() > 720 || getX() > 1280 || getX() < 0 || getY() < 0)
            return false;
        else return true;
    }

    /**
     * Is not affected by wind
     * @return ammo horizontal coordinate
     */

    float getX() const {
        return _location.x - std::cos((180-_angle)*PI/180) * _velocity * getAirTime().asSeconds();
    }


    /**
     * Is not affected by gravity
     * @return ammo vertical coordinate
     */

    float getY() const {
        return _location.y + std::sin((180-_angle)*PI/180) *_velocity * getAirTime().asSeconds() + 0.5 * std::pow(getAirTime().asSeconds(), 2);
    }

};

#endif
