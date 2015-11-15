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
        _isFlipped = true; // Characters are drawn facing left.
        _Grip.x = 125;
        _Grip.y = 86;
    }

    sf::Sprite getSprite() {
        return _sprite;
    }

    sf::Vector2f getGripLocation() const {
        // Character sprites current global bounds and scale.
        sf::FloatRect loc = _sprite.getGlobalBounds();
        sf::Vector2f scale = _sprite.getScale();

        sf::Vector2f ret;
        // Grips y-axis coord is always y-location + y-scale*y-offset.
        ret.y = loc.top + scale.y*_Grip.y;

        if (_isFlipped) {
            // Character is flipped:
            // Grip x-axis coord is characters location + scale*offset.
            ret.x = loc.left + scale.x*_Grip.x;
        }
        else {
            // Character is not flipped:
            // Grip x-axis coord is characters location + (width - scale*offset).
            ret.x = loc.left + loc.width - scale.x*_Grip.x;
        }

        return ret;
    }

    void move(float x, float y) {
        // Change the sprite to face the x-axis moving direction.
        if ( x<0 && !_isFlipped ) flip();
        else if ( x>0 && _isFlipped) flip();
        _sprite.move(x,y);
    }

    /**
     * Flips the character horizontally.
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

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isFlipped;

    // Grip position i.e. The point on character where weapon origin is placed.
    // Defined as pixel offset from top left.
    sf::Vector2f _Grip;
};

#endif
