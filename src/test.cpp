#include <iostream>
#include <SFML/Graphics.hpp>

#include "map_generator.hpp"

#define MAPWIDTH 1280
#define MAPHEIGHT 720
#define SEEDPHRASE "Random seeasdfasddphrase"
#define DISPLACEMENT 300
#define ROUGHNESS 0.57

int main() {
    sf::RenderWindow window(sf::VideoMode(MAPWIDTH, MAPHEIGHT), "SFML window");
    window.setVerticalSyncEnabled(true);
    // window.setKeyRepeatEnabled(false);
    std::vector<int> heights = getPoints(SEEDPHRASE, MAPWIDTH, MAPHEIGHT,
                                         DISPLACEMENT, ROUGHNESS);
    for (auto i : heights)
        std::cout << i << std::endl;
    int steps = heights.size();
    std::vector<int> xCoords;
    for (int i = 0; i <= MAPWIDTH; i += MAPWIDTH / (steps - 1))
        xCoords.push_back(i);
    sf::VertexArray lines(sf::LinesStrip, steps);
    for (int i = 0; i < steps; ++i)
        lines[i].position = sf::Vector2f(xCoords[i], heights[i]);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(lines);
        window.display();
    }
    window.close();
    return 0;
}
