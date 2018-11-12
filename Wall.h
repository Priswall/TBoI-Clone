#pragma once
#include "Player.h"
#include "Tile.h"

class Wall : public Tile {
public:
	WallID id;

	Wall() {};
	Wall(int, int, WallID, sf::Sprite&);

	void update(Player&, std::vector<Tear>&) const override;
};