#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"

/**
 * Class for bazooka type weapon.
 * Inherits basics from weapon-class.
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
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(280,135);
        _sprite.setScale(0.2,0.2);
        _sprite.setRotation(0);
        _isFlipped = true; // Texture was drawn facing left.
        updateLocation(weaponHolder);
        flip();
    }

    /**
     * @return The bazookas sprite.
     */
    sf::Sprite getSprite() {
        return _sprite;
    }

    /**
     * Updates the sprites location.
     */
    void updateLocation(const Character& weaponHolder) {
        _sprite.setPosition(weaponHolder.getGripLocation());

        // Make sure weapon is facing same direction as character.
        // Also corrct the angle if flip is needed.
        if (weaponHolder.isCharFlipped() != _isFlipped) {
            flip();
        }
    }

    sf::Vector2f getMuzzleLocation() {
        sf::Vector2f muzzleLocation;
        muzzleLocation.x = 30;
        muzzleLocation.y = 30;
        return muzzleLocation;
    }
};

#endif
