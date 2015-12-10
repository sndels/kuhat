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
    * Constructor sets up characters, default ammo counts and sets the turn
    * as not finished
    * @param characters number of characters
    * @param charX
    * @param charY      [description]
    * @param team       number of the team
    */
    Player(int characters, int charX = 500, int charY = 75, int team = 0) : _weapon(), _chars(characters) {
        _team = team;
        _finished = false, _aim = 90;
        for (int i = 0; i < _chars; i++) {
            _chararr.push_back(std::make_shared<Character>("resource/sprites/diykuha.png", charX+i*100, 0, true, team));
        }
        _current = 0;
    }

    /**
     * Moves the active character
     * @param x       destination x-coordinate
     * @param y       destination y-coordinate
     * @param charnum number of the character
     */
    void moveActive(float x, float y, int charnum = -1) {
        if (charnum < 0) charnum = _current;
        _chararr[charnum]->move(x,y);
        _weapon.updateLocation(getCharacter());
    }

    /**
     * Rotates the weapon
     * @param deg rotation amount
     */
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
        if (i < _chars && i >= 0) {
            return *(_chararr[i]);
        }
        else return *(_chararr[_current]);
        // throw error?
    }

    /**
     * Switch over to next character
     */
    void nextCharacter() {
        if (_current < _chars-1)
            _current++;
        else _current = 0;
    }

    /**
     * Draws the characters and healths
     * @param window render window
     */
    void draw(sf::RenderWindow &window) {
        for (auto c : _chararr) {
            if (c->isAlive())
                window.draw(c->getSprite());
        }
        if (!_finished) {
            _weapon.updateLocation(getCharacter());
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

    /**
     * Begins the player's turn
     */
    void beginTurn() {
        _finished = false;
    }
    /**
     * Ends the player's turn
     */
    void finishTurn() {
        int deadcount = -1;
        do {
            nextCharacter();
            if(deadcount++>=_chars) {
                std::cout << "all ded" <<std::endl;
                exit(0);
            }
        } while (!getCharacter().isAlive());
        _finished = true;
    }

private:
    std::vector<std::shared_ptr<Character>> _chararr;
    //Character _character;
    int _current;
    Bazooka _weapon;
    bool _finished;
    float _aim;
    int _chars;
    int _team;
};

#endif
