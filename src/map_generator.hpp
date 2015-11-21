#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../resource/libs/spline.hpp"
#include "xorshift.hpp"

#define MAPWIDTH 1280
#define MAPHEIGHT 720
#define DISPLACEMENT 250
#define ROUGHNESS 0.5
#define MAPPATH "resource/map_bitmask.png"

/**
 * Gives randomized coordinates for map drawing
 *
 * Uses midpoint displacement at highest even division for the given width
 */
std::vector<double> getHeights(std::string const &seed, int width, int const &height,
                            int displacement, float roughness) {
    Xorshift xors(seed);
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

int getMap(std::string const& seed) {
    //Get randomized height coordinates
    std::vector<double> heights = getHeights(seed, MAPWIDTH, MAPHEIGHT,
                                         DISPLACEMENT, ROUGHNESS);
    //Get amount of heights generated
    int steps = heights.size();
    //Create x-coordinates to pair with heights
    std::vector<double> xCoords;
    for (int i = 0; i <= MAPWIDTH; i += MAPWIDTH / (steps - 1))
        xCoords.push_back(i);
    //Set up the spline-lib interpolation
    tk::spline s;
    s.set_points(xCoords, heights);
    sf::Image mapMask;
    mapMask.create(MAPWIDTH, MAPHEIGHT, sf::Color::Black);
    double height;
    for (auto i = 0; i < MAPWIDTH; ++i) {
        height = s(i);
        if (!(height < 0) && !(height > MAPHEIGHT)) {
            //Draw border pixel
            mapMask.setPixel(i,height, sf::Color::White);
            //Fill "under" border
            for (auto j = height; j < MAPHEIGHT; ++j)
                mapMask.setPixel(i,j, sf::Color::White);
        }
    }
    if (!mapMask.saveToFile(MAPPATH))
        return -1;
    return 0;
}

#endif
