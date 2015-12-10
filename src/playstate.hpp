#ifndef PLAY_H
#define PLAY_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include "gstate.hpp"
#include "player.hpp"
#include "map.hpp"
#include "hud.hpp"
#include "collision.hpp"
#include "particles.hpp"
#include "p_menu.hpp"
#include <cmath>
#include <vector>
#include <iostream>

#define CHARGRAV 0.2
#define MAXCLIMB -10

class PlayState : public GState
{
public:
    PlayState(Game& game, std::string const& mapSeed = "Default seedphsgsdfgsdfgsdfghrase") : _ammo(), _map(mapSeed), _particles(500), _hud("resource/sprites/gradient.png"), _charging(false) {
        _numPlayers = _settings.getl("", "numPlayers", 2);
        _numChars = _settings.getl("", "numChars", 4);
        _charSpeed = _settings.getf("", "charSpeed", 0.1);

        for (int i = 0; i < _numPlayers; i++) {
            _players.push_back(std::make_shared<Player>(_numChars, 100 + 500*i, 100, i));
            if (i > 0) _players[i]->finishTurn();
        }
        _running = true;
        // Skip to round two to fix first shot problems
        for (int i = 0; i < _numPlayers; ++i) {
            endTurn();
        }
    }

    void pause() {
        ;
    }

    void resume() {
        ;
    }

    /**
     * Event handling
     * @param game  Ref to game-engine
     * @param event Ref to the event
     */
    void handleEvents(Game& game, sf::Event& event) {
        // Check if window is closed
        if (event.type == sf::Event::Closed) {
            game.quit();
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) game.moveToState(std::make_shared<PauseMenu>(game));
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

    void update(Game& game) {
        Player &currentPlayer = getCurrentPlayer();
        sf::Time currentUpdate = _clock.getElapsedTime();
        int dT = currentUpdate.asMilliseconds() - _prevUpdate.asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            for (int dX = 0; dX < dT * _charSpeed; ++dX) {
                //Try moving for every dX
                if (!checkCollision(currentPlayer.getCharacter(), _map, -1).x)
                        currentPlayer.moveActive(-1,0);
                else {//If there is a collision, try climbing
                    for (int dY = 0; dY > MAXCLIMB; --dY) {
                        ++dX;//Slow down on steep hills
                        if (!checkCollision(currentPlayer.getCharacter(), _map, -1, dY).x) {
                            currentPlayer.moveActive(-1,dY);
                            break;
                        }
                    }
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            for (int dX = 0; dX < dT * _charSpeed; ++dX) {
                if (!checkCollision(currentPlayer.getCharacter(), _map, 1).x)
                        currentPlayer.moveActive(1,0);
                else {//If there is a collision, try climbing
                    for (int dY = 0; dY > MAXCLIMB; --dY) {
                        ++dX;//Slow down on steep hills
                        if (!checkCollision(currentPlayer.getCharacter(), _map, 1, dY).x) {
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
        _particles.update(currentUpdate - _prevUpdate, _map);
        _prevUpdate = currentUpdate;
    }

    /**
     * Collision handling
     */
    void handleCollision(){
        if(_ammo.shot()){
            for (auto player : _players) {
                for (int i = 0; i < _numChars; i++) {
                    if(_ammo.getAirTime().asMilliseconds() < 5) continue;
                    if(checkCollision(_ammo, player->getCharacter(i)).x){
                        std::cout<<"Character hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                        doDamage();
                        _map.addHole(_ammo.getX(), _ammo.getY());
                        _ammo.destroy(_particles);
                        endTurn();
                    }
                }
            }
            if (checkCollision(_ammo, _map).x) {
                std::cout<<"Terrain hit at coordinates X:"<<_ammo.getX()<<" Y:"<<_ammo.getY()<<std::endl;
                doDamage();
                _map.addHole(_ammo.getX(), _ammo.getY());
                _ammo.destroy(_particles);
                endTurn();
            }
        }
    }

    void doDamage() {
        int dist;
        for (auto& player : _players) {
            for (int i = 0; i < _numChars; i++) {
                dist = getDistance(player->getCharacter(i).getSprite().getPosition().x,
                    player->getCharacter(i).getSprite().getPosition().y, _ammo.getX(), _ammo.getY());
                if (dist < HOLERADIUS) {
                    player->getCharacter(i).reduceHealth(50 * dist/HOLERADIUS);
                    std::cout << "Character " << i << " took " <<  50 * dist/HOLERADIUS << " damage!" << std::endl;
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        _particles.draw(window);
        _map.draw(window);
        if (_ammo.shot())
            window.draw(_ammo.getSprite());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
        for (auto player : _players) {
            player->draw(window);
        }
        if (_charging)
            _hud.drawPower(window);
        _hud.drawWind(window);
    }

    void checkGravity(int dT) {
        //"Gravity" to keep active character on the ground
        for (auto player : _players) {
            for (int i = 0; i < _numChars; i++) {
                for (int dY = 0; dY < dT * CHARGRAV; ++dY){
                    if (!checkCollision(player->getCharacter(i), _map, 0, 1).x) {
                        player->moveActive(0,1, i);
                    } else break;
                }
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
        for (unsigned int i = 0; i < _players.size(); i++) {
            if (! _players[i]->isFinished()) {
                _players[i]->finishTurn();
                if (i+1 < _players.size())
                    _players[i+1]->beginTurn();
                else
                    _players[0]->beginTurn();
                break;
            }
        }
        _wind = std::rand() % 200 - 100;
        _hud.setWind(_wind);
        std::cout << "Turn ended, wind has changed to " << _wind << std::endl;
    }
    Player& getCurrentPlayer() {
        for (auto player : _players) {
            if (!player->isFinished()) return *(player);
        }
        return *(_players[0]);
    }

    void checkBounds() {
        for (auto player : _players) {
            for (int i = 0; i < _numChars; i++) {
                if (!player->getCharacter(i).onScreen())
                    player->getCharacter(i).kill();
            }
        }
    }


    int getDistance(int x1, int y1, int x2, int y2) {
        return std::sqrt(std::pow(x1-x2, 2) + std::pow(y1-y2, 2));
    }

    minIni _settings = minIni("settings.ini");
    int _numPlayers;
    int _numChars;
    float _charSpeed;

    BazookaAmmo _ammo;
    std::vector<std::shared_ptr<Player>> _players;
    int _wind;
    Map _map;
    ParticleSystem _particles;
    Hud _hud;
    sf::Clock _clock;
    sf::Time _prevUpdate;
    bool _charging;
    sf::Clock _charge;
};

#endif
