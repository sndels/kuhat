#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <cmath>
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
    virtual const sf::Sprite& getSprite() {
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

    virtual float getAim() const{
        if (_isFlipped) {
            float rotation = _sprite.getRotation() -180;
            // Make sure the angle stays on range 0-360
            if (rotation < 0) rotation += 360;
            return rotation;
        }
        else return _sprite.getRotation();
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
        sf::Vector2f muzzleLocation;
        // Muzzles coords respect to local origin.
        // Multiply by scale to get difference in global coords.
        float x;
        float y = (_muzzleOffset.y -_sprite.getOrigin().y)*_sprite.getScale().y;
        // X depends on whether the texture is flipped.
        if (!_isFlipped) {
            x = (_muzzleOffset.x -_sprite.getOrigin().x)*_sprite.getScale().x;
        }
        else {
            x = (_sprite.getLocalBounds().width - _muzzleOffset.x - _sprite.getOrigin().x)*_sprite.getScale().x;
        }
        // Sprites rotation in radians.
        // 4*atan(1) = pi
        float a = _sprite.getRotation() *(4*atan(1)) /180;

        // Calculate the rotated coords.
        muzzleLocation.y = x*sin(a) + y*cos(a);
        muzzleLocation.x = x*cos(a) - y*sin(a);

        // Add sprites global coords to get muzzles final global coords.
        muzzleLocation += _sprite.getPosition();

        return muzzleLocation;
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
        // Correct the origin point
        _sprite.setOrigin(_sprite.getLocalBounds().width - _sprite.getOrigin().x , _sprite.getOrigin().y);
        // Correct the weapon angle
        _sprite.setRotation(-_sprite.getRotation() );
        // Toggle flipped status
        _isFlipped ^= 1;
    }

protected:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isFlipped;
    sf::Vector2f _muzzleOffset; // Coords in sprite image.
};

#endif
