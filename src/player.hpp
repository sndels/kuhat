#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "character.hpp"
#include "weapon.hpp"
#include "bazooka.hpp"
#include "shotgun.hpp"
#include "punch.hpp"
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
    Player(int characters, int charX = 500, int charY = 75, int team = 0) : _chars(characters) {
        _team = team;
        _finished = false, _aim = 90;
        for (int i = 0; i < _chars; i++) {
            _chararr.push_back(std::make_shared<Character>("resource/sprites/diykuha.png", charX+i*100, 0, true, team));
        }
        _weaponarr.push_back(std::make_shared<Bazooka>());
        _weaponarr.push_back(std::make_shared<Shotgun>());
        _weaponarr.push_back(std::make_shared<Punch>());
        _current = 0;
        _weaponnum = 0;
    }

    void moveActive(float x, float y, int charnum = -1) {
        if (charnum < 0) charnum = _current;
        _chararr[charnum]->move(x,y);
        _weaponarr[_weaponnum]->updateLocation(getCharacter());
    }

    void rotateWeapon(float deg) {
        _aim += deg;
        // Limit _aim to 0-180 range.
        if (_aim < 0 ) _aim = 0;
        else if (_aim > 180 ) _aim = 180;

        _weaponarr[_weaponnum]->rotate(_aim);
    }

    Weapon& getWeapon() const {
        return *(_weaponarr[_weaponnum]);
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
        if (_current < _chars-1){
            _current++;
        }
        else _current = 0;
    }

    void draw(sf::RenderWindow &window) {
        for (auto c : _chararr) {
            if (c->isAlive()) {
                window.draw(c->getSprite());
                window.draw(c->getBar());
            }
        }
        if (!_finished) {
            _weaponarr[_weaponnum]->updateLocation(getCharacter());
            window.draw(_weaponarr[_weaponnum]->getSprite());
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

    /**
     * Changes player weapon
     * @param integer which is given by user as an input
     */
    void changeWeapon(int i){
        _weaponnum = i;
        _weaponarr[_weaponnum]->updateLocation(getCharacter());
        _weaponarr[_weaponnum]->rotate(_aim);
    }

    /**
     * Returns the index of the currently equipped weapon.
     * 0 for bazooka, 1 for shotgun and 2 for punch.
     * @return integer which is the weapon id
     */
    int getWeaponId(){
        return _weaponnum;
    }

private:
    std::vector<std::shared_ptr<Character>> _chararr;
    std::vector<std::shared_ptr<Weapon>> _weaponarr;
    //Character _character;
    int _current;
    //Bazooka _weapon;
    bool _finished;
    float _aim;
    int _chars;
    int _team;
    int _weaponnum;
};

#endif
