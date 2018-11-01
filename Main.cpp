#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include "Wall.h"
#include "Tear.h"
#include "Room.h"
#include "Fly.h"

int frames = 0;
bool loaded = false;
sf::Sprite sprite;
Player player1;

std::vector<Wall> walls;
std::vector<Entity> entities;
std::vector<Tear> tears;
std::vector<sf::Sprite> sprites;
sf::Texture texture;
sf::Texture texture1;
sf::Texture texture2;
sf::Texture texture3;
sf::Texture texture4;
std::vector<Fly> flies;
std::vector<sf::SoundBuffer> sounds;
std::vector<sf::Sprite> images;
sf::Music song;
sf::Music layer;
sf::Sound sound;
std::vector<Animation> animations;
Room room;

int map[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
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
			walls.push_back(Wall((round(i % 13) * 28) + 49, (round(floor(i / 13) * 29)) + 52, test, images[1]));
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
	texture2.loadFromFile("resources/gfx/basement_backdrop.png");
	sprite.setTexture(texture2);
	images.push_back(sprite);
	texture3.loadFromFile("resources/gfx/tearpoof.png");
	sprite.setTexture(texture3);
	std::vector<Frame> temp = {
		Frame(sprite, 0, 0, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 64, 0, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 128, 0, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 192, 0, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 64, 64, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 128, 64, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 192, 64, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 0, 128, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 64, 128, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 128, 128, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 192, 128, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 0, 192, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 64, 192, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 128, 192, 64, 64, 1, 1, 16, 48, 1),
		Frame(sprite, 192, 192, 64, 64, 1, 1, 16, 48, 20),
		Frame(sprite, 192, 192, 64, 64, 1, 1, 16, 48, 1),
	};
	Animation tempAnim;
	tempAnim.load(temp);
	animations.push_back(tempAnim);

	texture4.loadFromFile("resources/gfx/enemies/fly.png");
	sprite.setTexture(texture4);
	temp = {
		Frame(sprite, 0, 0, 32, 32, 0.8, 0.8, 16, 30, 2),
		Frame(sprite, 32, 0, 32, 32, 0.8, 0.8, 16, 30, 2)
	};
	tempAnim.load(temp);
	animations.push_back(tempAnim);


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

	player1 = Player(100, 100, first, images[0], animations[0]);
	room = Room("Basement", images[2]);

	flies.push_back(Fly(200, 200, animations[1]));

	loadmap();
}

int main()
{

	//This stuff is mainly to setup the window and initialize variables

	sf::RenderWindow window(sf::VideoMode(932, 620), "The Binding of Isaac: Clonebirth", sf::Style::Titlebar | sf::Style::Close);

	window.setVerticalSyncEnabled(true);
	sf::RenderTexture maint;

	if (!loaded) {

		std::thread loadingThread(load);
		loadingThread.join();

		maint.create(466, 310);
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
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && layer.getStatus() == sf::Music::Status::Playing)
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

			sprites.clear();

			if (song.getStatus() == sf::Music::Status::Stopped)
			{
				song.openFromFile("resources/music/burning basement loop.ogg");
				song.setLoop(true);
				song.play();
			}

			player1.update(tears);

			for (std::vector<Wall>::iterator wallIter = walls.begin(); wallIter != walls.end(); wallIter++)
			{
				wallIter->update(player1, tears);
			}

			for (std::vector<Fly>::iterator flyIter = flies.begin(); flyIter != flies.end(); flyIter++)
			{
				flyIter->update(player1);
			}

			for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end();)
			{
				if (!tearIter->splat.isFinished)
				{
					tearIter->update();
					tearIter->splat.play();
					if (!tearIter->splat.isPlaying && tearIter->range < 0 && !tearIter->splat.isFinished)
					{
						int random = rand() % 3;
						sound.setBuffer(sounds[random]);
						sound.setLoop(false);
						sound.play();
						tearIter->splat.isPlaying = true;
					}
					tearIter++;
				}
				else
					tearIter = tears.erase(tearIter);
			}

			for (std::vector<Frame>::iterator roomIter = room.backdrop.begin(); roomIter != room.backdrop.end(); roomIter++)
			{
				maint.draw(roomIter->sprite);
			}

			for (std::vector<Wall>::iterator wallIter = walls.begin(); wallIter != walls.end(); wallIter++)
			{
				maint.draw(wallIter->getSprite());
			}

			for (std::vector<Entity>::iterator entIter = entities.begin(); entIter != entities.end(); entIter++)
			{
				maint.draw(entIter->getSprite());
			}

			for (std::vector<Fly>::iterator flyIter = flies.begin(); flyIter != flies.end(); flyIter++)
			{
				maint.draw(flyIter->getSprite());
			}

			for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end(); tearIter++)
			{
				maint.draw(tearIter->getSprite());
			}

			maint.draw(player1);

			//This code bracked handles the GUI
			{
			}

		}

		maint.display();

		const sf::Texture& maintexture = maint.getTexture();
		sf::Sprite sprite(maintexture);
		sprite.scale((window.getSize().x / maint.getSize().x), (window.getSize().y / maint.getSize().y));
		window.draw(sprite);
		window.display();
	}

	return 0;
}