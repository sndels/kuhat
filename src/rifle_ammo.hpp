#ifndef R_AMMO_H
#define R_AMMO_H

#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include <cmath>

class RifleAmmo: public Projectile
{
public:
    /**
     * RifleAmmo constructor
     *
     * Initializes a new ammo. Sets location and sprite.
     * Flight parameters are set to zero and changed on fire.
     */
    RifleAmmo () {
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
        _sprite.setScale(-0.02,0.02);
        //updateLocation();
    };

};

#endif
