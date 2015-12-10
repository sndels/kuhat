#ifndef MAP_H
#define MAP_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#define HOLERADIUS 40
#define MAPPATH "resource/map.png"

#include "map_generator.hpp"
#include <cmath>

class Map {
public:
    Map(std::string const& seed) : _holeMask(HOLERADIUS) {
        _resolution.x = _settings.getl("", "resolution.x", 1280);
        _resolution.y = _settings.getl("", "resolution.y", 720);
        _holeMask.setFillColor(sf::Color::Transparent);
        _holeMask.setOrigin(HOLERADIUS, HOLERADIUS);
        generateMap(seed, MAPPATH);
        _texture.loadFromFile(MAPPATH);
        _sprite.setTexture(_texture);
        _render.create(_resolution.x, _resolution.y);
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

    void addHole(int centerX, int centerY, float radius = HOLERADIUS) {
        //Move the hole mask and draw the hole
        _holeMask.move(centerX - _holeMask.getPosition().x, centerY - _holeMask.getPosition().y);
        _holeMask.setScale(radius/HOLERADIUS,radius/HOLERADIUS);
        _render.draw(_holeMask, sf::BlendMultiply);
        _render.display();
        _sprite.setTexture(_render.getTexture());
        //Update the map mask
        for (int i = centerX - radius; i <= centerX + radius; ++i) {
            for (int j = centerY - radius; j <= centerY + radius; ++j) {
                if (sqrt((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY)) < radius) {
                    if ((i >= 0) && (i < _resolution.x) && (j >= 0) && (j < _resolution.y))
                        _mask[i][j] = false;
                }
            }
        }
        _holeMask.setScale(HOLERADIUS/radius,HOLERADIUS/radius);
    }

private:
    minIni _settings = minIni("settings.ini");
    sf::Vector2i _resolution;

    sf::Texture _texture;
    sf::RenderTexture _render;
    std::vector<std::vector<bool> > _mask;
    sf::Sprite _sprite;
    sf::CircleShape _holeMask;
};
#endif
