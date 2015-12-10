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

/**
 * Class for playable character.
 * Handles all calls to character manipulation and collision checks.
 */
class Character
{
public:
    /**
     * Constructor sets sprite, collision mask, initial position,
     * team color and grip location.
     * @param t    texture path
     * @param x    x-coordinate for character spawn
     * @param y    y-coordinate for character spawn
     * @param turn "turned" state
     * @param team team number
     * @param health base health for character
     */
    Character (std::string t, int x, int y, bool turn = false, int team = 0, int health = 100) {
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
        switch (team) {
            case 0:
                break;
            case 1:
                _sprite.setColor(sf::Color::Red);
                break;
            case 2:
                _sprite.setColor(sf::Color::Magenta);
                break;
            case 3:
                _sprite.setColor(sf::Color::Green);
                break;
        }
        _sprite.setPosition(x, y);
        _sprite.setOrigin(temp.getSize().x/2, temp.getSize().y/2);
        _isFlipped = false; // Character is drawn facing right.
        _Grip.x = 17;
        _Grip.y = 15;
        if (turn == true) flip(); // Spawn the character facing left.
        _health = health;
        _maxhealth = health;
        _alive = true;
        _healthBar.setSize(sf::Vector2f(30,5));
        _healthBar.setFillColor(sf::Color::Green);
    }

    /**
     * Returns the character sprite
     * @return character sprite
     */
    const sf::Sprite& getSprite() const {
        return _sprite;
    }

    const sf::RectangleShape& getBar() const{
        return _healthBar;
    }

    /**
     * Returns the location for weapon grip
     * @return sf::Vector2f of grip location for character
     */
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

    /**
     * Checks if given coordinates are solid in collision mask
     * @param  x x-coordinate of the point to be checked
     * @param  y y-coordinate of the point to be checked
     * @return   boolean hit or not
     */
    bool doesCollide(unsigned int x, unsigned int y) const {
        //Read mask from opposite side if sprite is flipped
        if (_isFlipped)
            x = _mask.size() - x - 1;
        if ((x + OVERLAP < _mask.size()) && (y + OVERLAP < _mask[x].size())) {
            return _mask[x + OVERLAP][y + OVERLAP];
        }
        return false;
    }

    /**
     * Moves the character to given coordinates
     * @param x x-coordinate
     * @param y y-coordinate
     */
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

    /**
     * Checks if character is flipped
     * @return boolean flipped or not
     */
    bool isCharFlipped() const {
        return _isFlipped;
    }

    /**
     * Sets the character as dead
     */
    void kill() {
        _alive = false;
    }

    /**
     * Checks if the character is alive
     * @return boolean alive or not
     */
    bool isAlive() {
        return _alive;
    }

    /**
     * Checks if the character is on screen (the playarea)
     * @return boolean in or not
     */
    bool onScreen() const {
        int x = getSprite().getPosition().x,
            y = getSprite().getPosition().y;
        if (y > 720
            || y < 0
            || x > 1280
            || x < 0) return false;
        return true;
    }
    void reduceHealth(int damage) {
        _health -= damage;
        if (_health <= 0) {
            kill();
            std::cout << "Character dead!" << std::endl;
        } else {
            if (_health < 50) {
                _healthBar.setFillColor(sf::Color::Yellow);
            }
            if (_health < 20) {
                _healthBar.setFillColor(sf::Color::Red);
            }
        }
    }

    void updateBar() {
        _healthBar.setSize(sf::Vector2f(30*_health/_maxhealth,5));
        _healthBar.setPosition(_sprite.getPosition().x -15, _sprite.getPosition().y -30);
    }


private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    std::vector<std::vector<bool> > _mask;
    bool _isFlipped;
    bool _alive;
    int _maxhealth;
    int _health;
    sf::RectangleShape _healthBar;

    // Grip position i.e. The point on character where weapon origin is placed.
    // Defined as pixel offset from top left.
    sf::Vector2f _Grip;
};

#endif
