#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "character.hpp"

/**
 * Class which holds a players character(s) and ammo counts
 * and handles turn logic
 */
class Player
{
public:
	Player();

	bool isFinished() const;
	void finishTurn();

	bool hasAmmo(int weaponID) const;
	void reduceAmmo(int weaponID);

private:
	std::shared_ptr<Character> _character;
	std::vector<char> _ammoCounts;//Ammo counts in the weapon order
	bool _finished;
};

#endif
