#ifndef RIFFLLE_H
#define RIFFLE_H
#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include "rifle_ammo.hpp"

/**
 * Class for rifle type weapon.
 * Inherits basics and functionality from weapon-class.
 */
class Rifle: public Weapon
{
public:
    /**
     * Rifle constructor.
     *
     * Initializes the rifle sprite. Sets smoothing, origin, location and scaling.
     * @param weaponHolder Character holding the weapon.
     */
    Rifle(Character& weaponHolder) {
        _texture.loadFromFile("resource/sprites/rifle.png");
        _muzzleOffset.x = 693;
        _muzzleOffset.y = 75;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(250,98);
        _sprite.setScale(0.2,0.2);
        _sprite.setRotation(0);
        _isFlipped = false; // Texture was drawn facing right.
        updateLocation(weaponHolder);
    }
};

#endif
