#pragma once
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include <thread>
#include <iostream>
#include "Entity.h"
#include "Tear.h"
#include "Frame.h"
#include "Animation.h"


class Player : public Entity, public sf::Drawable {
public:
	void update(std::vector<Tear>&);

	Player(int, int, PlayerID, sf::Sprite&, Animation&);
	Player() {};
	PlayerID id;
	sf::Sprite headSprite;
	sf::Texture tearTexture;
	Animation tearPoof;
	Animation walkUp;
	Animation walkDown;
	Animation walkLeft;
	Animation walkRight;
	Animation headUp;
	Animation headDown;
	Animation headLeft;
	Animation headRight;
	Animation idle;
	double damage = 3.5, range = 25.0, Reload = 10.0, reload = 10.0, maxSpeed = 2.0, acc = 0.15;
	bool up = false, down = false, left = false, right = false;
private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};