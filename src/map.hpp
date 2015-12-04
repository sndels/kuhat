#ifndef MAP_H
#define MAP_H

#define MAPPATH "resource/map.png"
#define MAPX 1280
#define MAPY 720

#include "map_generator.hpp"

class Map {
public:
    Map(std::string const& seed) {
        generateMap(seed, MAPPATH);
        _texture.loadFromFile(MAPPATH);
        _sprite.setTexture(_texture);
        _render.create(MAPX,MAPY);
        _render.draw(_sprite);
        _render.display();
        sf::Image temp;
        temp.loadFromFile(MAPPATH);
        std::vector<bool> v;
        for (unsigned int i = 0; i < temp.getSize().x; ++i) {
            v.clear();
            for (unsigned int j = 0; j < temp.getSize().y; ++j) {
                if (temp.getPixel(i,j).a == 0)
                    v.push_back(false);
                else
                    v.push_back(true);
            }
            _mask.push_back(v);
        }
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(_sprite);
    }

    sf::Sprite getSprite() const {
        return _sprite;
    }

    bool doesCollide(unsigned int x, unsigned int y) const {
        if ((x < _mask.size()) && (y < _mask[x].size()))
            return _mask[x][y];
        return false;
    }

    void addHole(int centerX, int centerY, int radius) {
        ;
    }

private:
    sf::Texture _texture;
    sf::RenderTexture _render;
    std::vector<std::vector<bool> > _mask;
    sf::Sprite _sprite;
};
#endif
