#include "game.hpp"
/*
 * Main loop
 * Initializes the game and intro screen and calls game to handle logic and
 * drawing
 */
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML window");
    window.setVerticalSyncEnabled(true);
    Game game(window);
    while (game.isRunning()) {
        game.handleEvents();
        game.draw();
    }
    window.close();
    return 0;
}
