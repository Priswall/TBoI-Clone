#pragma once
#include "Wall.h"
#include "Hole.h"
#include <iostream>
#include <deque>
#include "tinyxml2.h"
#include "Door.h"
#include "Enemy.h"

class Room{
public:
	int roomNumber;
	tinyxml2::XMLDocument doc;
	sf::Vector2f pos;
	std::deque<std::shared_ptr<Tile>> tiles;
	std::vector<Hole> holes;
	std::deque<std::shared_ptr<Enemy>> entities;
	std::vector<Frame> backdrop;
	std::vector<Frame> frames;
	std::vector<Frame> holeFrames;
	std::vector<Door> doors;
	bool loaded = false, hasLeftDoor = false, hasRightDoor = false, hasUpDoor = false, hasDownDoor = false, firstEnter = false, cleared = false;
	
	FloorID floor;
	const char* roomSize;

	void load(sf::Sprite&, sf::Sprite&);
	void update(Player&, std::vector<Tear>&);

	Room() {};
	Room(int, int, FloorID, sf::Sprite&);

	Room (const Room&);
	Room operator=(const Room&);
};