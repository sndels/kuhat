#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "player.hpp"

class PlayState : public GState
{
public:
    PlayState() {
            _running = true;
        }


    void handleEvents(sf::Event &event) {
        ;
    }

    void update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _player.moveActive(-1.5,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _player.moveActive(1.5,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _player.rotateWeapon(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _player.rotateWeapon(-1);
        }
    }


    void draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        _player.draw(window);
    }
private:
    Player _player;
    sf::Clock _clock;
};

#endif
