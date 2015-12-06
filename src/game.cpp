#include "game.hpp"
// Include all gamestates
#include "m_menu.hpp"
#include "playstate.hpp"

/**
 * Inits the MainMenu instance and pushes it to the GState-vector
 * @params: active render window
 * @return: none
 */
Game::Game(sf::RenderWindow &window) : window(window) {
    _running = true;
    std::shared_ptr<GState> mainMenu = std::make_shared<MainMenu>();
    this->pushState(mainMenu);
    //  Comment the two lines above and uncomment the ones before to enter playstate on run
    //    std::shared_ptr<GState> playState = std::make_shared<PlayState>();
    //    this->pushState(playState);

}

/**
 * Pops the last (active) GState and sets given state in it's place
 * @param state GState to be added
 */
void Game::changeState(std::shared_ptr<GState> state) {
    if (!_states.empty()) {
        this->popState();
        this->pushState(state);
    }
    else {
        this->pushState(state);
    }
}

/**
 * Pushes the given state as active state
 * @param state GState to be pushed to vector.
 */
void Game::pushState(std::shared_ptr<GState> state) {
    _states.push_back(state);
}

/**
 * Pops the last (active) state from the vector
 */
void Game::popState() {
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
