#ifndef M_MENU_H
#define M_MENU_H

#include <vector>
#include "gstate.hpp"
#include "m_option.hpp"

class MainMenu : public GState
{
public:
    MainMenu();

    virtual void handleEvents(Game *game);
    virtual void draw(sf::RenderWindow &window);
private:
    std::vector<std::shared_ptr<Option>> _options;
    unsigned int _selected;
    bool _running;
};

#endif
