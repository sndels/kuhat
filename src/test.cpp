#include <iostream>
#include <SFML/Graphics.hpp>

#include "map_generator.hpp"

#define SEEDPHRASE "Random seedphrase"

int main() {
    sf::RenderWindow window(sf::VideoMode(MAPWIDTH, MAPHEIGHT), "SFML window");
    // window.setVerticalSyncEnabled(true);
    generateMap(SEEDPHRASE);
    sf::RenderTexture mapRender;
    mapRender.create(1280,720);
    sf::Texture mapTexture;
    mapTexture.loadFromFile("resource/map_bitmask.png");
    sf::Sprite mapSprite(mapTexture);
    mapSprite.setScale(1, 1);
    mapSprite.setPosition(0, 0);
    mapRender.draw(mapSprite);
    mapRender.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sf::Sprite(mapRender.getTexture()));
        window.display();
    }
    window.close();
    return 0;
}
