#include <iostream>
#include <SFML/Graphics.hpp>

#include "map.hpp"

#define SEEDPHRASE "Insert random seedphrase here"

int main() {
    sf::RenderWindow window(sf::VideoMode(MAPWIDTH, MAPHEIGHT), "SFML window");
    // window.setVerticalSyncEnabled(true);
    Map map(SEEDPHRASE);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        map.draw(window);
        window.display();
    }
    window.close();
    return 0;
}
