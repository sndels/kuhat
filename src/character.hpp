#ifndef CHAR_H
#define CHAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

//The amount of tail to be cut from collisionmask
#define TAILEND 12
//How much overlap is allowed for Character sprites
#define OVERLAP 2

//class for the main logo, facilitates animation
class Character
{
public:
    Character (std::string t, int x, int y, bool turn = false) {
        _texture.loadFromFile(t);
        sf::Image temp;
        temp.loadFromFile(t);
        std::vector<bool> v;
        for (unsigned int i = 0; i < temp.getSize().x; ++i) {
            v.clear();
            for (unsigned int j = 0; j < temp.getSize().y; ++j) {
                if (i < TAILEND)
                    v.push_back(false);
                else if (temp.getPixel(i,j).a == 0)
                    v.push_back(false);
                else
                    v.push_back(true);
            }
            _mask.push_back(v);
        }
        _sprite.setTexture(_texture);
        _sprite.setPosition(x, y);
        _isFlipped = false; // Character is drawn facing right.
        _Grip.x = 17;
        _Grip.y = 15;
        if (turn == true) flip(); // Spawn the character facing left.
        _alive = true;
    }


    const sf::Sprite& getSprite() const {
        return _sprite;
    }

    sf::Vector2f getGripLocation() const {
        // Character sprites current global bounds and scale.
        sf::FloatRect loc = _sprite.getGlobalBounds();
        sf::Vector2f scale = _sprite.getScale();

        sf::Vector2f ret;
        // Grips y-axis coord is always y-location + y-scale*y-offset.
        ret.y = loc.top + scale.y*_Grip.y;

        if (!_isFlipped) {
            // Character is not flipped:
            // Grip x-axis coord is characters location + scale*offset.
            ret.x = loc.left + scale.x*_Grip.x;
        }
        else {
            // Character is flipped:
            // Grip x-axis coord is characters location + (width - scale*offset).
            ret.x = loc.left + loc.width - scale.x*_Grip.x;
        }

        return ret;
    }

    bool doesCollide(unsigned int x, unsigned int y) const {
        //Read mask from opposite side if sprite is flipped
        if (_isFlipped)
            x = _mask.size() - x - 1;
        if ((x + OVERLAP < _mask.size()) && (y + OVERLAP < _mask[x].size())) {
            return _mask[x + OVERLAP][y + OVERLAP];
        }
        return false;
    }

    void move(float x, float y) {
        // Change the sprite to face the x-axis moving direction.
        if ( x<0 && !_isFlipped ) flip();
        else if ( x>0 && _isFlipped) flip();
        _sprite.move(x,y);
        if (!onScreen()) {
            kill();
        }
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

    bool isCharFlipped() const {
        return _isFlipped;
    }
    void kill() {
        _alive = false;
    }
    bool isAlive() {
        return _alive;
    }
    bool onScreen() const {
        int x = getSprite().getPosition().x,
            y = getSprite().getPosition().y;
        if (y > 720
            || y < 0
            || x > 1280
            || x < 0) return false;
        return true;
    }


private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    std::vector<std::vector<bool> > _mask;
    bool _isFlipped;
    bool _alive;

    // Grip position i.e. The point on character where weapon origin is placed.
    // Defined as pixel offset from top left.
    sf::Vector2f _Grip;
};

#endif
