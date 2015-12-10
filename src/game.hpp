#ifndef GAME_H
#define GAME_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include <iostream>

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
    void restart();

private:
    sf::RenderWindow _window;
    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    sf::Vector2i _currentResolution;
    bool _running;
    std::vector<std::shared_ptr<GState>> _states;
};

#endif
