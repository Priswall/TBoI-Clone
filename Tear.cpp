#pragma once
#include "SFML/Graphics.hpp"
#include "Tear.h"

void Tear::update()
{
	frames++;
	if (splat.isPlaying) {
		sprite = splat.frames[0][splat.currentFrame].getSprite();
		sprite.setPosition(pos - splat.frames[0][splat.currentFrame].offSet);
	}
	else {
		pos += vel;
		sprite.setPosition(pos - sf::Vector2f(0, 36 + (range / 5)));
	}
	range -= 0.5;
};

Tear::Tear(sf::Vector2f ppos, sf::Vector2f vvel, double damage, double rrange, TearFlag tf, sf::Sprite& __sprite, Animation& tearSplat)
{
	pos = ppos;
	vel = vvel;
	dmg = damage;
	range = rrange;
	entityID = tear;
	sprite = __sprite;
	sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));

	splat = tearSplat;
};