#ifndef CHAR_H
#define CHAR_H

#include <SFML/Graphics.hpp>
#include <string>

//class for the main logo, facilitates animation
class Character
{
public:
    Character (std::string t) {
        _texture.loadFromFile(t);
        _sprite.setTexture(_texture);
        _sprite.setPosition(820,350);
        _sprite.setScale(0.5,0.5);
        _isFlipped = false; // Characters are drawn facing left.
    }

    sf::Sprite getSprite() {
        return _sprite;
    }

    void move(float x, float y) {
        // Change the sprite to face the x-axis moving direction.
        if ( x<0 && _isFlipped == true ) flip();
        else if ( x>0 && _isFlipped == false) flip();
        _sprite.move(x,y);
    }

    bool isSpriteFlipped() {
        return _isFlipped;
    }

    /**
     * Flips the character horizontally.
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
        // Toggle flipped status
        _isFlipped ^= 1;
    }

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isFlipped;
};

#endif
