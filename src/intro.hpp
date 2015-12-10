#ifndef INTRO_H
#define INTRO_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <fstream>  // File IO
#include <stdlib.h> // rand()
#include <time.h>   // for seeding rand
#include <iostream> // cout
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into
#include "m_menu.hpp"

class Intro : public GState
{
public:

    Intro(Game& game) {
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);

        // Start the clock
        _clock.restart();
        // Logo
        if (!_logoTexture.loadFromFile("resource/sprites/logo.png") ) {
            std::cout << "Logo texture failed to load from file." << std::endl;
        }
        _logoTexture.setSmooth(true);
        _logoSprite.setTexture(_logoTexture);
        _logoSprite.setScale((float)_resolution.y/720, (float)_resolution.y/720);
        _logoSprite.setPosition(_resolution.x/2 - _logoSprite.getGlobalBounds().width/2, _resolution.y * 0.14);
        // Slogan
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }
        _slogan.setFont(_aileron_bold_italic);
        _slogan.setCharacterSize(_resolution.y * 0.07);
        _slogan.setColor(sf::Color::Black);
        _newSlogan(game);
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
            // Q quits the game, all other keys swap to mainmenu
            if (event.key.code == sf::Keyboard::Q) game.quit();
            else game.swapActiveState(std::make_shared<MainMenu>(game) );
        }
    }

    void update(Game& game) {
        // Update the slogan every 5 seconds
        if ((_clock.getElapsedTime().asMilliseconds() - _lastSloganUpdate.asMilliseconds() ) >= 5000) {
            _newSlogan(game);
        }
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

    /**
     * Updates the displayed slogan.
     * Gets a random line from slogans.txt and positions it correctly.
     * @param game Reference to game-engine.
     */
    void _newSlogan(Game& game) {
        std::ifstream inFile("resource/slogans.txt");
        int numLines = 0;
        int chosenLine = 0;
        std::string string = "";
        // Count the number of slogans in file
        while ( std::getline(inFile, string) ) {
            ++numLines;
        }
        // Choose random line
        srand(time(nullptr));
        chosenLine = rand() % (numLines + 1);
        // Clear the eof flag and move cursor to start of file
        inFile.clear();
        inFile.seekg(0, std::ios::beg);
        // Read until chosenLine
        for (int i = 0; i <=chosenLine; i++) {
            std::getline(inFile, string);
        }
        // Update the line to _slogan
        _slogan.setString(string);
        // Update the _slogan position, center and 150px from bottom
        _slogan.setPosition(_resolution.x/2 - _slogan.getGlobalBounds().width/2, _resolution.y - _resolution.y * 0.21);
        // Update the timestamp
        _lastSloganUpdate = _clock.getElapsedTime();
    }

    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;
    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;
    sf::Text _slogan;
    sf::Font _aileron_bold_italic;
    sf::Clock _clock;
    sf::Time _lastSloganUpdate;
};

#endif
