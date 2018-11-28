#pragma once
#include "Tile.h"

class Hole : public Tile
{
public:
	HoleID holeID;

	Hole() {};
	Hole(int, int, HoleID, sf::Sprite&);

	void update(Player&, std::vector<Tear>&) const override;
};