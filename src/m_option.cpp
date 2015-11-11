#include "m_option.hpp"

#define OPTHEIGHT 50 //height of texture
#define OPTWIDTH 250 //width of texture

/**
 * Sets the given file as texture and sets the sprite to "unselected"
 * @params: path for texture
 * @params: position in list
 * @return: none
 */
Option::Option(std::string texture, int position) {
    _texture.loadFromFile(texture);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, OPTWIDTH, OPTHEIGHT));
    _sprite.setPosition(220,150 + (position * 100));
}


/**
 * Sets the sprite as "selected"
 * @params: none
 * @return: none
 */
void Option::setSelected() {
    _sprite.setTextureRect(sf::IntRect(OPTWIDTH, 0, OPTWIDTH * 2, OPTHEIGHT));
}

/**
 * Sets the sprite as "unselected"
 * @params: none
 * @return: none
 */
void Option::setUnselected() {
    _sprite.setTextureRect(sf::IntRect(0, 0, OPTWIDTH, OPTHEIGHT));
}

/**
 * Returns the option sprite
 * @params: none
 * @return: sprite
 */
sf::Sprite Option::getSprite() {
    return _sprite;
}
