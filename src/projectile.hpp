#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

/// A virtual Projectile class for different projectile types to inherit from.
class Projectile
{
public:
<<<<<<< HEAD
    Projectile() {   }
=======
    Projectile() {    }
>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505

    sf::Sprite getSprite() const
    {
        return _sprite;
    }

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
<<<<<<< HEAD

=======
>>>>>>> 5aa60212d5fc957dd076315554e88627d513e505
};

#endif
