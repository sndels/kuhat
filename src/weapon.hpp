#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "character.hpp"

/**
 * A Virtual weapon class for different weapons to inherit from.
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
    void rotate(float angle) {
        _sprite.setRotation(90-angle);
    }

    /**
     * Updates the sprites location.
     * Called when the character holding the weapon has moved and the weapon
     * also needs to move.
     */
    virtual void updateLocation(const Character& weaponHolder) =0;

    /**
     * Returns weapons muzzle location.
     * Muzzle location is where projectiles are spawned.
     * @return Vector2f of coords
     */
    virtual sf::Vector2f getMuzzleLocation() =0;

    /**
     * Flips the weapon horizontally.
     *
     * NOTE: Currently flipping is done by reversing the sprites texture. Which
     * means that the same texture can't be used for many sprites to save memory,
     * because they will all be flipped.
     */
    void flip() {
        if (_isFlipped) {
            // Flip the texture on x-axis
            _sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().width, 0, -(_sprite.getTextureRect().width), _sprite.getTextureRect().height));
        }
        else {
            // Use normal texture
            _sprite.setTexture(_texture, true);
        }
        // Toggle flipped status
        _isFlipped ^= 1;
    }

protected:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isFlipped;
};

#endif
