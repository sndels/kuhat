#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka.hpp"
#include <iostream>
#include <vector>

/**
 * Class which holds a players character(s) and ammo counts
 * and handles turn logic
 */
class Player
{
public:
    /**
     * Initializes the character(s), sets up default ammo counts and sets the turn
     * as not finished
     */
    Player(int charX = 500, int charY = 75) : _weapon() {
        _finished = false, _aim = 90;
        for (int i = 0; i < 4; i++) {
            _chararr.push_back(Character("resource/sprites/diykuha.png", charX+i*100, 0, true));
        }
        _current = 0;
    }

    void moveActive(float x, float y) {
        _chararr[_current].move(x,y);
        _weapon.updateLocation(getCharacter());
    }

    void rotateWeapon(float deg) {
        _aim += deg;
        // Limit _aim to 0-180 range.
        if (_aim < 0 ) _aim = 0;
        else if (_aim > 180 ) _aim = 180;

        _weapon.rotate(_aim);
    }

    Bazooka getWeapon() const {
        return _weapon;
    }

    Character& getCharacter(int i = -1) {
        if (i < 4 && i >= 0) {
            return _chararr[i];
        }
        else return _chararr[_current];
        // throw error?
    }
    /**
     * Switch over to next character
     */
    void nextCharacter() {
        if (_current < 3)
            _current++;
        else _current = 0;
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < 4; i++) {
            window.draw(_chararr[i].getSprite());
        }
        if (!_finished) {
            window.draw(_weapon.getSprite());
        }
    }

    /**
     * Checks if the player has ended his turn
     * @return: true if turn has ended, false if not
     */
    bool isFinished() const {
        return _finished;
    }
    void beginTurn() {
        _finished = false;
    }
    /**
     * Ends the player's turn
     */
    void finishTurn() {
        nextChahacter();
        _finished = true;
    }

private:
    std::vector<Character> _chararr;
    //Character _character;
    int _current;
    Bazooka _weapon;
    bool _finished;
    float _aim;
};

#endif
