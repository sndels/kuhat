#ifndef S_MENU_H
#define S_MENU_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <iostream> // cout
#include "gstate.hpp"

class SettingsMenu : public GState
{
public:

    SettingsMenu(Game& game) {
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);

        // Logo
        if (!_logoTexture.loadFromFile("resource/sprites/logo.png") ) {
            std::cout << "Logo texture failed to load from file." << std::endl;
        }
        _logoTexture.setSmooth(true);
        _logoSprite.setTexture(_logoTexture);
        _logoSprite.setPosition(_resolution.x/2 - _logoSprite.getGlobalBounds().width/2, 100);
        // Slogan
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }
        _slogan.setFont(_aileron_bold_italic);
        _slogan.setCharacterSize(50);
        _slogan.setColor(sf::Color::Black);
        _slogan.setString("Settings");
        _slogan.setPosition(_resolution.x/2 - _slogan.getGlobalBounds().width/2, 720 - 150);
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

        // Check keypresses
        if (event.type == sf::Event::KeyPressed) {
            // Esc goes back
            if (event.key.code == sf::Keyboard::Escape) game.goToPreviousState();
        }
    }

    void update(Game& game) {
        ;
    }

    /**
     * Draw
     * @param game Reference to game-engine
     */
    void draw(sf::RenderWindow& window) {
        window.clear(sf::Color::White);
        window.draw(_logoSprite);
        window.draw(_slogan);
    }

private:

    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;
    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;
    sf::Text _slogan;
    sf::Font _aileron_bold_italic;
};

#endif
