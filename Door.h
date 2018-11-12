#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Animation.h"
#include <deque>

class Door : public Entity
{
public:
	DoorID doorID;
	DoorWall doorWall;
	Animation close;
	Animation open;
	Animation unlock;

	Door(int, int, DoorID, DoorWall, Animation);

	void update(std::deque<std::shared_ptr<Entity>>& entities);
};