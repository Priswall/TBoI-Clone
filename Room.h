#pragma once
#include "Wall.h"
#include <iostream>
#include <deque>
#include "tinyxml2.h"
#include "Door.h"

class Room{
public:
	tinyxml2::XMLDocument doc;
	sf::Vector2f pos;
	std::deque<std::shared_ptr<Tile>> tiles;
	std::vector<Entity> baseEntities;
	std::vector<Entity> entities;
	std::vector<Frame> backdrop;
	std::vector<Frame> frames;
	std::vector<Door> doors;
	bool hasLeftDoor = false, hasRightDoor = false, hasUpDoor = false, hasDownDoor = false, firstEnter = false, cleared = false;
	
	FloorID floor;
	const char* roomSize;

	void load(sf::Sprite&);
	void update(Player&, std::vector<Tear>&);

	Room() {};
	Room(int, int, FloorID, sf::Sprite&);

	Room (const Room&);
	Room operator=(const Room&);
};