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
#define CHARS 4

class PlayState : public GState
{
public:
    PlayState(std::string const& mapSeed = "Default seedphsgsdfgsdfgsdfghrase") : _ammo(), _player1(CHARS, 100,100, 1), _player2(CHARS, 600, 100, 2), _map(mapSeed), _hud("resource/sprites/gradient.png"), _charging(false) {
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

                //Commented out for shotgun testing
                /*if (!_ammo.shot()) {
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
            }*/
            if(!getCurrentPlayer().getWeapon().shot()){
               if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Space:
                            getCurrentPlayer().getWeapon().fire();
                            break;
                        default:
                            break;
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
        if (!currentPlayer.getCharacter().isAlive()) endTurn();
        checkGravity(dT);
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
            for (int i = 0; i < CHARS; i++) {
                if(checkCollision(_ammo, _player1.getCharacter(i)) ||
                   checkCollision(_ammo, _player2.getCharacter(i))){
                    std::cout<<"Character hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                    _map.addHole(_ammo.getX(), _ammo.getY());
                    _ammo.destroy();
                    endTurn();
                }
            }
            if (checkCollision(_ammo, _map)) {
                std::cout<<"Terrain hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                _map.addHole(_ammo.getX(), _ammo.getY());
                _ammo.destroy();
                endTurn();
            }

        }
        //Testing shotgun collision for characters
        if(getCurrentPlayer().getWeapon().shot()){
            for (int i = 0; i < CHARS; i++) {
               if(getCurrentPlayer().getWeapon().shotgunCollision(_player1.getCharacter(i))) std::cout<<"Shotgun hit player 1 character"<<std::endl;
               if(getCurrentPlayer().getWeapon().shotgunCollision(_player2.getCharacter(i))) std::cout<<"Shotgun hit player 2 character"<<std::endl;
            }
            endTurn();
        }
    }

    void draw(Game& game) {
        game.window.clear(sf::Color::Black);
        _map.draw(game.window);
        if (_ammo.shot())
            game.window.draw(_ammo.getSprite());
        //Draw shotguns shooting trajectory for debugging
        if (!getCurrentPlayer().getWeapon().shot())
            game.window.draw(getCurrentPlayer().getWeapon().getTrajectory());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
        _player1.draw(game.window);
        _player2.draw(game.window);
        if (_charging)
            _hud.drawPower(game.window);
        _hud.drawWind(game.window);
    }

    void checkGravity(int dT) {
        //"Gravity" to keep active character on the ground
        for (int i = 0; i < CHARS; i++) {
            for (int dY = 0; dY < dT * CHARGRAV; ++dY){
                if (!checkCollision(_player1.getCharacter(i), _map, 0, 1)) {
                    _player1.moveActive(0,1, i);
                } else break;
            }
        }
        for (int i = 0; i < CHARS; i++) {
            for (int dY = 0; dY < dT * CHARGRAV; ++dY){
                if (!checkCollision(_player2.getCharacter(i), _map, 0, 1)) {
                    _player2.moveActive(0,1, i);
                } else break;
            }
        }

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
        checkBounds();
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

    void checkBounds() {
        for (int i = 0; i < CHARS; i++) {
            if (!_player1.getCharacter(i).onScreen()) _player1.getCharacter(i).kill();
        }
        for (int i = 0; i < CHARS; i++) {
            if (!_player2.getCharacter(i).onScreen()) _player2.getCharacter(i).kill();

        }

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
