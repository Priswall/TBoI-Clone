#pragma once
#include <iostream>
#include "Tear.h"


class Player : public Entity, public sf::Drawable {
public:
	bool mobile = true;
	void update(std::vector<Tear>&);

	Player(int, int, PlayerID, sf::Sprite&, Animation&);
	Player() {};
	PlayerID id;
	sf::Sprite headSprite;
	sf::Sprite bodySprite;
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