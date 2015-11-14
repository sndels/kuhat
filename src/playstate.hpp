#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "player.hpp"

#include <iostream>

class PlayState : public GState
{
public:
    PlayState() : _ammo() {
            _running = true;
        }


    void handleEvents(sf::Event &event) {
        std::cout << _player.getWeapon().getAngle() << std::endl;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _ammo.fire(_player.getWeapon().getSprite().getPosition(), _player.getWeapon().getAngle(), 1000);
        }
        _ammo.updateLocation();
    }


    void draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        _player.draw(window);
        if (_ammo.shot())
            window.draw(_ammo.getSprite());
    }
private:
    BazookaAmmo _ammo;
    Player _player;
    sf::Clock _clock;
};

#endif
