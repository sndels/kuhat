#ifndef B_AMMO_H
#define B_AMMO_H

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
    BazookaAmmo () {
        _location.x = 0;
        _location.y = 0;
        _angle = 0;
        _velocity = 0;
        _shot = false;
        _texture.loadFromFile("resource/sprites/ammo.png");
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setPosition(_location);
        _sprite.setOrigin(32,32);
        _sprite.setScale(-0.2,0.2);
        //updateLocation();
    };

};

#endif
