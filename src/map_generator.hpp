#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H

// minIni ini-parser lib
#include "../resource/libs/minIni/minIni.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../resource/libs/spline.hpp"
#include "xorshift.hpp"

#define DISPLACEMENT 250
#define ROUGHNESS 0.5
#define SURFACEDEPTH 6 //Depth of surface color
#define MAPTEXTURE "resource/sprites/ground.png"

/**
 * Returns randomized heights
 * Uses midpoint displacement with given parameters and xorshift to generate
 * randomized height values for the desired map width. Also randomizes roughness
 * and height differences.
 *
 * @param seed         seed for the prng
 * @param width        map width
 * @param height       max height
 * @param displacement max deviation for the midpoints
 * @param roughness    coefficient for change in displacement as step gets smaller
 * @return             generated height values
 */
std::vector<double> generateHeights(std::string const& seed, int width, int const& height,
                            int displacement, float roughness) {
    Xorshift xors(seed);
    displacement += xors.random() * 40;
    roughness += xors.random() * 0.2;
    std::vector<double> heights;
    //Get start and end coordinates
    heights.push_back(height/2 + xors.random() * displacement);
    heights.push_back(height/2 + xors.random() * displacement);
    //Make sure the division is even and displacement big enough to matter
    while ((width % 2 == 0) && (displacement > 10)) {
        width /= 2;
        //Midpoint displacement. Assigning i from insert to prevent invalidating
        for (auto i = heights.begin(); i + 1 != heights.end();
             i = 1 + heights.insert(i + 1, (*i + *(i + 1)) / 2 + xors.random() *
                                   displacement));
        displacement *= roughness;
    }
    return heights;
}


/**
 * Map generator -function
 * Generates map from seed and saves it to a .png -file
 *
 * @param seed seed for the prng
 * @return     zero if generated succesfully, -1 for error
 */
void generateMap(std::string const& seed, std::string const& mapPath) {
    minIni _settings = minIni("settings.ini");
    int _mapWidth = _settings.getl("", "resolution.x", 1280);
    int _mapHeight = _settings.getl("", "resolution.y", 720);
    //Get randomized height coordinates
    std::vector<double> heights = generateHeights(seed, _mapWidth, _mapHeight,
                                         DISPLACEMENT, ROUGHNESS);
    //Get amount of heights generated
    int steps = heights.size();
    //Create x-coordinates to pair with heights
    std::vector<double> xCoords;
    for (int i = 0; i <= _mapWidth; i += _mapWidth / (steps - 1))
        xCoords.push_back(i);
    //Set up the spline-lib interpolation
    tk::spline s;
    s.set_points(xCoords, heights);
    sf::Image mapTexture;
    mapTexture.loadFromFile(MAPTEXTURE);
    sf::Image map;
    map.create(_mapWidth, _mapHeight, sf::Color::Transparent);
    double height;
    std::vector<std::vector<bool> > mask;
    std::vector<bool> temp;
    //Loop over the map width, draw the map
    for (auto i = 0; i < _mapWidth; ++i) {
        height = s(i);
        temp.clear();
        for (auto j = height; j < _mapHeight; ++j) {
            if (j > height + SURFACEDEPTH)
                map.setPixel(i, j, mapTexture.getPixel(i, j));
            else
                map.setPixel(i, j, sf::Color(139, 69, 19));
        }
    }
    //Save the map to set file
    map.saveToFile(mapPath);
}

#endif
