#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Player.h"
#include "Item.h"

Item::Item(ItemID ID)
{
	id = ID;
	switch (id)
	{
	case cryingOnion:
	case cricketsHead:
		isPassive = true;
		break;
	case bookOfBelial:
	case necronomicon:
		isPassive = false;
		break;
	}
};
void Item::activate(Player& player)
{
	switch (id)
	{
	case bookOfBelial:

		break;
	}
};
void Item::update(Player& player)
{
	switch (id)
	{
	case cryingOnion:

		break;
	}
};