#ifndef M_OPTION_H
#define M_OPTION_H

#include "game.hpp"

#define OPTHEIGHT 50 //height of texture
#define OPTWIDTH 250 //width of texture

/**
 * Generic menu option. This will probably be a virtual class from which functional
 * menu items inherit from.
 */

class Option {
public:
    /**
     * Sets the given file as texture and sets the sprite to "unselected"
     * @param path for texture
     * @param position in list
     */
    Option(std::string texture, int position) {
        _texture.loadFromFile(texture);
        _sprite.setTexture(_texture);
        _sprite.setTextureRect(sf::IntRect(0, 0, OPTWIDTH, OPTHEIGHT));
        _sprite.setPosition(220,150 + (position * 100));
    }

    /**
     * Sets the sprite as "selected"
     */
    void setSelected() {
        _sprite.setTextureRect(sf::IntRect(OPTWIDTH, 0, OPTWIDTH * 2, OPTHEIGHT));
    }

    /**
     * Sets the sprite as "unselected"
     */
    void setUnselected() {
        _sprite.setTextureRect(sf::IntRect(0, 0, OPTWIDTH, OPTHEIGHT));
    }

    /**
     * Returns the option sprite
     * @return the option sprite
     */
    sf::Sprite getSprite() {
        return _sprite;
    }
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};


#endif
