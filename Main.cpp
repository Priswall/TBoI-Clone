#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include "Enums.h"
#include "Wall.h"
#include "Tear.h"
#include "Animation.h"

int frames = 0;
bool loaded = false;
sf::Sprite sprite;
Player player1;

std::vector<Wall> walls;
std::vector<Entity> entities;
std::vector<Tear> tears;
sf::Texture texture;
sf::Texture texture1;
std::vector<sf::SoundBuffer> sounds;
std::vector<sf::Sprite> images;
sf::Music song;
sf::Music layer;
sf::Sound sound;

int map[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1
};

void loadmap()
{
	for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
	{
		switch (map[i])
		{
		case 0:
			break;
		case 1:
			walls.push_back(Wall(round(i % 9) * 32, round(floor(i / 9) * 32), test, images[1]));
			break;
		case 2:
			break;
		}
	}
}

void load()
{

	tears.reserve(500);

	//Load images
	texture1.loadFromFile("resources/gfx/isaac.png");
	sprite.setTexture(texture1);
	images.push_back(sprite);
	texture.loadFromFile("resources/gfx/rocks.png");
	sprite.setTexture(texture);
	images.push_back(sprite);

	//Load sounds and music
	sf::SoundBuffer s;
	s.loadFromFile("resources/sfx/splatter 0.wav");
	sounds.push_back(s);
	s.loadFromFile("resources/sfx/splatter 1.wav");
	sounds.push_back(s);
	s.loadFromFile("resources/sfx/splatter 2.wav");
	sounds.push_back(s);

	song.openFromFile("resources/music/burning basement intro.ogg");
	song.setVolume(30);
	song.play();
	layer.openFromFile("resources/music/burning basement layer.ogg");
	song.setVolume(50);

	player1 = Player(45, 45, first, images[0]);

	loadmap();
}

int main()
{

	//This stuff is mainly to setup the window and initialize variables

	sf::RenderWindow window(sf::VideoMode(800, 600), "The Binding of Isaac: Clonebirth", sf::Style::Titlebar | sf::Style::Close);

	window.setVerticalSyncEnabled(true);
	sf::RenderTexture maint;

	if (!loaded) {

		std::thread loadingThread(load);
		loadingThread.join();

		maint.create(400, 300);
		loaded = true;

	}

	while (window.isOpen())
	{
		frames++;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//This code bracket checks for keyboard/mouse inputs
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && layer.getStatus() == sf::Music::Status::Stopped)
			{
				layer.setPlayingOffset(song.getPlayingOffset());
				layer.play();
			}
			else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && layer.getStatus() == sf::Music::Status::Playing)
			{
				layer.stop();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		//This code bracket renders and updates everything
		{

			maint.clear();


			if (song.getStatus() == sf::Music::Status::Stopped)
			{
				song.openFromFile("resources/music/burning basement loop.ogg");
				song.setLoop(true);
				song.play();
			}

			player1.update(tears);

			for (std::vector<Wall>::iterator wallIter = walls.begin(); wallIter != walls.end(); wallIter++)
			{
				wallIter->update(player1);
			}

			/*
			for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end();)
			{
				
				if (tearIter->range <= 0)
				{
					int random = rand() % 3;
					sound.setBuffer(sounds[random]);
					sound.setLoop(false);
					sound.play();
					tearIter = tears.erase(tearIter);
				}
				else
				{
					tearIter->update();
					tearIter++;
				}
			}
			*/

			for (std::vector<Wall>::iterator wallIter = walls.begin(); wallIter != walls.end(); wallIter++)
			{
				maint.draw(wallIter->getSprite());
			}

			for (std::vector<Entity>::iterator entIter = entities.begin(); entIter != entities.end(); entIter++)
			{
				maint.draw(entIter->getSprite());
			}
			/*
			for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end(); tearIter++)
			{
				maint.draw(tearIter->getSprite());
			}
			*/

			sf::RectangleShape rect(sf::Vector2f(player1.rect.width * 2, player1.rect.height * 2));
			rect.setPosition(sf::Vector2f(player1.pos.x + player1.rect.left, player1.pos.y + player1.rect.top));
			rect.setFillColor(sf::Color::Green);
			maint.draw(rect);
			maint.draw(player1);

			//This code bracked handles the GUI
			{
			}

		}


		maint.display();

		const sf::Texture& maintexture = maint.getTexture();
		sf::Sprite sprite(maintexture);
		sprite.scale(window.getSize().x / maint.getSize().x, window.getSize().y / maint.getSize().y);
		window.draw(sprite);
		window.display();
	}

	return 0;
}