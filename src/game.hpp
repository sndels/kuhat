#ifndef GAME_H
#define GAME_H

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
    Game(sf::RenderWindow &window);

    void changeState(std::shared_ptr<GState> state);
    void pushState(std::shared_ptr<GState> state);
    void popState();

    void handleEvents();
    void update();
    void draw();

    bool isRunning() const;
    void quit();
private:
    sf::RenderWindow &_window;
    bool _running;
    std::vector<std::shared_ptr<GState>> _states;
};

#endif
