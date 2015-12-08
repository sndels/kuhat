#ifndef P_MENU_H
#define P_MENU_H

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into

class PauseMenu : public GState
{
public:
    /**
     * Initializes all menu items and sets class state to running
     * @params: none
     * @return: none
     */
    PauseMenu(Game& game, GState& caller) : _caller(caller) {
        // Logo
        if (!_logoTexture.loadFromFile("resource/sprites/logo.png") ) {
            std::cout << "Logo texture failed to load from file." << std::endl;
        }
        _logoSprite.setTexture(_logoTexture);
        _logoSprite.setPosition(game.settings().getResolution().x/2 - _logoSprite.getGlobalBounds().width/2, 100);
    }

    void pause() {
        ;
    }

    void resume() {
        ;
    }

    /**
     * Selects the active item according to user input
     * @params: reference to sf::Event
     * @return: none
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
                if (event.key.code == sf::Keyboard::Escape) {
                    game.goToPreviousState();
                    return;
                }
            }
        }
    }

    void update(Game& game) {
        ;
    }

    /**
     * Draws all menu items
     * @params: reference to active render window
     * @return: none
     */
    void draw(sf::RenderWindow& window) {
        // Draw the caller screen
        _caller.draw(window);
        window.draw(_logoSprite);
    }

private:
    sf::Sprite _logoSprite;
    sf::Texture _logoTexture;

    GState& _caller;
};

#endif
