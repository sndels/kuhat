#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

/// A virtual Projectile class for different projectile types to inherit from.
class Projectile
{
public:
    Projectile() {   }

    const sf::Sprite& getSprite() const
    {
        return _sprite;
    }

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif
