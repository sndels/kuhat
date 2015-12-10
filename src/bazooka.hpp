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
     * Constructor sets the bazooka sprite. Sets smoothing, origin, location and scaling.
     */
    Bazooka() {
        _texture.loadFromFile("resource/sprites/diysinko.png");
        _muzzleOffset.x = 35;
        _muzzleOffset.y = 5;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(16,7);
        _sprite.setRotation(0);
        _isFlipped = false; // Texture was drawn facing right.
    }
};

#endif
