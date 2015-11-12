#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "logo.hpp"
#include "character.hpp"
#include "bazooka.hpp"

class PlayState : public GState
{
public:
	PlayState();

	virtual void handleEvents(sf::Event &event);
	virtual void draw(sf::RenderWindow &window);
private:
    bool _running;
    Character _kuha;
    sf::Clock _clock;
    Bazooka _bazooka;
};

#endif
