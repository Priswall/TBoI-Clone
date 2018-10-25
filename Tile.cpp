#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Tile.h"

sf::Vector2f Tile::getPos()
{
	return pos;
};

sf::Sprite Tile::getSprite()
{
	return sprite;
};

sf::RectangleShape Tile::getRect()
{
	return rect;
};