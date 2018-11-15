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
	int neighbors[8];
	bool hasSprite;
	std::vector<Frame> frames;

	Tile();

	virtual void update(Player &, std::vector<Tear>&) const;

	sf::Vector2f getPos();

	std::vector<Frame> getFrames();

	sf::Sprite getSprite();

	sf::RectangleShape getRect();

};