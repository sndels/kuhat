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

#define CHARSPEED 0.1
#define CHARGRAV 0.2
#define MAXCLIMB -10

class PlayState : public GState
{
public:
    PlayState(std::string const& mapSeed = "Default seedphsgsdfgsdfgsdfghrase") : _ammo(), _player2(0, 0), _map(mapSeed), _hud("resource/sprites/gradient.png"), _charging(false) {
            _running = true;
            _player2.finishTurn();
        }

    void pause() {
        ;
    }

    void resume() {
        ;
    }

    /**
     * Handles SFML events like keypresses, releases
     * @param event Gets a reference to a SF event as parameter
     */
    void handleEvents(Game& game) {
        sf::Event event;
        while (game.window.pollEvent(event) ) {
            // Check if window is closed
            if (event.type == sf::Event::Closed) {
                game.quit();
                return;
            }

            
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
    }

    void update(Game& game) {
        Player &currentPlayer = getCurrentPlayer();
        sf::Time currentUpdate = _clock.getElapsedTime();
        int dT = currentUpdate.asMilliseconds() - _prevUpdate.asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            for (int dX = 0; dX < dT * CHARSPEED; ++dX) {
                //Try moving for every dX
                if (!checkCollision(currentPlayer.getCharacter(), _map, -1))
                        currentPlayer.moveActive(-1,0);
                else {//If there is a collision, try climbing
                    for (int dY = 0; dY > MAXCLIMB; --dY) {
                        ++dX;//Slow down on steep hills
                        if (!checkCollision(currentPlayer.getCharacter(), _map, -1, dY)) {
                            currentPlayer.moveActive(-1,dY);
                            break;
                        }
                    }
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            for (int dX = 0; dX < dT * CHARSPEED; ++dX) {
                if (!checkCollision(currentPlayer.getCharacter(), _map, 1))
                        currentPlayer.moveActive(1,0);
                else {//If there is a collision, try climbing
                    for (int dY = 0; dY > MAXCLIMB; --dY) {
                        ++dX;//Slow down on steep hills
                        if (!checkCollision(currentPlayer.getCharacter(), _map, 1, dY)) {
                            currentPlayer.moveActive(1,dY);
                            break;
                        }
                    }
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            currentPlayer.rotateWeapon(dT * 0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            currentPlayer.rotateWeapon(dT * (-0.1));
        }
        //"Gravity" to keep active character on the ground
        for (int dY = 0; dY < dT * CHARGRAV; ++dY){
            if (!checkCollision(currentPlayer.getCharacter(), _map, 0, 1)) {
                currentPlayer.moveActive(0,1);
            } else
                break;
        }
        _ammo.updateLocation();
        if (_charging) {
            _hud.setState(_charge.getElapsedTime().asSeconds());
            if (_charge.getElapsedTime().asSeconds() > 1.5f) {
                _ammo.fire(currentPlayer.getWeapon().getMuzzleLocation(), currentPlayer.getWeapon().getAim(), getVelocity(), _wind);
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
            if(checkCollision(_ammo, _player1.getCharacter()) ||
               checkCollision(_ammo, _player2.getCharacter())){
                std::cout<<"Bazooka hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                _ammo.destroy();
                endTurn();
            }
        }
    }

    void draw(Game& game) {
        game.window.clear(sf::Color::Black);
        _map.draw(game.window);
        if (_ammo.shot())
            game.window.draw(_ammo.getSprite());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
        _player1.draw(game.window);
        _player2.draw(game.window);
        if (_charging)
            _hud.drawPower(game.window);
        _hud.drawWind(game.window);
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
    Map _map;
    Hud _hud;
    sf::Clock _clock;
    sf::Time _prevUpdate;
    bool _charging;
    sf::Clock _charge;
};

#endif
