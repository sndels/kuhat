#include "game.hpp"
// Include all gamestates
#include "intro.hpp"
#include "m_menu.hpp"
//#include "playstate.hpp"

/**
 * Inits the MainMenu instance and pushes it to the GState-vector
 * @params: active render window
 * @return: none
 */
Game::Game(sf::RenderWindow &window) : window(window) {
    _running = true;
    _states.clear();
    this->moveToState(std::make_shared<Intro>() );

}

/**
 * Pops the last (active) GState and sets given state in it's place
 * @param state GState to be added
 */
void Game::swapActiveState(std::shared_ptr<GState> state) {
    if (!_states.empty()) {
        this->goToPreviousState();
        this->swapActiveState(state);
    }
    else {
        this->swapActiveState(state);
    }
}

/**
 * Pushes the given state as active state
 * @param state GState to be pushed to vector.
 */
void Game::moveToState(std::shared_ptr<GState> state) {
    _states.push_back(state);
}

/**
 * Pops the last (active) state from the vector
 */
void Game::goToPreviousState() {
    if (!_states.empty()) {
        _states.pop_back();
    }
}

/**
 * Calls the active state for event handling
 */
void Game::handleEvents() {
    _states.back()->handleEvents(*this);
}

/**
 * Updates the active state
 */
void Game::update() {
    _states.back()->update(*this);
}

/**
 * Clears the screen to black and calls the active state for drawing
 */
void Game::draw() {
    window.setActive();
    window.clear(sf::Color::Black);
    _states.back()->draw(*this);
    window.display();
}

/**
 * Checks if game is still running
 * @return: true if game is running, false if not
 */
bool Game::isRunning() const {
    return _running;
}

/**
 * Sets the game to quit
 */
void Game::quit() {
    _running = false;
}
