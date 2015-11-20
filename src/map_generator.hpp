#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H

#include <vector>
#include <iostream>
#include "xorshift.hpp"

/**
 * Gives randomized coordinates for map drawing
 *
 * Uses midpoint displacement at highest even division for the given width
 */
std::vector<int> getPoints(std::string const &seed, int width, int const &height,
                            int displacement, float roughness) {
    Xorshift xors(seed);
    std::vector<int> heights;
    //Get start and end coordinates
    heights.push_back(height/2 + xors.random() * displacement);
    heights.push_back(height/2 + xors.random() * displacement);
    //Make sure the division is even
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



#endif
