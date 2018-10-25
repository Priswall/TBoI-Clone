#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Enums.h"
#include "ItemPedestal.h"

ItemPedestal::ItemPedestal(int x, int y)
{
	pos = sf::Vector2f(x, y);
	entityID = itemPedestal;
};

ItemPedestal::ItemPedestal(int x, int y, ItemID itemId)
{
	pos = sf::Vector2f(x, y);
	entityID = itemPedestal;
	itemID = itemId;
};