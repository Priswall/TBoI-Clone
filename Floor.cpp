#include "Floor.h"

void Floor::load(sf::Sprite& sprite, sf::Sprite& _sprite, sf::Sprite& holeSprite, Animation& anim)
{
	if (!loaded)
	{
		//////////////////////////////////////////////////////////////////
		////  LESSON LEARENED: NEVER HAVE ROOMS WITH NO NEIGHBORS!!!  ////
		////  IT TOOK ME FOREVER TO FIGURE OUT WHERE THE PROBLEM WAS  ////
		////                     WHEN IT HAPPENED                     ////
		//////////////////////////////////////////////////////////////////
		startRoom = sf::Vector2f(0, 0);
		currentRoom = sf::Vector2f(0, 0);
		rooms.push_back(Room(-466, -310, floor, sprite));
		rooms.push_back(Room(-466, 0, floor, sprite));
		rooms.push_back(Room(0, 0, floor, sprite));
		rooms.push_back(Room(466, 0, floor, sprite));
		rooms.push_back(Room(2 * 466, 0, floor, sprite));
		rooms.push_back(Room(2 * 466, 310, floor, sprite));

		////////////////////////////////////////////////////////
		////  LEAVE THIS SPACE FOR RANDOM FLOOR GENERATION  ////
		////////////////////////////////////////////////////////

		//Load doors for neighboring rooms
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
			i->load(_sprite, holeSprite);
		}
		loaded = true;
	}
}

Floor::Floor() {};

Floor::Floor(FloorID _floor)
{
	//Determine what type of floor you are on so the floor can generate differently
	floor = _floor;
}