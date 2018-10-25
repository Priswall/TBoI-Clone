#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Player.h"

class Item {
public:
	sf::Sprite sprite;
	ItemID id;
	int maxCharges;
	int charges;
	bool isPassive;

	Item(ItemID ID);
	void activate(Player& player);
	void update(Player& player);
};