#ifndef GSTATE_H
#define GSTATE_H

#include <SFML/Graphics.hpp>

class Game;

class GState
{
public:
    GState() { };
    virtual ~GState() { };

    // Functions to pause and resume the gamestate while changing states.
    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void draw(Game& game) = 0;

    void changeState(Game& game, std::shared_ptr<GState> state) {
		game.changeState(state);
	}

    bool isRunning() const {return _running;}
    void quit() {_running = false;}
protected:
    bool _running;
};

#endif
