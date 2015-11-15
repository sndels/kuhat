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
        _sprite.setScale(-0.2,0.2);
        updateLocation(weaponHolder);
    }

    /**
     * @return The bazookas sprite.
     */
    sf::Sprite getSprite() {
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
     */
    void updateLocation(const Character& weaponHolder) {
        _sprite.setPosition(weaponHolder.getGripLocation());
    }

    sf::Vector2f getMuzzleLocation() {
        sf::Vector2f muzzleLocation;
        muzzleLocation.x = 30;
        muzzleLocation.y = 30;
        return muzzleLocation;
    }
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif
