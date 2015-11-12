#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "character.hpp"

class Character;

/*
    TODO: Character needs to update the weapon it's holding
 */

/**
 * A Virtual weapon class for different weapons to inherit from.
 */
class Weapon
{
public:
    /**
     * Weapon constructor.
     *
     * Initializes the weapon sprite. Sets smoothing, origin, location and scaling.
     * @param filename     Filename for Texture.
     * @param weaponHolder Character holding the weapon.
     */
	Weapon (std::string filename, Character& weaponHolder):
        _weaponHolder(weaponHolder) {
		_texture.loadFromFile(filename);
        _texture.setSmooth(true);
		_sprite.setTexture(_texture);
        updateLocation();
        _sprite.setOrigin(280,135);
    	_sprite.setScale(-0.2,0.2);
	}

	sf::Sprite getSprite() const
	{
		return _sprite;
	}

    /**
     * Rotates the weapon sprite.
     * @param angle Degrees to rotate the sprite.
     */
	void rotate(float angle)
	{
		_sprite.rotate(angle);
	}

    void updateLocation() {
        sf::Vector2f newPosition = _weaponHolder.getSprite().getPosition();
        newPosition.x +=70;
        newPosition.y +=40;
        _sprite.setPosition(newPosition);

    }
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
    Character& _weaponHolder; //!< The character holding the weapon
};

#endif
