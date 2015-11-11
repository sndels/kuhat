#include "game.hpp"
#include "m_menu.hpp"

/*
 * Inits the MainMenu instance and pushes it to the GState-vector
 * @params: active render window
 * @return: none
 */
Game::Game(sf::RenderWindow &window) : _window(window) {
    _running = true;
    std::shared_ptr<GState> mainMenu = std::make_shared<MainMenu>();
    this->pushState(mainMenu);
}

/*
 * Pops the top GState and sets given state in it's place
 * @params: GState to be added
 * @return: none
 */
void Game::changeState(std::shared_ptr<GState> state) {
    this->popState();
    this->pushState(state);
}

/*
 * Pushes the given state as active state
 * @params: GState to be added
 * @return: none
 */
void Game::pushState(std::shared_ptr<GState> state) {
    _states.insert(_states.begin(),state);
}

/*
 * Pops the top GState
 * @params: none
 * @return: none
 */
void Game::popState() {
    _states.erase(_states.begin());
}

/*
 * Checks for closing of window and calls all active states for event handling
 * @params: none
 * @return: none
 */
void Game::handleEvents() {
    sf::Event event;
    while (_window.pollEvent(event))
    {
        // Request for closing the _window
        if (event.type == sf::Event::Closed)
            _running = false;
            return;
    }
    for (auto i : _states)
        i->handleEvents(event);
}

/*
 * Draws all active states
 * @params: none
 * @return: none
 */
void Game::draw() {
    _window.setActive();
    _window.clear(sf::Color::Black);
    for (auto i : _states)
        i->draw(this->_window);
    _window.display();
}

/*
 * Checks if game is still running
 * @params: none
 * @return: true if game is running, false if not
 */
bool Game::isRunning() const {
    return _running;
}

/*
 * Sets the game to quit
 * @params: none
 * @return: none
 */
void Game::quit() {
    _running = false;
}
