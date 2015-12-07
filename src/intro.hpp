#ifndef INTRO_H
#define INTRO_H

#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into
#include "m_menu.hpp"

class Intro : public GState
{
public:

    Intro() {
        // Logo
        if (!_logoTexture.loadFromFile("resource/sprites/logo.png") ) {
            std::cout << "Logo texture failed to load from file." << std::endl;
        }
        _logoSprite.setTexture(_logoTexture);
        _logoSprite.setPosition(1280/2 - _logoSprite.getGlobalBounds().width/2, 100);
        // Slogan
        if (!_aileron_bold_italic.loadFromFile("resource/fonts/aileron/Aileron-BoldItalic.otf") ) {
            std::cout << "Slogan font failed to load from file." << std::endl;
        }
        _slogan.setFont(_aileron_bold_italic);
        _slogan.setCharacterSize(50);
        _slogan.setColor(sf::Color::Black);
        _slogan.setString("Jee!");
        _slogan.setPosition(1280/2 - _slogan.getGlobalBounds().width/2, 720 - 150);
    }

    void pause() {
        ;
    }

    void resume() {
        ;
    }

    /**
     * Handle events.
     * @param game Reference to the game-engine.
     */
    void handleEvents(Game& game) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            // Check if window is closed
            if (event.type == sf::Event::Closed) {
                game.quit();
                return;
            }

            // Check keypresses
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    game.moveToState(std::make_shared<MainMenu>() );
                    return;
                }
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
    void draw(Game& game) {
        game.window.clear(sf::Color::White);
        game.window.draw(_logoSprite);
        game.window.draw(_slogan);
    }

private:

    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;
    sf::Text _slogan;
    sf::Font _aileron_bold_italic;
};

#endif
