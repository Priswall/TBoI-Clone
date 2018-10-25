#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Enums.h"

class ItemPedestal : public Entity {
public:
	int itemID;
	ItemPedestal(int x, int y);

	ItemPedestal(int x, int y, ItemID itemId);
	void update() {};
};