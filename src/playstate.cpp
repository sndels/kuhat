#include "playstate.hpp"
#include "character.hpp"

PlayState::PlayState() : _kuha("resource/sprites/kuha.gif") {
	_running = true;
}


void PlayState::handleEvents(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _kuha.move(-1.5,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _kuha.move(1.5,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _kuha.move(0,-1.5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _kuha.move(0,1.5);
}

void PlayState::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);
    window.draw(_kuha.getSprite());
}
