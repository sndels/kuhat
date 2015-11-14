#ifndef GSTATE_H
#define GSTATE_H

#include <SFML/Graphics.hpp>

class Game;

class GState
{
public:
    GState() { };
    virtual ~GState() { };

    virtual void handleEvents(sf::Event &event) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    bool isRunning() const {return _running;}
    void quit() {_running = false;}
protected:
    bool _running;
};

#endif
