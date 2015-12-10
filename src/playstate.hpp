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
#include "gameover.hpp"
#include <cmath>
#include <vector>
#include <iostream>

#define CHARGRAV 0.2
#define MAXCLIMB -10

/**
 * Class for the playstate
 */
class PlayState : public GState
{
public:
    /**
     * Constructor generates terrain and spawns characters
     * @param game    active game instance
     * @param mapSeed seed for map generation
     */
    PlayState(Game& game, std::string const& mapSeed = "Get random map") : _ammo(), _map(mapSeed), _particles(500), _hud("resource/sprites/gradient.png"), _charging(false) {
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

    /**
     * Sets the logical clock to current time to prevent skipping
     */
    void resume() {
        _prevUpdate = _clock.getElapsedTime();
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
            if (event.key.code == sf::Keyboard::P) game.moveToState(std::make_shared<GameOver>(game, 1));
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) getCurrentPlayer().changeWeapon(0);
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num2) getCurrentPlayer().changeWeapon(1);
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num3) getCurrentPlayer().changeWeapon(2);
        }

        switch (getCurrentPlayer().getWeaponId()){
            case 0:
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
                            _charge.restart();
                        }
                    }
                }
                break;
            case 1:
                if (!_slug.shot()){
                   if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                            case sf::Keyboard::LAlt:
                                _slug.fire(getCurrentPlayer().getWeapon().getMuzzleLocation(), getCurrentPlayer().getWeapon().getAim());
                                break;
                            default:
                                break;
                        }
                    }
                }
            case 2:
                if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                            case sf::Keyboard::LControl:
                                getCurrentPlayer().getWeapon().punch();
                                break;
                            default:
                                break;
                        }
                    }
                break;
            default:
                break;
        }
    }

    /**
     * Updates the state
     * @param game  Ref to game-engine
     */
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
        _slug.updateLocation();
        if (_charging) {
            _hud.setState(_charge.getElapsedTime().asSeconds());
            if (_charge.getElapsedTime().asSeconds() > 1.5f) {
                _ammo.fire(currentPlayer.getWeapon().getMuzzleLocation(), currentPlayer.getWeapon().getAim(), getVelocity(), _wind);
                _charging = false;
                _charge.restart();
            }
        }
        if (_ammo.shot() && !_ammo.onScreen()) {
            std::cout << "Ammo is off the screen" << std::endl;
            _ammo.destroy();
            endTurn();
        }
        if (_slug.shot() && !_slug.onScreen()) {
            std::cout << "Ammo is off the screen" << std::endl;
            _slug.destroy();
            endTurn();
        }
        handleCollision();
        updateHealthBars();
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
                        player->getCharacter(i).reduceHealth(25);
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
        if(_slug.shot()){
            for (auto player : _players) {
                for (int i = 0; i < _numChars; i++) {
                    if(_slug.getAirTime().asMilliseconds() < 5) continue;
                    if(checkCollision(_slug, player->getCharacter(i)).x){
                        std::cout<<"Character hit at coordinates X:"<<_slug.getX()<<" Y:"<<_slug.getY()<<std::endl;
                        player->getCharacter(i).reduceHealth(15);
                        doDamage(20,20);
                        _map.addHole(_slug.getX(), _slug.getY(), 20);
                        _slug.destroy(_particles);
                        endTurn();
                    }
                }
            }
            if (checkCollision(_slug, _map).x) {
                std::cout<<"Terrain hit at coordinates X:"<<_slug.getX()<<" Y:"<<_slug.getY()<<std::endl;
                doDamage(20,20);
                _map.addHole(_slug.getX(), _slug.getY(), 20);
                _slug.destroy(_particles);
                endTurn();
            }
        }
        if(getCurrentPlayer().getWeapon().punchStatus()){
            for (auto player : _players) {
                for (int i = 0; i < _numChars; i++) {
                    if(getCurrentPlayer().getWeapon().punchCollision(player->getCharacter(i))){
                        player->getCharacter(i).reduceHealth(50);
                        std::cout << "Character "<< i <<" got punched for 50 damage!"<< std::endl;
                    }
                }
            }
            endTurn();
        }
    }

    void doDamage(int dmg = 25, float radius = 40) {
        int dist;
        for (auto& player : _players) {
            for (int i = 0; i < _numChars; i++) {
                dist = getDistance(player->getCharacter(i).getSprite().getPosition().x,
                    player->getCharacter(i).getSprite().getPosition().y, _ammo.getX(), _ammo.getY());
                if (dist < radius) {
                    player->getCharacter(i).reduceHealth(dmg);
                    std::cout << "Character " << i << " took " <<  dmg << " damage!" << std::endl;
                }
            }
        }
    }

    /**
     * Draw the state
     * @param render window
     */
    void draw(sf::RenderWindow& window) {
        _particles.draw(window);
        _map.draw(window);
        if (_ammo.shot())
            window.draw(_ammo.getSprite());
        if (_slug.shot())
            window.draw(_slug.getSprite());
        // Draw player after ammo, so that ammo is spawned inside (behind) the barrel.
        for (auto player : _players) {
            player->draw(window);
        }
        if (_charging)
            _hud.drawPower(window);
        _hud.drawWind(window);
    }

    /**
     * Drops characters to the ground
     * @param dT change in time
     */
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
    /**
     * Returns the current player
     * @return current player
     */
    Player& getCurrentPlayer() {
        for (auto player : _players) {
            if (!player->isFinished()) return *(player);
        }
        return *(_players[0]);
    }

    /**
     * Loops over characters to kill ones out of bounds
     */
    void checkBounds() {
        for (auto player : _players) {
            for (int i = 0; i < _numChars; i++) {
                if (!player->getCharacter(i).onScreen())
                    player->getCharacter(i).kill();
            }
        }
    }

    void updateHealthBars() {
        for (auto& player : _players) {
            for (int i = 0; i < _numChars; i++) {
                player->getCharacter(i).updateBar();
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
    ShotgunAmmo _slug;
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
