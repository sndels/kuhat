#include "playstate.hpp"
#include "character.hpp"
#include "weapon.hpp"

PlayState::PlayState():
    _running(true),
    _kuha("resource/sprites/kuha.png"),
    _bazooka("resource/sprites/bazooka.png", _kuha) { }


void PlayState::handleEvents(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _kuha.move(-1.5,0);
        _bazooka.updateLocation();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _kuha.move(1.5,0);
        _bazooka.updateLocation();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _kuha.move(0,-1.5);
        _bazooka.updateLocation();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _kuha.move(0,1.5);
        _bazooka.updateLocation();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _bazooka.rotate(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _bazooka.rotate(-3);
    }
}

void PlayState::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);
    window.draw(_kuha.getSprite());
    window.draw(_bazooka.getSprite());
}
