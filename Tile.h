#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"

class Tile
{
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f pos;
	TileID tileID;

	sf::Vector2f getPos();

	sf::Sprite getSprite();

	sf::RectangleShape getRect();

};