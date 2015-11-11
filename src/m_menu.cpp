#include "m_menu.hpp"

#define OPTNUM 2 //number of options in menu

/*
 * Initializes all menu items and sets class state to running
 * @params: none
 * @return: none
 */
MainMenu::MainMenu() {
    _running = true;
    std::shared_ptr<Option> newOption = std::make_shared<Option>("resource/sprites/NewGame.png", 0);
    _options.push_back(newOption);
    _selected = 0;
    _options[0]->setSelected();
    newOption = std::make_shared<Option>("resource/sprites/Options.png", 1);
    _options.push_back(newOption);
}

/*
 * Selects the active item according to user input
 * @params: pointer to game
 * @return: none
 */
void MainMenu::handleEvents(Game *game) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {//Moves selection up
        _options[_selected]->setUnselected();
        ++_selected;
        if (_selected == OPTNUM)//Wraps if moved up from first
            _selected = 0;
        _options[_selected]->setSelected();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {//Moves selection down
        _options[_selected]->setUnselected();
        --_selected;
        if (_selected >= OPTNUM)//Wraps if moved down from last
            _selected = OPTNUM - 1;
        _options[_selected]->setSelected();
    }
}

/*
 * Draws all menu items
 * @params: reference to active render window
 * @return: none
 */
void MainMenu::draw(sf::RenderWindow &window)
{
        for (auto i : _options)
            window.draw(i->getSprite());
}
