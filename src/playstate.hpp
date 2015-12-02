#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "player.hpp"
#include "map.hpp"
#include "hud.hpp"
#include "collision.hpp"
#include <cmath>
#include <vector>
#include <iostream>

class PlayState : public GState
{
public:
    PlayState(std::string const& mapSeed = "Default seedphsgsdfgsdfgsdfghrase") : _ammo(), _player2(0, 0), _map(mapSeed), _hud("resource/sprites/gradient.png"), _charging(false) {
            _running = true;
            _player2.finishTurn();
        }
    /**
     * Handles SFML events like keypresses, releases
     * @param event Gets a reference to a SF event as parameter
     */
    void handleEvents(sf::Event &event) {
        if (!_ammo.shot()) {
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
                    _ammo.fire(getCurrentPlayer().getWeapon().getMuzzleLocation(), getCurrentPlayer().getWeapon().getAim(), getVelocity());
                    _charging = false;
                }
            }
        }
    }

    void update() {
        sf::Time currentUpdate = _clock.getElapsedTime();
        float deltaT = (float)currentUpdate.asMilliseconds() - (float)_prevUpdate.asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (!checkCollision(_player1.getCharacter(), _map,
                                deltaT * (-0.5), deltaT * (0)))
                getCurrentPlayer().moveActive(deltaT * (-0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (!checkCollision(_player1.getCharacter(), _map,
                                deltaT * (0.5), deltaT * (0)))
                getCurrentPlayer().moveActive(deltaT * (0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (!checkCollision(_player1.getCharacter(), _map,
                                deltaT * (0), deltaT * (-0.5)))
                getCurrentPlayer().moveActive(deltaT * (0),deltaT * (-0.5));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (!checkCollision(_player1.getCharacter(), _map,
                                deltaT * (0), deltaT * (0.5)))
                getCurrentPlayer().moveActive(deltaT * (0),deltaT * (0.5));
        }
        _ammo.updateLocation();
        if (_charging) {
            _hud.setState(_charge.getElapsedTime().asSeconds());
            // NOTE: For this to work properly, turns have to be implemented
            if (_charge.getElapsedTime().asSeconds() > 1.5f) {
                _ammo.fire(getCurrentPlayer().getWeapon().getMuzzleLocation(), getCurrentPlayer().getWeapon().getAim(), getVelocity());
                _charging = false;
            }
        }
        if (_ammo.shot() && !_ammo.onScreen()) {
            std::cout << "Ammo is off the screen" << std::endl;
            _ammo.destroy();
            switchTurn();
        }
        handleCollision();

        _prevUpdate = currentUpdate;
    }

    /**
     * Collision handling
     */
    void handleCollision(){
        if(_ammo.shot()){
            if(checkCollision(_ammo, _player1.getCharacter()) ||
               checkCollision(_ammo, _player2.getCharacter())){
                std::cout<<"Bazooka hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                _ammo.destroy();
                switchTurn();
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::Black);
        if (_charging)
            _hud.draw(window);
        if (_ammo.shot())
            window.draw(_ammo.getSprite());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
        _map.draw(window);
        _player1.draw(window);
        _player2.draw(window);
    }
private:
    /**
     * Get velocity of a charged bazooka shot
     * @return Velocity value between 400 and 1000
     */
    float getVelocity() const {
        float vel = (1+ std::min(_charge.getElapsedTime().asSeconds(), 1.5f))*400;
        std::cout << "Player 1 firing bazooka. Force " << vel << "/1000" << std::endl;
        return vel;
    }
    void switchTurn() {
        if (! _player1.isFinished()) {
            _player1.finishTurn();
            _player2.beginTurn();
        } else {
            _player1.beginTurn();
            _player2.finishTurn();
        }
    }
    Player& getCurrentPlayer() {
        return _player1.isFinished() ? _player2 : _player1;
    }

    BazookaAmmo _ammo;
    Player _player1;
    Player _player2;
    Map _map;
    Hud _hud;
    sf::Clock _clock;
    sf::Time _prevUpdate;
    bool _charging;
    sf::Clock _charge;
};

#endif
