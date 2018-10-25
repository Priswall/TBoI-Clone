#include "SFML/Graphics.hpp"
#include "Frame.h"

Frame::Frame(sf::Sprite _sprite, int x, int y, int w, int h, double scalex, double scaley, int xoff, int yoff, int _frames)
{
	sprite = _sprite;
	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	sprite.scale(scalex, scaley);
	offSet = sf::Vector2f(xoff, yoff);
	frames = _frames;
}

sf::Sprite Frame::getSprite()
{
	return sprite;
}