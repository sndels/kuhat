#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka.hpp"
#include <iostream>

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
    Player(int charX = 500, int charY = 75) : _character("resource/sprites/kuha.png", charX, charY, true), _weapon(_character) {
        _finished = false, _aim = 90;
    }

    void moveActive(float x, float y) {
        _character.move(x,y);
        _weapon.updateLocation(_character);
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

    Character getCharacter() const {
        return _character;
    }

    void draw(sf::RenderWindow &window) {
        window.draw(_character.getSprite());
        window.draw(_weapon.getSprite());
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
        _finished = true;
    }

private:
    Character _character;
    Bazooka _weapon;
    bool _finished;
    float _aim;
};

#endif
