#ifndef BAZOOKA_H
#define BAZOOKA_H
#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka_ammo.hpp"

/**
 * Class for bazooka type weapon.
 * Inherits basics and functionality from weapon-class.
 */
class Bazooka: public Weapon
{
public:
    /**
     * Bazooka constructor.
     *
     * Initializes the bazooka sprite. Sets smoothing, origin, location and scaling.
     * @param weaponHolder Character holding the weapon.
     */
    Bazooka(Character& weaponHolder) {
        _texture.loadFromFile("resource/sprites/bazooka.png");
        _muzzleOffset.x = 570;
        _muzzleOffset.y = 105;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(280,135);
        _sprite.setScale(0.2,0.2);
        _sprite.setRotation(0);
        _isFlipped = false; // Texture was drawn facing right.
        updateLocation(weaponHolder);
    }
};

#endif
