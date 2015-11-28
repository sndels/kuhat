#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
template<typename T, typename V>
bool checkCollision(T small, V big) {
    sf::FloatRect intersection;
    sf::FloatRect smallBounds = small.getBounds();
    sf::FloatRect bigBounds = big.getBounds();
    if (smallBounds.intersects(bigBounds,intersection)) {
        for (auto i = intersection.left; i < intersection.left + intersection.width; ++i) {
            for (auto j = intersection.top; j < intersection.top + intersection.height; ++j) {
                if (small.doesCollide(i - intersection.left,j - intersection.top) &&
                    big.doesCollide(i - intersection.left,j - intersection.top))
                    return true;
            }
        }
    }
    return false;
}
#endif
