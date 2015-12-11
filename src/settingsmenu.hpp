#ifndef S_MENU_H
#define S_MENU_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <iostream> // cout
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
        text.setColor(sf::Color::White);
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
        _values.push_back(std::make_shared<sf::Text>(text));
        name = "resolution.y";
        text.setString(std::to_string(_resolution.y));
        text.move(0, _resolution.y * 0.14);
        _values.push_back(std::make_shared<sf::Text>(text));
        name = "numPlayers";
        text.setString(std::to_string(_settings.getl("", name, 2)));
        text.move(0, _resolution.y * 0.14);
        _values.push_back(std::make_shared<sf::Text>(text));
        name = "numChars";
        text.setString(std::to_string(_settings.getl("", name, 4)));
        text.move(0, _resolution.y * 0.14);
        _values.push_back(std::make_shared<sf::Text>(text));
        name = "charSpeed";
        text.setString(_settings.gets("", name, "0.1"));
        text.move(0, _resolution.y * 0.14);
        _values.push_back(std::make_shared<sf::Text>(text));

        // Apply & Restart
        name = "Apply & Restart Game";
        text.setString(name);
        text.setPosition(_resolution.x/2 - text.getGlobalBounds().width/2, _resolution.y * 0.84);
        _values.push_back(std::make_shared<sf::Text>(text));

        // Set initial selection
        _values.at(_selected)->setColor(sf::Color::Red);
        _values.at(_selected)->setStyle(sf::Text::Bold);
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

        // Check for entered text
        if (event.type == sf::Event::TextEntered) {
            // Backspace
            if (event.text.unicode == 8) {
                std::string s = _values.at(_selected)->getString();
                if (!s.empty()) s.pop_back();
                _values.at(_selected)->setString(s);
            }
            // Ascii character and not Return
            else if (event.text.unicode < 128 && event.text.unicode != 13) {
                // Clear the string if starting to type
                if (_clear) {
                    _values.at(_selected)->setString("");
                    _clear = false;
                }
                _values.at(_selected)->setString(_values.at(_selected)->getString() + event.text.unicode);
            }
        }

        // Check keypresses
        if (event.type == sf::Event::KeyPressed) {
            // Esc goes back
            if (event.key.code == sf::Keyboard::Escape) game.goToPreviousState();
            // Move selection up/down
            if ((event.key.code == sf::Keyboard::Down) && (_selected < (int)_values.size()-1) ) {
                _values.at(_selected)->setColor(sf::Color::White);
                _values.at(_selected)->setStyle(sf::Text::Regular);
                ++_selected;
                _clear = true;
                _values.at(_selected)->setColor(sf::Color::Red);
                _values.at(_selected)->setStyle(sf::Text::Bold);
            }
            else if (event.key.code == sf::Keyboard::Up && _selected > 0) {
                _values.at(_selected)->setColor(sf::Color::White);
                _values.at(_selected)->setStyle(sf::Text::Regular);
                --_selected;
                _clear = true;
                _values.at(_selected)->setColor(sf::Color::Red);
                _values.at(_selected)->setStyle(sf::Text::Bold);
            }
            // Enter: save and restart if "Apply" is selected
            if (event.key.code == sf::Keyboard::Return) {
                if (_selected == (int)(_values.size()-1)) saveAndRestart(game);
            }

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
        for (auto o : _options) window.draw(*o);
        for (auto v : _values) window.draw(*v);
    }

private:

    /**
     * Saves the settings and restarts the game.
     * The new settings are limited to sensible ranges.
     * Restarting the game takes care of resolution change etc.
     * @param game [description]
     */
    void saveAndRestart(Game& game) {
        // Helper string and int
        std::string s;
        int i;
        float f;

        // Save settings to ini-file

        // Limit x resolution to 800-4069
        s = _values.at(0)->getString();
        i = 0;
        i = std::stoi(s);
        if (i>=800 && i<=4096) _settings.put("", "resolution.x", s);

        // Limit y resolution to 600-2160
        s = _values.at(1)->getString();
        i = 0;
        i = std::stoi(s);
        if (i>=600 && i<=2160) _settings.put("", "resolution.y", s);

        // Limit number of players to 2-4
        s = _values.at(2)->getString();
        i = 0;
        i = std::stoi(s);
        if (i>=2 && i<=4) _settings.put("", "numPlayers", s);

        // Limit number of characters in team to 1-8
        s = _values.at(3)->getString();
        i = 0;
        i = std::stoi(s);
        if (i>=1 && i<=8) _settings.put("", "numChars", s);

        // Limit speed of characters to 0.1-1
        s = _values.at(4)->getString();
        f = 0;
        f = std::stof(s);
        if (f>=0.1 && f<=1) _settings.put("", "charSpeed", s);

        // Restart the game
        game.restart();
    }

    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    std::shared_ptr<sf::Text> _title;
    std::vector<std::shared_ptr<sf::Text>> _options;
    std::vector<std::shared_ptr<sf::Text>> _values;
    sf::Font _aileron_bold_italic;

    int _selected = 0;
    bool _clear = true;
};

#endif
