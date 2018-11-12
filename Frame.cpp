#include "SFML/Graphics.hpp"
#include "Frame.h"

Frame::Frame(sf::Sprite& _sprite, int x, int y, int w, int h, double scalex, double scaley, int originx, int originy, int xoff, int yoff, int _frames)
{
	sprite = _sprite;
	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	origin = sf::Vector2f(originx, originy);
	offSet = sf::Vector2f(xoff, yoff);
	sprite.setOrigin(origin);
	sprite.scale(scalex, scaley);
	sprite.setPosition(origin);
	frames = _frames;
}

sf::Sprite Frame::getSprite()
{
	return sprite;
}