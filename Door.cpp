#include "Door.h"
#include <iostream>

Door::Door(int x, int y, DoorID _doorID, DoorWall _doorWall, Animation animation)
{
	pos = sf::Vector2f(x, y);
	doorID = _doorID;
	doorWall = _doorWall;
	open = animation;
}

void Door::update(std::deque<std::shared_ptr<Entity>>& entities)
{
	if (entities.size() == 0)
	{
		if (!open.isFinished)
		{
			open.isPlaying = true;
			open.play();
			sprite = open.sprite;
			sprite.setPosition(pos);
			if (doorWall == left)
				sprite.setRotation(-90);
			else if (doorWall == right)
				sprite.setRotation(90);
			else if (doorWall == down)
				sprite.setRotation(180);
		}
	}
}