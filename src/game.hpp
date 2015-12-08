#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include <iostream>

#include "settings.hpp"

class GState;

/**
 * Class which is used to hold and access the active game states. Only one instance
 * of this will exist.
 */
class Game
{
public:
    Game();

    void swapActiveState(std::shared_ptr<GState> state);
    void moveToState(std::shared_ptr<GState> state);
    void goToPreviousState();

    void handleEvents();
    void update();
    void draw();

    bool isRunning() const;
    void quit();

    sf::RenderWindow window;

private:
    Settings _settings;
    bool _running;
    std::vector<std::shared_ptr<GState>> _states;
};

#endif
