#ifndef MAP_H
#define MAP_H

#define MAPPATH "resource/map.png"
#define MAPX 1280
#define MAPY 720

#include "map_generator.hpp"

class Map {
public:
    Map(std::string const& seed) {
        _mapMask = generateMap(seed, MAPPATH);
        texture.loadFromFile(MAPPATH);
        _mapSprite.setTexture(texture);
        _mapRender.create(MAPX,MAPY);
        _mapRender.draw(_mapSprite);
        _mapRender.display();
    }

    void draw(sf::RenderWindow &window) {
        window.draw(_mapSprite);
    }

    sf::FloatRect getBounds() {
        return _mapSprite.getGlobalBounds();
    }

    bool doesCollide(int x, int y) {
        return _mapMask[x][y];
    }

    void addHole(int centerX, int centerY, int radius) {
        ;
    }

private:
    sf::Texture texture;
    sf::RenderTexture _mapRender;
    std::vector<std::vector<bool> > _mapMask;
    sf::Sprite _mapSprite;
};
#endif
