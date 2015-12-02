#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


/**
 * Check collisions between two objects, one moving and the other stationary
 * @param  moving     the object to be moved
 * @param  stationary the stationary object
 * @param  dX         how much the moving object is going to move on x-axis
 * @param  dY         how much the moving object is going to move on y-axis
 * @return            boolean true if there is a collision, false if not
 */
template<typename T, typename V>
bool checkCollision(T const& moving, V const& stationary, float dX = 0.0, float dY = 0.0) {
    //Get necessary rects
    sf::FloatRect intersection;
    sf::FloatRect movingBounds = moving.getSprite().getGlobalBounds();
    sf::FloatRect stationaryBounds = stationary.getSprite().getGlobalBounds();
    //Check if the given objects collide
    if (movingBounds.intersects(stationaryBounds,intersection)) {
        //Loop over the pixels in the collision
        for (auto i = intersection.left; i <= intersection.left + intersection.width; ++i) {
            for (auto j = intersection.top; j <= intersection.top + intersection.height; ++j) {
                //Check if both objects have an opaque pixel in the spot
                if (moving.doesCollide(i - movingBounds.left,j - movingBounds.top) &&
                    stationary.doesCollide(i + dX - stationaryBounds.left,j + dY - stationaryBounds.top))
                    return true;
            }
        }
    }
    return false;
}
#endif
