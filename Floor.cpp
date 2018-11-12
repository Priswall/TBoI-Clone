#include "Floor.h"

void Floor::load(sf::Sprite& sprite, sf::Sprite& _sprite, Animation& anim)
{
	if (!loaded)
	{
		
		startRoom = sf::Vector2f(466 * 2, 0);
		currentRoom = sf::Vector2f(466 * 2, 0);
		rooms.push_back(Room(0, 0, floor, sprite));
		rooms.push_back(Room(466, 0, floor, sprite));
		rooms.push_back(Room(466 * 2, 0, floor, sprite));
		rooms.push_back(Room(466 * 2, 310, floor, sprite));
		rooms.push_back(Room(466 * 3, 310, floor, sprite));
		for (std::vector<Room>::iterator i = rooms.begin(); i != rooms.end(); i++)
		{
			for (std::vector<Room>::iterator j = rooms.begin(); j != rooms.end(); j++)
			{
				if (j->pos.x == i->pos.x - 466 && j->pos.y == i->pos.y)
					i->doors.push_back(Door(i->pos.x + 10, i->pos.y + 187, _normal, left, anim));
				if (j->pos.x == i->pos.x + 466 && j->pos.y == i->pos.y)
					i->doors.push_back(Door(i->pos.x + 456, i->pos.y + 123, _normal, right, anim));
				if (j->pos.x == i->pos.x && j->pos.y == i->pos.y - 310)
					i->doors.push_back(Door(i->pos.x + 201, i->pos.y + 10, _normal, up, anim));
				if (j->pos.x == i->pos.x && j->pos.y == i->pos.y + 310)
					i->doors.push_back(Door(i->pos.x + 265, i->pos.y + 300, _normal, down, anim));
			}
			i->load(_sprite);
		}
		loaded = true;
	}
}

Floor::Floor() {};

Floor::Floor(FloorID _floor)
{
	floor = _floor;
}