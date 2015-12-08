#include "game.hpp"

/**
 * Main loop
 * Initializes the game and intro screen and calls game to handle logic and
 * drawing
 */
int main()
{
    Game game;
    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.draw();
    }
    return 0;
}
