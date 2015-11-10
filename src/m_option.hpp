#ifndef M_OPTION_H
#define M_OPTION_H

#include "game.hpp"

/*
 * Generic menu option. This will probably be a virtual class from which functional
 * menu items inherit from.
 */

class Option {
public:
    Option(std::string texture, int position);
    void setSelected();
    void setUnselected();
    sf::Sprite getSprite();
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};


#endif
