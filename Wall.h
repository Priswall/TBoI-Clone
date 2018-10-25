#pragma once
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <iostream>
#include "Tile.h"
#include "Frame.h"

class Wall : public Tile {
public:
	WallID id;
	std::vector<Frame> frames;

	Wall(int, int, WallID, sf::Sprite&);

	void update(Player&);
};