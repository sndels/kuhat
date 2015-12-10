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

        // Slogan
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }
        _title.setFont(_aileron_bold_italic);
        _title.setCharacterSize(50);
        _title.setColor(sf::Color::Black);
        _title.setString(_settings.gets("", "resolution.x", "1280"));
        _title.setPosition(_resolution.x/2 - _title.getGlobalBounds().width/2, 100);
        _options.push_back(std::make_shared<sf::Text>(_title));
        _title.setString("jee");
        _title.move(0,100);
        _options.push_back(std::make_shared<sf::Text>(_title));

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
        for (auto o : _options) window.draw(*o);
    }

private:

    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    std::vector<std::shared_ptr<sf::Text>> _options;
    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;
    sf::Text _title;
    sf::Font _aileron_bold_italic;
};

#endif
