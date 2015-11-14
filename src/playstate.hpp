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
        sf::Time currentUpdate = _clock.getElapsedTime();
        float deltaT = (float)currentUpdate.asMilliseconds() - (float)_prevUpdate.asMilliseconds();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _player.moveActive(deltaT * (-0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _player.moveActive(deltaT * (0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _player.rotateWeapon(deltaT * (0.1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _player.rotateWeapon(deltaT * (-0.1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _ammo.fire(_player.getWeapon().getSprite().getPosition(), _player.getWeapon().getAngle(), 1000);
        }
        _ammo.updateLocation();

        _prevUpdate = currentUpdate;
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
    sf::Time _prevUpdate;
};

#endif
