#pragma once
#include "SFML/Graphics.hpp"

class Frame
{
public:
	sf::Vector2f offSet, origin;
	sf::Sprite sprite;
	int frames;
	Frame(sf::Sprite&, int, int, int, int, double, double, int, int, int, int, int);

	sf::Sprite getSprite();
};