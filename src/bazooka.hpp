#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka_ammo.hpp"

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
    Bazooka(sf::Vector2f charPosition): _angle(0) {
        _texture.loadFromFile("resource/sprites/bazooka.png");
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        updateLocation(charPosition);
        _sprite.setOrigin(280,135);
        _sprite.setScale(-0.2,0.2);
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
        _angle += angle;
    }

    float getAngle() const {
        return _angle;
    }

    /**
     * Updates the sprites location.
     */
    virtual void updateLocation(sf::Vector2f charPosition) {
        charPosition.x +=70;
        charPosition.y +=40;
        _sprite.setPosition(charPosition);
    }

    virtual sf::Vector2f getMuzzleLocation() {
        sf::Vector2f muzzleLocation;
        muzzleLocation.x = 30;
        muzzleLocation.y = 30;
        return muzzleLocation;
    }

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    float _angle;
};

#endif
