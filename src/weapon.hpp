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
        _sprite.rotate(angle);
    }

    /**
     * Updates the sprites location.
     * Called when the character holding the weapon has moved and the weapon
     * also needs to move.
     */
    virtual void updateLocation(sf::Vector2f charPosition) =0;

    /**
     * Returns weapons muzzle location.
     * Muzzle location is where projectiles are spawned.
     * @return Vector2f of coords
     */
    virtual sf::Vector2f getMuzzleLocation() =0;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif
