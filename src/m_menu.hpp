#ifndef M_MENU_H
#define M_MENU_H

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into
#include "playstate.hpp"
#include "settingsmenu.hpp"

#define OPTNUM 2 //number of options in menu

/**
 * Game state for the main menu
 */
class MainMenu : public GState
{
public:
    /**
     * Initializes all menu items and sets class state to running
     * @param game  Ref to game-engine
     */
    MainMenu(Game& game) {
        _running = true;
        std::shared_ptr<Option> newOption = std::make_shared<Option>("resource/sprites/NewGame.png", 0);
        _options.push_back(newOption);
        _selected = 0;
        _options[0]->setSelected();
        newOption = std::make_shared<Option>("resource/sprites/Options.png", 1);
        _options.push_back(newOption);
    }

    /**
     * Empty pause as the menu won't be paused
     */
    void pause() {
        ;
    }

    /**
     * Empty resume as the menu won't be paused
     */
    void resume() {
        ;
    }

    /**
     * Event handling
     * @param game  Ref to game-engine
     * @param event Ref to the event
     */
    void handleEvents(Game& game, sf::Event& event) {
        // Check if window is closed
        if (event.type == sf::Event::Closed) {
            game.quit();
            return;
        }

        // Check keypresses
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
            if (event.key.code == sf::Keyboard::Return) {
                if (_selected == 0) game.moveToState(std::make_shared<PlayState>(game) );
                else if (_selected == 1) game.moveToState(std::make_shared<SettingsMenu>(game) );
                return;
            }
        }
    }

    void update(Game& game) {
        ;
    }

    /**
     * Draws all menu items
     * @params Ref to render window
     */
    void draw(sf::RenderWindow& window) {
            for (auto i : _options)
                window.draw(i->getSprite());
    }

    /**
     * Checks if new game is selected
     * @return boolean new game selected or not
     */
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
