#include <iostream>
#include <SFML/Graphics.hpp>

#include "map_generator.hpp"

#define SEEDPHRASE "Random seedphrase"

int main() {
    // sf::RenderWindow window(sf::VideoMode(MAPWIDTH, MAPHEIGHT), "SFML window");
    // window.setVerticalSyncEnabled(true);
    getMap(SEEDPHRASE);
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //     window.clear(sf::Color::Black);
    //     window.display();
    // }
    // window.close();
    return 0;
}
