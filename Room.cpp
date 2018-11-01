#include "SFML/Graphics.hpp"
#include <iostream>
#include "Room.h"

Room::Room(const char* _floor, sf::Sprite& _sprite)
{
	floor = _floor;
	int ran1 = rand() % 2;
	int ran2 = rand() % 2;
	int ran3 = rand() % 2;
	int ran4 = rand() % 2;
	backdrop = {
		Frame(_sprite, 0, (155 * ran1), 233, 155, 1, 1, 0, 0, 1),
		Frame(_sprite, 0, (155 * ran2), 233, 155, -1, 1, 0, 0, 1),
		Frame(_sprite, 0, (155 * ran3), 233, 155, -1, -1, 0, 0, 1),
		Frame(_sprite, 0, (155 * ran4), 233, 155, 1, -1, 0, 0, 1),
	};
	backdrop[1].sprite.setPosition(466, 0);
	backdrop[2].sprite.setPosition(466, 310);
	backdrop[3].sprite.setPosition(0, 310);
}

Room::Room() {};