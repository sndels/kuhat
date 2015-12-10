#ifndef B_AMMO_H
#define B_AMMO_H

#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include <vector>
#include <cmath>

/**
 * Class for the bazooka projectile.
 * Inherits basics and functionality from projectile-class.
 */
class BazookaAmmo: public Projectile
{
public:
    /**
     * Constructor sets location, sprite and collision mask.
     * Flight parameters are set to zero and changed on fire.
     */
    BazookaAmmo () {
        _location = sf::Vector2f(0,0);
        _angle = 0;
        _velocity = 0;
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
};

#endif
