#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "player.hpp"

#include <iostream>

class PlayState : public GState
{
public:
    PlayState() : _ammo(), _charging(false) {
            _running = true;
        }
    /**
     * Handles SFML events like keypresses, releases
     * @param event Gets a reference to a SF event as parameter
     */
    void handleEvents(sf::Event &event) {
        if (event.type == sf::Event::KeyPressed) {
            // Using switch rather than if in case of future keypress events
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    if (!_charging) {
                        _charge.restart();
                        _charging = true;
                    }
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                float force = (1+ std::min(_charge.getElapsedTime().asSeconds(), 1.5f))*400;
                // Min force: 400, max: 1000
                std::cout << "Player 1 firing bazooka. Force " << force << "/1000" << std::endl;
                _ammo.fire(_player.getWeapon().getSprite().getPosition(), _player.getWeapon().getAngle(), force);
                _charging = false;
            }
        }
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
    bool _charging;
    sf::Clock _charge;
};

#endif
