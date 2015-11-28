#ifndef MAP_H
#define MAP_H

#define MAPPATH "resource/map.png"
#define MAPX 1280
#define MAPY 720

#include "map_generator.hpp"

class Map {
public:
    Map(std::string const& seed) {
        if (generateMap(seed, MAPPATH) < 0)
            std::cout << "Error generating map" << std::endl;
        // sf::Texture texture;
        texture.loadFromFile(MAPPATH);
        _mapSprite.setTexture(texture);
        _mapRender.create(MAPX,MAPY);
        _mapRender.draw(_mapSprite);
        _mapRender.display();
    }

    void draw(sf::RenderWindow &window) {
        window.draw(_mapSprite);
    }

    bool doesCollide(sf::Sprite const& check) {
        return true;
    }

    void addHole(int centerX, int centerY, int radius) {
        ;
    }

private:
    sf::Texture texture;
    sf::RenderTexture _mapRender;
    sf::Sprite _mapSprite;
};
#endif
