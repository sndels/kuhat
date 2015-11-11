#ifndef LOGO_H
#define LOGO_H

#include <SFML/Graphics.hpp>
#include <string>

//class for the main logo, facilitates animation
class Logo
{
public:
	Logo(std::string t) {
		_texture.loadFromFile(t);
		_sprite.setTexture(_texture);
		_sprite.setPosition(220,150);
	}

	sf::Sprite getSprite() const
	{
		return _sprite;
	}
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif
