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
        ;
    }
};

#endif
