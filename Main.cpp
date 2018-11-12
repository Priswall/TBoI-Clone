#include "SFML/Audio.hpp"
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include "Wall.h"
#include "Room.h"
#include "Fly.h"
#include "Floor.h"

int frames = 0;
bool loaded = false;
sf::Sprite sprite;
Player player1;

std::vector<Wall> walls;
std::deque<std::shared_ptr<Entity>> entities;
std::vector<Tear> tears;
std::vector<sf::Sprite> sprites;
std::vector<Fly> flies;
std::vector<sf::SoundBuffer> sounds;
std::vector<sf::Sprite> images;
std::vector<Animation> animations;
sf::Texture texture;
sf::Texture texture1;
sf::Texture texture2;
sf::Texture texture3;
sf::Texture texture4;
sf::Texture texture5;
Animation open;
sf::Music song;
sf::Music layer;
sf::Sound sound;
sf::Vector2f cam;
sf::Vector2f camTransition;
sf::Vector2f roomTransition;
double volume = 0.0;
Floor _floor;
Room room;

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
	std::vector<std::vector<Frame>> temp = { {
		Frame(sprite, 0, 0, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 64, 0, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 128, 0, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 192, 0, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 64, 64, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 128, 64, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 192, 64, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 0, 128, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 64, 128, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 128, 128, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 192, 128, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 0, 192, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 64, 192, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 128, 192, 64, 64, 1, 1, 16, 48, 0, 0, 1),
		Frame(sprite, 192, 192, 64, 64, 1, 1, 16, 48, 0, 0, 20),
		Frame(sprite, 192, 192, 64, 64, 1, 1, 16, 48, 0, 0, 1),
	} };
	Animation tempAnim;
	tempAnim.load(temp);
	animations.push_back(tempAnim);

	texture5.loadFromFile("resources/gfx/grid/door.png");
	sf::Sprite doorSprite;
	doorSprite.setTexture(texture5);
	std::vector<std::vector<Frame>> tempF = {
		{
			Frame(doorSprite, 64, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 1.1, 0.9, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 1.2, 0.8, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 0.8, 1.2, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 0.9, 1.1, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 4),
			Frame(doorSprite, 64, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2)
		},
		{
			Frame(doorSprite, 64, 48, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 1.1, 0.9, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 1.2, 0.8, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 0.8, 1.2, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 0.9, 1.1, 32, 42, 32, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 4),
			Frame(doorSprite, 64, 48, 64, 48, 0.68, 1.0, 32, 42, 36, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 0.37, 1.0, 32, 42, 40, 42, 2),
			Frame(doorSprite, 64, 48, 64, 48, 0.05, 1.0, 32, 42, 44, 42, 2)
		},
		{
			Frame(doorSprite, 0, 48, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 1.1, 0.9, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 1.2, 0.8, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 0.8, 1.2, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 0.9, 1.1, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 4),
			Frame(doorSprite, 0, 48, 64, 48, 0.68, 1.0, 32, 42, 28, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 0.37, 1.0, 32, 42, 24, 42, 2),
			Frame(doorSprite, 0, 48, 64, 48, 0.05, 1.0, 32, 42, 20, 42, 2),
		},
		{
			Frame(doorSprite, 0, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 0, 64, 48, 1.1, 0.9, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 0, 64, 48, 1.2, 0.8, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 0, 64, 48, 0.8, 1.2, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 0, 64, 48, 0.9, 1.1, 32, 42, 32, 42, 2),
			Frame(doorSprite, 0, 0, 64, 48, 1.0, 1.0, 32, 42, 32, 42, 4)
		}
	};
	open.load(tempF);

	texture4.loadFromFile("resources/gfx/enemies/fly.png");
	sprite.setTexture(texture4);
	temp = { {
		Frame(sprite, 0, 0, 32, 32, 0.8, 0.8, 16, 24, 0, -4, 2),
		Frame(sprite, 32, 0, 32, 32, 0.8, 0.8, 16, 24, 0, -4, 2)
	} };
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

	_floor = Floor(basement);
	_floor.load(images[2], images[1], open);

	player1 = Player(_floor.startRoom.x + 233, _floor.startRoom.y + 155, first, images[0], animations[0]);
	cam = sf::Vector2f(player1.pos);
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
		cam = -_floor.currentRoom;
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

		song.setVolume(volume * 100);
		layer.setVolume(volume * 100);

		//This code bracket checks for keyboard/mouse inputs
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
			{
				volume += 0.1;
				if (volume > 1.0)
					volume = 1.0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
			{
				volume -= 0.1;
				if (volume < 0.0)
					volume = 0.0;
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
				layer.openFromFile("resources/music/burning basement layer.ogg");
				layer.setLoop(true);
				layer.play();
			}

			if(camTransition == sf::Vector2f(0, 0))
				player1.update(tears);

			sf::Transform transform;

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

			for (std::vector<Room>::iterator room = _floor.rooms.begin(); room != _floor.rooms.end(); room++)
			{
				if (room->pos == _floor.currentRoom)
				{
					room->update(player1, tears);
					for (int i = 0; i < room->tiles.size(); i++)
						room->tiles[i]->update(player1, tears);
					for (int i = 0; i < room->doors.size(); i++)
						room->doors[i].update(entities);

					for (std::vector<Room>::iterator i = _floor.rooms.begin(); i != _floor.rooms.end(); i++)
					{
						if (player1.pos.y < _floor.currentRoom.y + 32 && i->pos.y == _floor.currentRoom.y - 310 && i->pos.x == _floor.currentRoom.x)
						{
							roomTransition = _floor.currentRoom;
							_floor.currentRoom.y -= 310;
							player1.pos.y = i->pos.y + 258;
							player1.vel = sf::Vector2f(0, 0);
							camTransition.y -= 310;
						}
						else if (player1.pos.y > _floor.currentRoom.y + 278 && i->pos.y == _floor.currentRoom.y + 310 && i->pos.x == _floor.currentRoom.x)
						{
							roomTransition = _floor.currentRoom;
							_floor.currentRoom.y += 310;
							player1.pos.y = i->pos.y + 52;
							player1.vel = sf::Vector2f(0, 0);
							camTransition.y += 310;
						}
						else if (player1.pos.x < _floor.currentRoom.x + 32 && i->pos.x == _floor.currentRoom.x - 466 && i->pos.y == _floor.currentRoom.y)
						{
							roomTransition = _floor.currentRoom;
							_floor.currentRoom.x -= 466;
							player1.pos.x = i->pos.x + 414;
							player1.vel = sf::Vector2f(0, 0);
							camTransition.x -= 466;
						}
						else if (player1.pos.x > _floor.currentRoom.x + 434 && i->pos.x == _floor.currentRoom.x + 466 && i->pos.y == _floor.currentRoom.y)
						{
							roomTransition = _floor.currentRoom;
							_floor.currentRoom.x += 466;
							player1.pos.x = i->pos.x + 52;
							player1.vel = sf::Vector2f(0, 0);
							camTransition.x += 466;
						}
					}
				}
			}

			if (camTransition != sf::Vector2f(0, 0))
			{
				if (abs(camTransition.x) < 20)
				{
					cam.x -= camTransition.x;
					camTransition.x = 0;
				}
				if (abs(camTransition.y) < 20)
				{
					cam.y -= camTransition.y;
					camTransition.y = 0;
				}

				if (camTransition.x > 0)
				{
					cam.x -= 20;
					camTransition.x -= 20;
				}
				if (camTransition.y > 0)
				{
					cam.y -= 20;
					camTransition.y -= 20;
				}
				if (camTransition.x < 0)
				{
					cam.x += 20;
					camTransition.x += 20;
				}
				if (camTransition.y < 0)
				{
					cam.y += 20;
					camTransition.y += 20;
				}
			}
			transform.translate(cam);

			for (int i = 0; i < _floor.rooms.size(); i++)
			{
				if (_floor.rooms[i].pos == _floor.currentRoom || _floor.rooms[i].pos == roomTransition)
				{
					for (int j = 0; j < _floor.rooms[i].backdrop.size(); j++)
						maint.draw(_floor.rooms[i].backdrop[j].getSprite(), transform);
				}
			}

			for (std::vector<Fly>::iterator flyIter = flies.begin(); flyIter != flies.end(); flyIter++)
			{
				maint.draw(flyIter->getSprite(), transform);
			}

			for (std::vector<Tear>::iterator tearIter = tears.begin(); tearIter != tears.end(); tearIter++)
			{
				maint.draw(tearIter->getSprite(), transform);
			}

			for (std::vector<Room>::iterator roomIter = _floor.rooms.begin(); roomIter != _floor.rooms.end(); roomIter++)
			{
				if (roomIter->pos == _floor.currentRoom || roomIter->pos == roomTransition)
				{
					for (int i = 0; i < roomIter->tiles.size(); i++)
						maint.draw(roomIter->tiles[i]->getSprite(), transform);
					for (int i = 0; i < roomIter->doors.size(); i++)
					{
						maint.draw(roomIter->doors[i].sprite, transform);
					}
				}
			}

			maint.draw(player1, transform);

			//This code bracked handles the GUI
			{
				for (std::vector<Room>::iterator roomIter = _floor.rooms.begin(); roomIter != _floor.rooms.end(); roomIter++)
				{
					sf::RectangleShape rect(sf::Vector2f(4, 4));
					rect.setPosition(((roomIter->pos.x / 466) * 5), 50 - ((roomIter->pos.y / 310) * 5));
					rect.setFillColor(sf::Color::Blue);
					if (roomIter->pos == _floor.currentRoom)
						rect.setFillColor(sf::Color::Cyan);
					maint.draw(rect);
				}

				for (double i = 0.0; i < volume; i += 0.1)
				{
					sf::RectangleShape rect(sf::Vector2f(5, 10));
					rect.setPosition(3 + (i * 26), maint.getSize().y - 13);
					rect.setFillColor(sf::Color::Blue);
					maint.draw(rect);
				}
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