#include "Entity.h"
#include "SFML/Graphics.hpp"

sf::Vector2f Entity::getPos()
{
	return pos;
};
sf::Sprite Entity::getSprite()
{
	return sprite;
};
sf::IntRect Entity::getRect()
{
	return rect;
};

void Entity::setPos(sf::Vector2f newPos)
{
	pos = newPos;
};
void Entity::setSprite(sf::Sprite newSprite)
{
	sprite = newSprite;
};
void Entity::setRect(sf::IntRect newRect)
{
	rect = newRect;
};