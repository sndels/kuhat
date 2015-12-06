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
 * Pops the top GState and sets given state in it's place
 * @params: GState to be added
 */
void Game::changeState(std::shared_ptr<GState> state) {
    this->popState();
    this->pushState(state);
}

/**
 * Pushes the given state as active state
 * @params: GState to be added
 */
void Game::pushState(std::shared_ptr<GState> state) {
    _states.insert(_states.begin(),state);
}

/**
 * Pops the top GState
 */
void Game::popState() {
    _states.erase(_states.begin());
}

/**
 * Calls the top state for event handling
 */
void Game::handleEvents() {
    _states[0]->handleEvents(*this);
}

/**
 * Updates the top state
 */
void Game::update() {
    _states[0]->update(*this);
}

/**
 * Clears the screen to black and calls the top state for drawing
 */
void Game::draw() {
    window.setActive();
    window.clear(sf::Color::Black);
    _states[0]->draw(*this);
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
