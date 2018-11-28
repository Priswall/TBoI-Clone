#pragma once
#include "Player.h"
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <deque>

class Enemy : public Entity
{
public:
	sf::Sound sound;
	std::vector<sf::SoundBuffer> sounds;
	std::vector<Animation> animations;
	sf::Vector2f targetPos;
	EnemyID enemyID;

	Enemy() {};

	virtual void update(Player&, std::deque<std::shared_ptr<Tile>>);
};