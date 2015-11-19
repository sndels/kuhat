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
    Player() : _character("resource/sprites/kuha.png"), _weapon(_character.getSprite().getPosition()) {
        _finished = false;
    }

    void moveActive(float x, float y) {
        _character.move(x,y);
        _weapon.updateLocation(_character.getSprite().getPosition());
    }

    void rotateWeapon(float deg) {
        _weapon.rotate(deg);
    }

    Bazooka getWeapon() {
        return _weapon;
    }

    Character getCharacter(){
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
};

#endif
