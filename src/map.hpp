#ifndef MAP_H
#define MAP_H

#define MAPPATH "resource/map.png"
#define MAPX 1280
#define MAPY 720
#define HOLERADIUS 40

#include "map_generator.hpp"
#include <cmath>

class Map {
public:
    Map(std::string const& seed) : _holeMask(HOLERADIUS) {
        _holeMask.setFillColor(sf::Color::Transparent);
        _holeMask.setOrigin(HOLERADIUS, HOLERADIUS);
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

    void addHole(int centerX, int centerY) {
        //Move the hole mask and draw the hole
        _holeMask.move(centerX - _holeMask.getPosition().x, centerY - _holeMask.getPosition().y);
        _render.draw(_holeMask, sf::BlendMultiply);
        _render.display();
        _sprite.setTexture(_render.getTexture());
        //Update the map mask
        for (int i = centerX - HOLERADIUS; i <= centerX + HOLERADIUS; ++i) {
            for (int j = centerY - HOLERADIUS; j <= centerY + HOLERADIUS; ++j) {
                if (sqrt((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY)) < HOLERADIUS) {
                    if ((i >= 0) && (i < MAPX) && (j >= 0) && (j < MAPY))
                        _mask[i][j] = false;
                }
            }
        }
    }

private:
    sf::Texture _texture;
    sf::RenderTexture _render;
    std::vector<std::vector<bool> > _mask;
    sf::Sprite _sprite;
    sf::CircleShape _holeMask;
};
#endif
