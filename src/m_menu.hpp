#ifndef M_MENU_H
#define M_MENU_H

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"

#define OPTNUM 2 //number of options in menu

class MainMenu : public GState
{
public:
    /**
     * Initializes all menu items and sets class state to running
     * @params: none
     * @return: none
     */
    MainMenu() {
        _running = true;
        std::shared_ptr<Option> newOption = std::make_shared<Option>("resource/sprites/NewGame.png", 0);
        _options.push_back(newOption);
        _selected = 0;
        _options[0]->setSelected();
        newOption = std::make_shared<Option>("resource/sprites/Options.png", 1);
        _options.push_back(newOption);
    }

    /**
     * Selects the active item according to user input
     * @params: reference to sf::Event
     * @return: none
     */
    void handleEvents(sf::Event &event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {//Moves selection up
                if (_selected != 0) {
                    _options[_selected]->setUnselected();
                    --_selected;
                    _options[_selected]->setSelected();
                }
            }
            if (event.key.code == sf::Keyboard::Down) {//Moves selection down
                if (_selected != OPTNUM - 1) {
                    _options[_selected]->setUnselected();
                    ++_selected;
                    _options[_selected]->setSelected();
                }
            }
        }
    }

    void update() {
        ;
    }

    /**
     * Draws all menu items
     * @params: reference to active render window
     * @return: none
     */
    void draw(sf::RenderWindow &window)
    {
            for (auto i : _options)
                window.draw(i->getSprite());
    }

    bool newSelected() {
        if (_selected == 0)
            return true;
        else
            return false;
    }
private:
    std::vector<std::shared_ptr<Option>> _options;
    unsigned int _selected;
};

#endif
