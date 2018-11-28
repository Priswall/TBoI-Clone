#pragma once
#include "Room.h"

class Floor {
public:
	FloorID floor;
	sf::Vector2f startRoom;
	sf::Vector2f currentRoom;
	std::vector<Room> rooms;
	bool loaded = false;
	sf::Texture texture;

	Floor();
	Floor(FloorID);
	void load(sf::Sprite&, sf::Sprite&, sf::Sprite&, Animation&);
};