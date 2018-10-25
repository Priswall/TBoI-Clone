#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <iostream>
#include "Tile.h"
#include "Wall.h"


Wall::Wall(int x, int y, WallID ID, sf::Sprite& txtr)
{
	tileID = wall;
	pos = sf::Vector2f(x, y);
	id = ID;
	frames = {
		Frame(txtr, 0, 0, 32, 32, 1, 1, 0, 0, 0),
		Frame(txtr, 32, 0, 32, 32, 1, 1, 0, 0, 0),
		Frame(txtr, 64, 0, 32, 32, 1, 1, 0, 0, 0)
	};
	sprite = frames[rand() % 3].getSprite();
	sprite.setPosition(pos);
};

void Wall::update(Player& player)
{
	//Top collision detection
	if (player.pos.x + player.rect.width > pos.x + (player.maxSpeed - player.vel.x) && player.pos.x + player.rect.left < pos.x + ((32 + player.vel.x) - (player.maxSpeed + player.vel.x)) && player.pos.y + player.rect.height < pos.y + 10 && player.pos.y + player.rect.height > pos.y)
	{
		player.pos.y = pos.y + player.rect.top;
		player.vel.y = 0;
	}

	//Bottom collision detection
	if (player.pos.x + player.rect.width > pos.x + ((player.maxSpeed + 0.5) - player.vel.x) && player.pos.x + player.rect.left < pos.x + ((32 + player.vel.x) - (player.maxSpeed + player.vel.x)) && player.pos.y + player.rect.top < pos.y + 32 && player.pos.y + player.rect.top > pos.y + 22)
	{
		player.pos.y = pos.y + player.rect.height + 32;
		player.vel.y = 0;
	}

	//Left side collision detection
	if (player.pos.x + player.rect.width < pos.x + 5 && player.pos.x + player.rect.width > pos.x && player.pos.y + player.rect.top < pos.y + ((32 + player.vel.y) - (player.maxSpeed + player.vel.y)) && player.pos.y + player.rect.height > pos.y + (player.maxSpeed - player.vel.y))
	{
		player.pos.x = pos.x + player.rect.left;
		player.vel.x = 0;
	}

	//Right side collision detection
	if (player.pos.x + player.rect.left < pos.x + 32 && player.pos.x + player.rect.left > pos.x + 27 && player.pos.y + player.rect.top < pos.y + ((32 + player.vel.y) - (player.maxSpeed + player.vel.y)) && player.pos.y + player.rect.height > pos.y + (player.maxSpeed - player.vel.y))
	{
		player.pos.x = pos.x + player.rect.width + 32;
		player.vel.x = 0;
	}
};