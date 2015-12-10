#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

/**
 * Check collisions between two objects, one moving and the other stationary
 * @param  moving     the object to be moved
 * @param  stationary the stationary object
 * @param  dX         how much the moving object is going to move on x-axis
 * @param  dY         how much the moving object is going to move on y-axis
 * @return            boolean collision or not
 */
template<typename T, typename V>
sf::Vector2f checkCollision(T const& moving, V const& stationary, float dX = 0.0, float dY = 0.0) {
    //Get necessary rects
    sf::FloatRect intersection;
    sf::FloatRect movingBounds = moving.getSprite().getGlobalBounds();
    movingBounds.left += dX;
    movingBounds.top += dY;
    sf::FloatRect stationaryBounds = stationary.getSprite().getGlobalBounds();
    //Check if the given objects collide
    if (movingBounds.intersects(stationaryBounds,intersection)) {
        //Loop over the pixels in the collision
        for (auto i = intersection.left; i < intersection.left + intersection.width; ++i) {
            for (auto j = intersection.top; j < intersection.top + intersection.height; ++j) {
                //Check if both objects have an opaque pixel in the spot
                if (moving.doesCollide(i - movingBounds.left,j - movingBounds.top) &&
                    stationary.doesCollide(i - stationaryBounds.left,j - stationaryBounds.top))
                    return sf::Vector2f(i,j);
            }
        }
    }
    return sf::Vector2f(0,0);
}
#endif
