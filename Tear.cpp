#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Enums.h"
#include "Tear.h"

void Tear::update()
{
	pos += vel;
	range -= 0.5;
	sprite.setPosition(pos);
};

Tear::Tear(sf::Vector2f ppos, sf::Vector2f vvel, double damage, double rrange, TearFlag tf, sf::Sprite ssprite)
{
	pos = ppos;
	vel = vvel;
	dmg = damage;
	range = rrange;
	entityID = tear;
	sprite = ssprite;
};