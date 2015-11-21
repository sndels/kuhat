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
#define SURFACEDEPTH 6 //Depth of surface color
#define MAPPATH "resource/map_bitmask.png"
#define MAPTEXTURE "resource/sprites/ground.png"

/**
 * Returns randomized heights
 *
 * Uses midpoint displacement with given parameters and xorshift to generate
 * randomized height values for the desired map width
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
 *
 * Generates a b/w -mask from seed and saves it to a .png -file
 *
 * @param seed seed for the prng
 * @return     zero if generated succesfully, -1 for error
 */
int generateMap(std::string const& seed) {
    //Get randomized height coordinates
    std::vector<double> heights = generateHeights(seed, MAPWIDTH, MAPHEIGHT,
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
    sf::Image mapTexture;
    mapTexture.loadFromFile(MAPTEXTURE);
    sf::Image mapMask;
    mapMask.create(MAPWIDTH, MAPHEIGHT, sf::Color::Transparent);
    double height;
    //Loop over the map width and draw the mask
    for (auto i = 0; i < MAPWIDTH; ++i) {
        height = s(i);
        if (!(height < 0) && !(height > MAPHEIGHT)) {
            //Draw border pixel
            mapMask.setPixel(i,height, mapTexture.getPixel(i, height));
            //Fill under border
            for (auto j = height; j < MAPHEIGHT; ++j)
                if (j < height + SURFACEDEPTH)
                    mapMask.setPixel(i, j, sf::Color(139, 69, 19));
                else
                    mapMask.setPixel(i, j, mapTexture.getPixel(i, j));
        }
    }
    //Save the mask to set file
    if (!mapMask.saveToFile(MAPPATH))
        return -1;
    return 0;
}

#endif
