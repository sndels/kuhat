#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
template<typename T, typename V>
bool checkCollision(T small, V big) {
    sf::FloatRect intersection;
    sf::FloatRect smallBounds = small.getSprite().getGlobalBounds();
    sf::FloatRect bigBounds = big.getSprite().getGlobalBounds();
    if (smallBounds.intersects(bigBounds,intersection)) {
        for (auto i = intersection.left; i < intersection.left + intersection.width; ++i) {
            for (auto j = intersection.top; j < intersection.top + intersection.height; ++j) {
                if (small.doesCollide(i - smallBounds.left,j - smallBounds.top) &&
                    big.doesCollide(i - bigBounds.left,j - bigBounds.top))
                    return true;
            }
        }
    }
    return false;
}
#endif
