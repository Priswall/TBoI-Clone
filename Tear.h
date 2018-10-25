#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Enums.h"

class Tear : public Entity
{
public:
	sf::Vector2f vel;
	double dmg, range;
	TearFlag tearFlag;

	void update();

	Tear(sf::Vector2f, sf::Vector2f, double, double, TearFlag, sf::Sprite);
};