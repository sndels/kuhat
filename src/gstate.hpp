#ifndef GSTATE_H
#define GSTATE_H

#include <SFML/Graphics.hpp>

class Game;

/**
 * Virtual class from which all game states inherit from
 */
class GState
{
public:
    /**
     * GState constructor
     */
    GState() { };
    /**
     * Virtual destructor
     */
    virtual ~GState() { };

    /**
     * Pauses the state
     */
    virtual void pause() = 0;
    /**
     * Resumes the state
     */
    virtual void resume() = 0;

    /**
     * Handles sf::Event for the state
     * @param game  active game state
     * @param event event to be processed
     */
    virtual void handleEvents(Game& game, sf::Event& event) = 0;
    /**
     * Updates the state
     * @param game active game instance
     */
    virtual void update(Game& game) = 0;
    /**
     * Draws the state
     * @param window render window
     */
    virtual void draw(sf::RenderWindow& window) = 0;

    /**
     * Moves to given game state
     * @param game  active game instance
     * @param state state to activate
     */
    void moveToState(Game& game, std::shared_ptr<GState> state) {
		game.moveToState(state);
	}

    /**
     * Switches to given game state
     * @param game  active game instance
     * @param state state to activate
     */
    void swapActiveState(Game& game, std::shared_ptr<GState> state) {
		game.swapActiveState(state);
	}

    /**
     * Switches to the previous state
     * @param game active game instance
     */
    void goToPreviousState(Game& game) {
		game.goToPreviousState();
	}

    /**
     * Returns info if the state expects the lower state to be drawn also
     * @return True if lower state should be drawn aswell.
     */
    bool drawLower() const {
        return _drawLower;
    }

    bool isRunning() const {return _running;}
    void quit() {_running = false;}
protected:
    bool _running;
    bool _drawLower = false;
};

#endif
