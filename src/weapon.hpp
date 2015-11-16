#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "character.hpp"

/**
 * A Virtual weapon class.
 * Different weapons inherit basic functionality from this class.
 */
class Weapon
{
public:
    Weapon() { };

    /**
     * @return The weapons sprite.
     */
    virtual sf::Sprite getSprite() {
        return _sprite;
    }

    /**
     * @param angle Degrees to rotate the sprite.
     */
    virtual void rotate(float angle) {
        _sprite.setRotation(90-angle);
        // If the weapon is flipped, mirror the rotation.
        if (_isFlipped) _sprite.setRotation(-_sprite.getRotation() );
    }

    /**
     * Updates the sprites location.
     */
    virtual void updateLocation(const Character& weaponHolder) {
        _sprite.setPosition(weaponHolder.getGripLocation());

        // Make sure weapon is facing same direction as character.
        // Also corrct the angle if flip is needed.
        if (weaponHolder.isCharFlipped() != _isFlipped) {
            flip();
        }
    }

    /**
     * Returns weapons muzzle location.
     * Muzzle location is where projectiles are spawned.
     * @return Vector2f of coords
     */
    virtual sf::Vector2f getMuzzleLocation() {
        return _muzzleLocation;
    }

    /**
     * Flips the weapon horizontally.
     *
     * NOTE: Currently flipping is done by reversing the sprites texture. Which
     * means that the same texture can't be used for many sprites to save memory,
     * because they will all be flipped.
     */
    void flip() {
        if (!_isFlipped) {
            // Flip the texture on x-axis
            _sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().width, 0, -(_sprite.getTextureRect().width), _sprite.getTextureRect().height));
        }
        else {
            // Use normal texture
            _sprite.setTexture(_texture, true);
        }
        // Correct the weapon angle
        _sprite.setRotation(-_sprite.getRotation() );
        // Toggle flipped status
        _isFlipped ^= 1;
    }

protected:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isFlipped;
    sf::Vector2f _muzzleLocation;
};

#endif
