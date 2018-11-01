#include "Fly.h"
#include <iostream>

Fly::Fly(int x, int y, Animation& anim)
{
	pos = sf::Vector2f(x, y);
	anim.loop = true;
	anim.isPlaying = true;
	animations.push_back(anim);
	acc = 0.1;
}

void Fly::update(Player& player)
{
	animations[0].play();
	sprite = animations[0].frames[animations[0].currentFrame].getSprite();

	targetPos = player.pos;

	t--;
	if (animations[0].currentFrame == 1)
		timer++;
	if (timer % 20 == 0)
		t = 9;
	if(t > 0)
		vel += sf::Vector2f((rand() % 3) - 1, (rand() % 3) - 1);
	if (vel.x < -2)
		vel.x = -2;
	if (vel.x > 2)
		vel.x = 2;
	if (vel.y < -2)
		vel.y = -2;
	if (vel.y > 2)
		vel.y = 2;
	if (t <= 0)
	{
		if (vel.x > 0)
			vel.x -= acc;
		if (vel.x < 0)
			vel.x += acc;
		if (vel.y > 0)
			vel.y -= acc;
		if (vel.y < 0)
			vel.y += acc;
	}

	sf::Vector2f dpos = pos - targetPos;
	double mag = sqrt(dpos.x * dpos.x + dpos.y * dpos.y);
	sf::Vector2f tempvel = sf::Vector2f((dpos.x / mag) * 0.2, (dpos.y / mag) * 0.2);

	pos += sf::Vector2f(vel.x / 3, vel.y / 3) - tempvel;
	if (pos.x < 22)
		pos.x = 22;
	if (pos.x > 429)
		pos.x = 429;
	if (pos.y < 22)
		pos.y = 22;
	if (pos.y > 250)
		pos.y = 250;
	sprite.setPosition(pos - animations[0].frames[animations[0].currentFrame].offSet);
}