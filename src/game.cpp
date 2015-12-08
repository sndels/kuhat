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
Game::Game() {
    _window.create(sf::VideoMode(_settings.getResolution().x, _settings.getResolution().y), "Kuhat");
    _currentResolution = _settings.getResolution();
    _window.setVerticalSyncEnabled(true);
    // window.setKeyRepeatEnabled(false);
    _running = true;
    _states.clear();
    this->moveToState(std::make_shared<Intro>(*this) );

}

/**
 * Pops the last (active) GState and sets given state in it's place
 * @param state GState to be added
 */
void Game::swapActiveState(std::shared_ptr<GState> state) {
    if (!_states.empty()) {
        this->goToPreviousState();
        this->moveToState(state);
    }
    // Shouldn't happen but in case there is no active state to swap FROM
    else {
        this->moveToState(state);
    }
}

/**
 * Pushes the given state as active state
 * @param state GState to be pushed to vector.
 */
void Game::moveToState(std::shared_ptr<GState> state) {
    // Pause the current active state if there is one
    if (!_states.empty() ) _states.back()->pause();
    _states.push_back(state);
}

/**
 * Pops the last (active) state from the vector
 */
void Game::goToPreviousState() {
    if (!_states.empty()) {
        _states.pop_back();
        // Resume the new active state if there is one
        if (!_states.empty() ) _states.back()->resume();
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
    // Recreate the game window if resolution setting has changed
    if (_currentResolution != _settings.getResolution() ) {
        _window.create(sf::VideoMode(_settings.getResolution().x, _settings.getResolution().y), "Kuhat");
        _window.setVerticalSyncEnabled(true);
        _currentResolution = _settings.getResolution();
    }
    _window.setActive();
    _window.clear(sf::Color::Black);
    _states.back()->draw(_window);
    _window.display();
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

/**
 * Used to get reference to game settings.
 * @return Ref to game resstings
 */
Settings& Game::settings() {
    return _settings;
}
