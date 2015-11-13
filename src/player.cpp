#include "player.hpp"

/**
 * Initializes the character(s), sets up default ammo counts and sets the turn
 * as not finished
 */
Player::Player() {
    _character = std::make_shared<Character>("resources/sprites/kuha.png");
    _ammoCounts.push_back(15);
    _ammoCounts.push_back(5);
    _ammoCounts.push_back(3);
    _finished = false;
}

/**
 * Checks if the player has ended his turn
 * @return: true if turn has ended, false if not
 */
bool Player::isFinished() const {
    return _finished;
}

/**
 * Ends the player's turn
 */
void Player::finishTurn() {
    _finished = true;
}

/**
 * Checks if given weapon has ammo left
 * @params: weaponsID number
 * @return: true if has ammo, false if not
 */
bool Player::hasAmmo(int weaponID) const {
    return _ammoCounts[weaponID] > 0;
}

/**
 * Reduces the given weapon's ammo count by 1
 * @params: weaponsID number
 */
void Player::reduceAmmo(int weaponID) {
    _ammoCounts[weaponID] -= 1;
}
