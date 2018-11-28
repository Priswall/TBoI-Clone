#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"

class Entity {
public:
	sf::IntRect rect;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f vel;
	EntityID entityID;
	int frames = 0;
	bool alive = true;

	sf::Vector2f getPos();
	sf::Sprite getSprite();
	sf::IntRect getRect();

	void setPos(sf::Vector2f);
	void setSprite(sf::Sprite);
	void setRect(sf::IntRect);

};