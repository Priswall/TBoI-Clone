#include "Wall.h"

Wall::Wall(int x, int y, WallID ID, sf::Sprite& txtr)
{
	tileID = wall;
	pos = sf::Vector2f(x, y);
	id = ID;
	frames = {
		Frame(txtr, 0, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 32, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 64, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 0, 96, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 32, 96, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 0, 128, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(txtr, 32, 128, 32, 32, 1, 1, 0, 0, 0, 0, 0)
	};
	sprite = frames[(rand() % 3)].getSprite();
	sprite.setPosition(pos.x - 2, pos.y - 2);
};

void Wall::update(Player& player, std::vector<Tear>& tears) const
{
	//Top collision detection
	if (player.pos.x + player.rect.width > pos.x + (player.maxSpeed - player.vel.x) &&
		player.pos.x + player.rect.left < (pos.x + 27) - (player.maxSpeed + player.vel.x) &&
		player.pos.y - player.rect.height < pos.y + player.maxSpeed &&
		player.pos.y - player.rect.height > pos.y &&
		player.vel.y >= 0)
	{
		player.pos.y = pos.y + player.rect.height;
		player.vel.y = 0;
	}

	//Bottom collision detection
	if (player.pos.x + player.rect.width > pos.x + (player.maxSpeed - player.vel.x) &&
		player.pos.x + player.rect.left < (pos.x + 27) - (player.maxSpeed + player.vel.x) &&
		player.pos.y + player.rect.top < pos.y + 27 &&
		player.pos.y + player.rect.top > pos.y + (27 - player.maxSpeed) &&
		player.vel.y <= 0)
	{
		player.pos.y = pos.y + 27 - player.rect.top;
		player.vel.y = 0;
	}

	//Left side collision detection
	if (player.pos.x + player.rect.width < pos.x + player.maxSpeed &&
		player.pos.x + player.rect.width > pos.x &&
		player.pos.y + player.rect.top < (pos.y + 27) - (player.maxSpeed + player.vel.y) &&
		player.pos.y - player.rect.height > pos.y + (player.maxSpeed - player.vel.y) &&
		player.vel.x >= 0)
	{
		player.pos.x = pos.x + player.rect.left;
		player.vel.x = 0;
	}

	//Right side collision detection
	if (player.pos.x + player.rect.left < pos.x + 27 &&
		player.pos.x + player.rect.left > pos.x + (27 - player.maxSpeed) &&
		player.pos.y + player.rect.top < (pos.y + 27) - (player.maxSpeed + player.vel.y) &&
		player.pos.y - player.rect.height > pos.y + (player.maxSpeed - player.vel.y) &&
		player.vel.x <= 0)
	{
		player.pos.x = pos.x + player.rect.width + 27;
		player.vel.x = 0;
	}

	for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end(); tearIter++)
	{
		if (tearIter->pos.x + 10 < pos.x + 27 && tearIter->pos.y - 16 < pos.y + 27 && tearIter->pos.x + 18 > pos.x && tearIter->pos.y - 8 > pos.y)
		{
			tearIter->splat.isPlaying = true;
		}
	}
};