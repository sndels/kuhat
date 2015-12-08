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

    virtual void handleEvents(Game& game, sf::Event& event) = 0;
    virtual void update(Game& game) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void moveToState(Game& game, std::shared_ptr<GState> state) {
		game.moveToState(state);
	}

    void swapActiveState(Game& game, std::shared_ptr<GState> state) {
		game.swapActiveState(state);
	}

    void goToPreviousState(Game& game) {
		game.goToPreviousState();
	}

    /**
     * Returns info if the state expects the lower state to be drawn also
     * @return True if lower state should be drawn aswell.
     */
    bool drawLower() {
        return _drawLower;
    }

    bool isRunning() const {return _running;}
    void quit() {_running = false;}
protected:
    bool _running;
    bool _drawLower = false;
};

#endif
