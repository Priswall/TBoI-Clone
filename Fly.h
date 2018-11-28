#pragma once
#include "Enemy.h"
#include "Player.h"

class Fly : public Enemy
{
public:
	int timer = 0, t = 0;
	double acc = 0.01;
	Fly(int, int, Animation&);

	void update(Player&, std::deque<std::shared_ptr<Tile>>) override;
};