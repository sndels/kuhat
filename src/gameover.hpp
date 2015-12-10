#ifndef GAMEOVER_H
#define GAMEOVER_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <iostream> // cout
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into
#include "m_menu.hpp"

class GameOver : public GState
{
public:
    /**
     * Initializes the GameOver screen
     */
    GameOver(Game& game, int winner) {
        // Draw lower
        _drawLower = true;

        // Read settigns
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);

        // Font for all text
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }

        // Background
        // Translucent white rectangle on screen center
        _bg.setSize(sf::Vector2f(_resolution.x * 0.9 , _resolution.y * 0.9));
        _bg.setFillColor(sf::Color(255,255,255,200));
        _bg.setOrigin(_bg.getGlobalBounds().width/2, _bg.getGlobalBounds().height/2);
        _bg.setPosition(_resolution.x/2, _resolution.y/2);

        // Title
        std::string text = "Player " + std::to_string(winner) + " won!";
        _title.setString(text);
        _title.setFont(_aileron_bold_italic);
        _title.setColor(sf::Color::Black);
        _title.setCharacterSize(_resolution.y * 0.15);
        _title.setPosition(_resolution.x/2 - _title.getGlobalBounds().width/2, _resolution.y * 0.2);

        // Instructions line 1
        _instructions1.setString("Press Return to restart");
        _instructions1.setFont(_aileron_bold_italic);
        _instructions1.setColor(sf::Color::Black);
        _instructions1.setCharacterSize(_resolution.y * 0.08);
        _instructions1.setPosition(_resolution.x/2 - _instructions1.getGlobalBounds().width/2, _resolution.y -(_resolution.y * 0.28));
        // Instructions line 2
        _instructions2.setString("or Q to quit the game.");
        _instructions2.setFont(_aileron_bold_italic);
        _instructions2.setColor(sf::Color::Black);
        _instructions2.setCharacterSize(_resolution.y * 0.08);
        _instructions2.setPosition(_resolution.x/2 - _instructions2.getGlobalBounds().width/2, _resolution.y -(_resolution.y * 0.2));
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
            // Q quits
            if (event.key.code == sf::Keyboard::Q) {
                game.quit();
                return;
            }
            // Return for restart
            if (event.key.code == sf::Keyboard::Return) {
                game.restart();
                return;
            }
        }
    }

    void update(Game& game) {
        ;
    }

    /**
     * Draws the state
     * @param window [description]
     */
    void draw(sf::RenderWindow& window) {
        // _drawLower is true, so the lower state is drawn on the background
        window.draw(_bg);
        window.draw(_title);
        window.draw(_instructions1);
        window.draw(_instructions2);
    }

private:
    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    sf::Text _title;
    sf::Text _instructions1;
    sf::Text _instructions2;
    sf::Font _aileron_bold_italic;

    sf::RectangleShape _bg;
};

#endif
