#ifndef SHOTGUN_H
#define SHOTGUN_H
#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include "shotgun_ammo.hpp"

/**
 * Class for Shotgun type weapon.
 * Inherits basics and functionality from weapon-class.
 */
class Shotgun: public Weapon
{
public:
    /**
     * Shotgun constructor.
     *
     * Initializes the Shotgun sprite. Sets smoothing, origin, location and scaling.
     * @param weaponHolder Character holding the weapon.
     */
    Shotgun() {
        _texture.loadFromFile("resource/sprites/diyshotty.png");
        _muzzleOffset.x = 40;
        _muzzleOffset.y = 3;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(8,4);
        _sprite.setRotation(0);
        _isFlipped = false; // Texture was drawn facing right.
    }
};

#endif
