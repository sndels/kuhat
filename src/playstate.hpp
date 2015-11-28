#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "player.hpp"
#include "hud.hpp"
#include <cmath>
#include <iostream>

class PlayState : public GState
{
public:
    PlayState() : _ammo(), _hud("resource/sprites/gradient.png"), _charging(false) {
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
                    _ammo.fire(getCurrentPlayer().getWeapon().getMuzzleLocation(), getCurrentPlayer().getWeapon().getAim(), getVelocity(), _wind);
                    _charging = false;
                }
            }
        }
    }

    void update() {
        sf::Time currentUpdate = _clock.getElapsedTime();
        float deltaT = (float)currentUpdate.asMilliseconds() - (float)_prevUpdate.asMilliseconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            getCurrentPlayer().moveActive(deltaT * (-0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            getCurrentPlayer().moveActive(deltaT * (0.5),deltaT * (0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            getCurrentPlayer().rotateWeapon(deltaT * (0.1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            getCurrentPlayer().rotateWeapon(deltaT * (-0.1));
        }
        _ammo.updateLocation();
        if (_charging) {
            _hud.setState(_charge.getElapsedTime().asSeconds());
            // NOTE: For this to work properly, turns have to be implemented
            if (_charge.getElapsedTime().asSeconds() > 1.5f) {
                _ammo.fire(getCurrentPlayer().getWeapon().getMuzzleLocation(), getCurrentPlayer().getWeapon().getAim(), getVelocity(), _wind);
                _charging = false;
            }
        }
        if (_ammo.shot() && !_ammo.onScreen()) {
            std::cout << "Ammo is off the screen" << std::endl;
            _ammo.destroy();
            endTurn();
        }
        handleCollision();

        _prevUpdate = currentUpdate;
    }

    /**
     * Collision handling
     */
    void handleCollision(){
        if(_ammo.shot()){
            sf::FloatRect _ammo_hitbox = _ammo.getSprite().getGlobalBounds();
            sf::FloatRect _player1_hitbox = _player1.getCharacter().getSprite().getGlobalBounds();
            sf::FloatRect _player2_hitbox = _player2.getCharacter().getSprite().getGlobalBounds();
            if(_ammo_hitbox.intersects(_player2_hitbox) || _ammo_hitbox.intersects(_player1_hitbox) ){
                std::cout<<"Bazooka hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                _ammo.destroy();
                endTurn();
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        if (_charging)
            _hud.drawPower(window);
        _hud.drawWind(window);
        if (_ammo.shot())
            window.draw(_ammo.getSprite());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
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
    /**
     * Handles all activities needed to finish a turn. Switches players' turn
     * values, recalculater wind and redraws the wind bar.
     */
    void endTurn() {
        if (! _player1.isFinished()) {
            _player1.finishTurn();
            _player2.beginTurn();
        } else {
            _player1.beginTurn();
            _player2.finishTurn();
        }
        _wind = std::rand() % 200 - 100;
        _hud.setWind(_wind);
        std::cout << "Turn ended, wind has changed to " << _wind << std::endl;
    }
    Player& getCurrentPlayer() {
        return _player1.isFinished() ? _player2 : _player1;
    }

    BazookaAmmo _ammo;
    Player _player1;
    Player _player2;
    int _wind;
    Hud _hud;
    sf::Clock _clock;
    sf::Time _prevUpdate;
    bool _charging;
    sf::Clock _charge;
};

#endif
