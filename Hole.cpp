#include "Hole.h"

Hole::Hole(int x, int y, HoleID ID, sf::Sprite& txtr)
{
	tileID = wall;
	pos = sf::Vector2f(x, y);
	holeID = ID;
	sprite = txtr;
	sprite.setPosition(pos.x - 2, pos.y - 2);
};

void Hole::update(Player& player, std::vector<Tear>& tears) const
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
}