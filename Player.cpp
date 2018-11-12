#pragma once
#include "Player.h"

void Player::update(std::vector<Tear>& tears)
{

	//This code bracket controls player movement
	{

		bodySprite = walkDown.frames[0][0].getSprite();
		bodySprite.setPosition(0, 11);
		headSprite = headDown.frames[0][0].getSprite();

		up = false;
		down = false;
		left = false;
		right = false;

		pos += vel;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			up = true;
			if (walkDown.isPlaying)
				walkDown.stop();
			walkUp.isPlaying = true;
			walkUp.play();
			bodySprite = walkUp.frames[0][walkUp.currentFrame].getSprite();
			bodySprite.setPosition(0, 11);
			headSprite = headUp.frames[0][0].getSprite();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			down = true;
			if (walkUp.isPlaying)
				walkUp.stop();
			walkDown.isPlaying = true;
			walkDown.play();
			bodySprite = walkDown.frames[0][walkDown.currentFrame].getSprite();
			bodySprite.setPosition(0, 11);
			headSprite = headDown.frames[0][0].getSprite();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			left = true;
			if (walkRight.isPlaying)
				walkRight.stop();
			walkLeft.isPlaying = true;
			walkLeft.play();
			bodySprite = walkLeft.frames[0][walkLeft.currentFrame].getSprite();
			bodySprite.setPosition(-walkLeft.frames[0][0].offSet.x * 2, 11);
			headSprite = headLeft.frames[0][0].getSprite();
			headSprite.setPosition(-headLeft.frames[0][0].offSet.x * 2, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			right = true;
			if (walkLeft.isPlaying)
				walkLeft.stop();
			walkRight.isPlaying = true;
			walkRight.play();
			bodySprite = walkRight.frames[0][walkRight.currentFrame].getSprite();
			bodySprite.setPosition(0, 11);
			headSprite = headRight.frames[0][0].getSprite();
		}

		if (up)
		{
			vel.y -= acc;
			if (vel.y < -maxSpeed)
			{
				vel.y = -maxSpeed;
			}
		}
		if (down)
		{
			vel.y += acc;
			if (vel.y > maxSpeed)
			{
				vel.y = maxSpeed;
			}
		}
		if (left)
		{
			vel.x -= acc;
			if (vel.x < -maxSpeed)
				vel.x = -maxSpeed;
		}
		if (right)
		{
			vel.x += acc;
			if (vel.x > maxSpeed)
				vel.x = maxSpeed;
		}

		if (!left && !right)
		{
			if (vel.x > 0)
			{
				vel.x -= acc;
			}
			if (vel.x < 0)
			{
				vel.x += acc;
			}
		}
		if (!up && !down)
		{
			if (vel.y > 0)
			{
				vel.y -= acc;
			}
			if (vel.y < 0)
			{
				vel.y += acc;
			}
		}

		if (abs(vel.x) < acc)
		{
			vel.x = 0;
		}
		if (abs(vel.y) < acc)
		{
			vel.y = 0;
		}

		if (vel.x == 0 && vel.y == 0)
		{
			if (walkLeft.isPlaying)
				walkLeft.stop();
			if (walkRight.isPlaying)
				walkRight.stop();
			if (walkDown.isPlaying)
				walkDown.stop();
			if (walkUp.isPlaying)
				walkUp.stop();
		}
	}

	//This code block controls shooting and reloading
		sf::Sprite tearSprite;
		tearSprite.setTexture(tearTexture);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (reload >= Reload)
			{
				reload = 0;
				headUp.isPlaying = true;
			}
			if (headUp.isPlaying)
			{
				headUp.play();
				if (headUp.frame == 4 && headUp.currentFrame == 0)
					tears.push_back(Tear(sf::Vector2f(pos.x - 8, pos.y), sf::Vector2f((vel.x / 1.5), (vel.y / 3) - 5), damage, range, normal, tearSprite, tearPoof));
				headSprite = headUp.frames[0][headUp.currentFrame].getSprite();
			}
			else
			{
				headSprite = headUp.frames[0][0].getSprite();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (reload >= Reload)
			{
				reload = 0;
				headDown.isPlaying = true;
			}
			if (headDown.isPlaying)
			{
				headDown.play();
				if (headDown.frame == 4 && headDown.currentFrame == 0)
					tears.push_back(Tear(sf::Vector2f(pos.x - 8, pos.y), sf::Vector2f((vel.x / 1.5), (vel.y / 3) + 5), damage, range, normal, tearSprite, tearPoof));
				headSprite = headDown.frames[0][headDown.currentFrame].getSprite();
			}
			else
			{
				headSprite = headDown.frames[0][0].getSprite();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (reload >= Reload)
			{
				reload = 0;
				headLeft.isPlaying = true;
			}
			if (headLeft.isPlaying)
			{
				headLeft.play();
				if (headLeft.frame == 4 && headLeft.currentFrame == 0)
					tears.push_back(Tear(sf::Vector2f(pos.x - 16, pos.y), sf::Vector2f((vel.x / 3) - 5, (vel.y / 1.5)), damage, range, normal, tearSprite, tearPoof));
				headSprite = headLeft.frames[0][headLeft.currentFrame].getSprite();
				headSprite.setPosition(-headLeft.frames[0][headLeft.currentFrame].offSet.x * 2, 0);
			}
			else
			{
				headSprite = headLeft.frames[0][0].getSprite();
				headSprite.setPosition(-headLeft.frames[0][0].offSet.x * 2, 0);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (reload >= Reload)
			{
				reload = 0;
				headRight.isPlaying = true;
			}
			if (headRight.isPlaying)
			{
				headRight.play();
				if (headRight.frame == 4 && headRight.currentFrame == 00)
					tears.push_back(Tear(sf::Vector2f(pos.x - 8, pos.y), sf::Vector2f((vel.x / 3) + 5, (vel.y / 1.5)), damage, range, normal, tearSprite, tearPoof));
				headSprite = headRight.frames[0][headRight.currentFrame].getSprite();
			}
			else
			{
				headSprite = headRight.frames[0][0].getSprite();
			}
		}

		if (reload < Reload) {
			reload += 0.4;
		}
};

Player::Player(int x, int y, PlayerID ID, sf::Sprite& txtr, Animation& tearSplat)
{
	entityID = player;
	pos = sf::Vector2f(x, y);
	id = ID;
	rect = sf::IntRect(-7, -8, 7, 1);
	maxSpeed = 2.5;
	acc = 0.15;

	std::vector< std::vector<Frame>> temp = { {
		Frame(txtr, 224, 0, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 192, 0, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 224, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 192, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 160, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 128, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 96, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 64, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 32, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 0, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4)
	} };
	walkUp.load(temp);
	temp = { {
		Frame(txtr, 0, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 32, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 64, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 96, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 128, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 160, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 192, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 224, 32, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 192, 0, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 224, 0, 32, 32, 1, 1, 0, 0, 0, 27, 4)
	} };
	walkDown.load(temp);
	temp = { {
		Frame(txtr, 0, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 32, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 64, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 96, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 128, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 160, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 192, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 224, 64, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 0, 96, 32, 32, -1, 1, 32, 0, 0, 27, 4),
		Frame(txtr, 32, 96, 32, 32, -1, 1, 32, 0, 0, 27, 4)
	} };
	walkLeft.load(temp);
	temp = { {
		Frame(txtr, 0, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 32, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 64, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 96, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 128, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 160, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 192, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 224, 64, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 0, 96, 32, 32, 1, 1, 0, 0, 0, 27, 4),
		Frame(txtr, 32, 96, 32, 32, 1, 1, 0, 0, 0, 27, 4)
	} };
	walkRight.load(temp);

	temp = { {
		Frame(txtr, 128, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4),
		Frame(txtr, 160, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4)
	} };
	headUp.load(temp);
	temp = { {
		Frame(txtr, 0, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4),
		Frame(txtr, 32, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4)
	} };
	headDown.load(temp);
	temp = { {
		Frame(txtr, 64, 0, 32, 32, -1.0, 1.0, 32, 0, 0, -5, 4),
		Frame(txtr, 96, 0, 32, 32, -1.0, 1.0, 32, 0, 0, -5, 4)
	} };
	headLeft.load(temp);
	temp = { {
		Frame(txtr, 64, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4),
		Frame(txtr, 96, 0, 32, 32, 1, 1, 16, 28, 0, -5, 4)
	} };
	headRight.load(temp);

	tearTexture.loadFromFile("resources/gfx/tears.png");
	tearPoof = tearSplat;
};

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RenderTexture tar;
	tar.create(32, 64);
	tar.clear(sf::Color::Transparent);
	tar.draw(bodySprite);
	tar.draw(headSprite);
	tar.display();

	sf::Sprite s;
	s.setTexture(tar.getTexture());
	s.setPosition(pos.x - 16, pos.y - 40);
	target.draw(s, states);
};