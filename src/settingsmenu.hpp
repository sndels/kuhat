#ifndef S_MENU_H
#define S_MENU_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <iostream> // cout
#include <map>
#include <vector>
#include "gstate.hpp"

class SettingsMenu : public GState
{
public:

    SettingsMenu(Game& game) {
        sf::Text text;

        // Read settings
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);

        // Font for all text
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }
        text.setFont(_aileron_bold_italic);

        // Title
        text.setCharacterSize(_resolution.y * 0.07 );
        text.setColor(sf::Color::Black);
        text.setString("Settings");
        text.setPosition(_resolution.x/2 - text.getGlobalBounds().width/2, _resolution.y * 0.03);
        _options.push_back(std::make_shared<sf::Text>(text));
        // Option names
        std::string name;
        name = "Resolution X: ";
        text.setString(name);
        text.setPosition(_resolution.y * 0.07, _resolution.y * 0.14);
        _options.push_back(std::make_shared<sf::Text>(text));
        name = "Resolution Y: ";
        text.setString(name);
        text.move(0, _resolution.y * 0.14);
        _options.push_back(std::make_shared<sf::Text>(text));
        name = "Number of Players: ";
        text.setString(name);
        text.move(0, _resolution.y * 0.14);
        _options.push_back(std::make_shared<sf::Text>(text));
        name = "Number of Characters: ";
        text.setString(name);
        text.move(0, _resolution.y * 0.14);
        _options.push_back(std::make_shared<sf::Text>(text));
        name = "Character Speed: ";
        text.setString(name);
        text.move(0, _resolution.y * 0.14);
        _options.push_back(std::make_shared<sf::Text>(text));
        // Option values
        name = "resolution.x";
        text.setString(std::to_string(_resolution.x));
        text.setPosition(_resolution.x * 0.7, _resolution.y * 0.14);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));
        name = "resolution.y";
        text.setString(std::to_string(_resolution.y));
        text.move(0, _resolution.y * 0.14);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));
        name = "numPlayers";
        text.setString(std::to_string(_settings.getl("", name, 2)));
        text.move(0, _resolution.y * 0.14);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));
        name = "numChars";
        text.setString(std::to_string(_settings.getl("", name, 4)));
        text.move(0, _resolution.y * 0.14);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));
        name = "charSpeed";
        text.setString(std::to_string(_settings.getf("", name, 0.1)));
        text.move(0, _resolution.y * 0.14);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));

        // Apply & Restart
        name = "Apply & Restart Game";
        text.setString(name);
        text.setPosition(_resolution.x/2 - text.getGlobalBounds().width/2, _resolution.y * 0.84);
        _values.insert(std::pair<std::string, std::shared_ptr<sf::Text>>(name, std::make_shared<sf::Text>(text)));

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
        for (auto o : _options) window.draw(*o);
        for (auto v : _values) window.draw(*(v.second));
    }

private:

    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    std::shared_ptr<sf::Text> _title;
    std::vector<std::shared_ptr<sf::Text>> _options;
    std::map<std::string, std::shared_ptr<sf::Text>> _values;
    sf::Font _aileron_bold_italic;
};

#endif
