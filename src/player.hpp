#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka.hpp"
<<<<<<< HEAD
#include <iostream>
=======
>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505

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
<<<<<<< HEAD
    Player() : _character("resource/sprites/kuha.png"), _weapon(_character.getSprite().getPosition()) {
        _finished = false;
=======
    Player() : _character("resource/sprites/kuha.png", true), _weapon(_character) {
        _finished = false, _aim = 90;
>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505
    }

    void moveActive(float x, float y) {
        _character.move(x,y);
<<<<<<< HEAD
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
=======
        _weapon.updateLocation(_character);
    }

    void rotateWeapon(float deg) {
        _aim += deg;
        // Limit _aim to 0-180 range.
        if (_aim < 0 ) _aim = 0;
        else if (_aim > 180 ) _aim = 180;

        _weapon.rotate(_aim);
    }

>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505


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
<<<<<<< HEAD
=======
    float _aim;
>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505
};

#endif
