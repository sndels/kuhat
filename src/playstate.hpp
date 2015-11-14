#ifndef PLAY_H
#define PLAY_H

#include "gstate.hpp"
#include "logo.hpp"
#include "character.hpp"
#include "bazooka.hpp"

class PlayState : public GState
{
public:
    PlayState():
        _running(true),
        _kuha("resource/sprites/kuha.png"),
        _bazooka(_kuha) { }


    void handleEvents(sf::Event &event) {
        ;
    }

    void update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _kuha.move(-1.5,0);
            _bazooka.updateLocation();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _kuha.move(1.5,0);
            _bazooka.updateLocation();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _bazooka.rotate(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _bazooka.rotate(-1);
        }
    }


    void draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        window.draw(_kuha.getSprite());
        window.draw(_bazooka.getSprite());
    }
private:
    bool _running;
    Character _kuha;
    sf::Clock _clock;
    Bazooka _bazooka;
};

#endif
