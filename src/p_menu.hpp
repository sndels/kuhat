#ifndef P_MENU_H
#define P_MENU_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into

/**
 * Class for the pause menu
 */
class PauseMenu : public GState
{
public:
    /**
     * Initializes all menu items and sets class state to running
     * @param active game instance
     */
    PauseMenu(Game& game) {
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);

        _drawLower = true;
        // Logo
        if (!_logoTexture.loadFromFile("resource/sprites/logo.png") ) {
            std::cout << "Logo texture failed to load from file." << std::endl;
        }
        _logoSprite.setTexture(_logoTexture);
        _logoSprite.setPosition(_resolution.x/2 - _logoSprite.getGlobalBounds().width/2, 100);
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
            if (event.key.code == sf::Keyboard::Escape) {
                game.goToPreviousState();
                return;
            }
        }
    }

    /**
     * Empty as no updates are needed for the pause menu
     * @param game  Ref to game-engine
     */
    void update(Game& game) {
        ;
    }

    /**
     * Draws the state
     * @param window [description]
     */
    void draw(sf::RenderWindow& window) {
        // _drawLower is true, so the lower state is drawn on the background
        window.draw(_logoSprite);
    }

private:
    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;
    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;
};

#endif
