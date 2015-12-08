#ifndef M_MENU_H
#define M_MENU_H

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"
// include all gamestates you want to move or swap into
#include "playstate.hpp"

#define OPTNUM 2 //number of options in menu

class MainMenu : public GState
{
public:
    /**
     * Initializes all menu items and sets class state to running
     * @params: none
     * @return: none
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

    void pause() {
        ;
    }

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
                game.moveToState(std::make_shared<PlayState>(game) );
                return;
            }
        }
    }

    void update(Game& game) {
        ;
    }

    /**
     * Draws all menu items
     * @params: reference to active render window
     * @return: none
     */
    void draw(sf::RenderWindow& window) {
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
