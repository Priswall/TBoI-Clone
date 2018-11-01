#pragma once
#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "Entity.h"
#include "Frame.h"
#include <iostream>

class Room{
public:
	std::vector<Tile> tiles;
	std::vector<Entity> entities;
	std::vector<Frame> backdrop;
	const char* floor;

	Room();
	Room(const char*, sf::Sprite&);
};