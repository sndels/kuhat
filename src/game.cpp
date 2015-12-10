#include <list>

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include "game.hpp"
// Include all gamestates
#include "intro.hpp"
#include "m_menu.hpp"
//#include "playstate.hpp"

/**
 * Inits the MainMenu instance and pushes it to the GState-vector
 * @param render window
 */
Game::Game() {
    _resolution.x = _settings.getl("", "resolution.x", 1280);
    _resolution.y = _settings.getl("", "resolution.y", 720);
    _window.create(sf::VideoMode(_resolution.x, _resolution.y), "Kuhat");
    _currentResolution = _resolution;
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
 * Get window events and call the active state to handle them
 */
void Game::handleEvents() {
    sf::Event event;
    while (_window.pollEvent(event) ) {
        _states.back()->handleEvents(*this, event);
    }
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
    // Clear screen to black and draw active and requested lower states
    _window.setActive();
    _window.clear(sf::Color::Black);
    // First check if only the active state needs drawing
    if (!(_states.back()->drawLower())) _states.back()->draw(_window);
    // Else do the more complicated draw-routine
    else {
        // Collect a list of states to draw
        std::list<std::shared_ptr<GState>> list;
        for (auto iterator = _states.rbegin(); iterator != _states.rend(); ++iterator) {
            list.push_front(*iterator);
            // Break loop if we don't need to draw any lower states
            if (!((*iterator)->drawLower()) ) break;
        }
        // Draw states in the collected list
        for (auto iterator = list.begin(); iterator != list.end(); ++iterator) {
            (*iterator)->draw(_window);
        }
    }

    _window.display();
}

/**
 * Checks if game is still running
 * @return boolean running or not
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
 * Restarts the game
 */
void Game::restart() {
    _states.clear();
    moveToState(std::make_shared<Intro>(*this) );
}
