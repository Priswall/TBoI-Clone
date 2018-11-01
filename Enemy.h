#pragma once
#include "Entity.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Enemy : public Entity
{
public:
	sf::Sound sound;
	std::vector<sf::SoundBuffer> sounds;
	std::vector<Animation> animations;
	sf::Vector2f targetPos;
	EnemyID enemyID;
};