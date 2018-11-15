#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Tile.h"

sf::Vector2f Tile::getPos()
{
	return pos;
};

std::vector<Frame> Tile::getFrames()
{
	return frames;
};

sf::Sprite Tile::getSprite()
{
	return sprite;
};

sf::RectangleShape Tile::getRect()
{
	return rect;
};

Tile::Tile() {};

void Tile::update(Player& player, std::vector<Tear>& tears) const
{
	return;
}