#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Player.h"
#include "Frame.h"

class Tile
{
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f pos;
	TileID tileID;
	Tile* neighbors[8];
	bool hasSprite = false;
	std::vector<Frame> frames;

	Tile();

	virtual void update(Player &, std::vector<Tear>&) const;

	sf::Vector2f getPos();

	sf::Sprite getSprite();

	sf::RectangleShape getRect();

};