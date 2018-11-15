#include "Room.h"
#include "Tile.h"
#include <string>

using namespace tinyxml2;

Room::Room(int x, int y, FloorID _floor, sf::Sprite& _sprite)
{
	pos = sf::Vector2f(x, y);
	floor = _floor;
	int ran1 = rand() % 2;
	int ran2 = rand() % 2;
	int ran3 = rand() % 2;
	int ran4 = rand() % 2;
	backdrop = {
		Frame(_sprite, 0, (156 * ran1), 233, 155, 1, 1, 0, 0, 0, 0, 1),
		Frame(_sprite, 0, (156 * ran2), 233, 155, -1, 1, 0, 0, 0, 0, 1),
		Frame(_sprite, 0, (156 * ran3), 233, 155, -1, -1, 0, 0, 0, 0, 1),
		Frame(_sprite, 0, (156 * ran4), 233, 155, 1, -1, 0, 0, 0, 0, 1),
	};
	backdrop[0].sprite.setPosition(pos);
	backdrop[1].sprite.setPosition(pos.x + 466, pos.y);
	backdrop[2].sprite.setPosition(pos.x + 466, pos.y + 310);
	backdrop[3].sprite.setPosition(pos.x, pos.y + 310);
}

Room::Room(const Room & room)
{
	pos = room.pos;
	tiles = room.tiles;
	entities = room.entities;
	backdrop = room.backdrop;
	floor = room.floor;
}

Room Room::operator=(const Room& room)
{
	Room r;
	r.pos = room.pos;
	r.tiles = room.tiles;
	r.entities = room.entities;
	r.backdrop = room.backdrop;
	r.floor = room.floor;
	return r;
}

void Room::load(sf::Sprite& _sprite)
{
	frames = {
		Frame(_sprite, 0, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 32, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 64, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 0, 96, 32, 32, 1, 1, 0, 0, -1, -3, 0),
		Frame(_sprite, 32, 96, 32, 32, 1, 1, 0, 0, 4, -3, 0),
		Frame(_sprite, 0, 128, 32, 32, 1, 1, 0, 0, -1, 2, 0),
		Frame(_sprite, 32, 128, 32, 32, 1, 1, 0, 0, 4, 2, 0),
		Frame(_sprite, 0, 224, 32, 32, 1, 1, 0, 0, -3, -3, 0),
		Frame(_sprite, 32, 224, 32, 32, 1, 1, 0, 0, 2, -3, 0),
		Frame(_sprite, 0, 160, 32, 32, 1, 1, 0, 0, -1, -3, 0),
		Frame(_sprite, 0, 192, 32, 32, 1, 1, 0, 0, -1, 2, 0)
	};
	doc.LoadFile("resources/rooms/testmap.xml");
	XMLElement* root = doc.RootElement()->FirstChildElement("room");
	int k = rand() % 4;
	for (int i = 0; i < k; i++)
		root = root->NextSiblingElement("room");
	roomSize = root->Attribute("size");
	XMLElement* i = root->FirstChildElement("wall");
	while(i != NULL)
	{
		tiles.push_back(std::make_unique<Tile>());
		tiles.push_back(std::make_unique<Wall>(pos.x + std::stoi(i->Attribute("x")), pos.y + std::stoi(i->Attribute("y")), test, _sprite));
		i = i->NextSiblingElement("wall");
	}
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors[i].doorWall == left)
			hasLeftDoor = true;
		if (doors[i].doorWall == right)
			hasRightDoor = true;
		if (doors[i].doorWall == up)
			hasUpDoor = true;
		if (doors[i].doorWall == down)
			hasDownDoor = true;
	}

	for (int i = 1; i < tiles.size(); i+=2)
	{
		for (int j = 1; j < tiles.size(); j+=2)
		{
			if (tiles[i]->pos.x == tiles[j]->pos.x - 27 && tiles[i]->pos.y == tiles[j]->pos.y - 27)
			{
				tiles[i]->neighbors[0] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x && tiles[i]->pos.y == tiles[j]->pos.y - 27)
			{
				tiles[i]->neighbors[1] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x + 27 && tiles[i]->pos.y == tiles[j]->pos.y - 27)
			{
				tiles[i]->neighbors[2] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x - 27 && tiles[i]->pos.y == tiles[j]->pos.y)
			{
				tiles[i]->neighbors[3] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x + 27 && tiles[i]->pos.y == tiles[j]->pos.y)
			{
				tiles[i]->neighbors[4] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x - 27 && tiles[i]->pos.y == tiles[j]->pos.y + 27)
			{
				tiles[i]->neighbors[5] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x && tiles[i]->pos.y == tiles[j]->pos.y + 27)
			{
				tiles[i]->neighbors[6] = j;
			}
			else if (tiles[i]->pos.x == tiles[j]->pos.x + 27 && tiles[i]->pos.y == tiles[j]->pos.y + 27)
			{
				tiles[i]->neighbors[7] = j;
			}
		}

		//Big rocks!!!

		// [x][x][ ]
		// [x][o][ ]
		// [ ][ ][ ]
		if (!tiles[i]->hasSprite &&
			tiles[i]->neighbors[0] != NULL &&
			tiles[i]->neighbors[1] != NULL &&
			tiles[i]->neighbors[3] != NULL &&
			rand() % 5 > 2)
		{
			if (!tiles[tiles[i]->neighbors[0]]->hasSprite &&
				!tiles[tiles[i]->neighbors[1]]->hasSprite &&
				!tiles[tiles[i]->neighbors[3]]->hasSprite)
			{
				tiles[tiles[i]->neighbors[0]]->sprite = frames[6].sprite;
				tiles[tiles[i]->neighbors[3]]->sprite = frames[4].sprite;
				tiles[tiles[i]->neighbors[1]]->sprite = frames[5].sprite;
				tiles[i]->sprite = frames[3].sprite;

				tiles[tiles[i]->neighbors[0]]->sprite.setPosition(tiles[tiles[i]->neighbors[0]]->pos + frames[6].offSet);
				tiles[tiles[i]->neighbors[3]]->sprite.setPosition(tiles[tiles[i]->neighbors[3]]->pos + frames[4].offSet);
				tiles[tiles[i]->neighbors[1]]->sprite.setPosition(tiles[tiles[i]->neighbors[1]]->pos + frames[5].offSet);
				tiles[i]->sprite.setPosition(tiles[i]->pos + frames[3].offSet);

				tiles[i]->hasSprite = true;
				tiles[tiles[i]->neighbors[0]]->hasSprite = true;
				tiles[tiles[i]->neighbors[1]]->hasSprite = true;
				tiles[tiles[i]->neighbors[3]]->hasSprite = true;
			}
		}

		// [ ][x][ ]
		// [ ][o][ ]
		// [ ][ ][ ]
		if (!tiles[i]->hasSprite &&
			tiles[i]->neighbors[1] != NULL &&
			rand() % 5 > 2)
		{
			if (!tiles[tiles[i]->neighbors[1]]->hasSprite)
			{
				tiles[i]->sprite = frames[9].getSprite();
				tiles[tiles[i]->neighbors[1]]->sprite = frames[10].getSprite();

				tiles[i]->sprite.setPosition(tiles[i]->pos + frames[9].offSet);
				tiles[tiles[i]->neighbors[1]]->sprite.setPosition(tiles[tiles[i]->neighbors[1]]->pos + frames[10].offSet);

				tiles[i]->hasSprite = true;
				tiles[tiles[i]->neighbors[1]]->hasSprite = true;
			}
		}

		// [x][o][ ]
		// [ ][ ][ ]
		// [ ][ ][ ]
		if (!tiles[i]->hasSprite &&
			tiles[i]->neighbors[3] != NULL &&
			rand() % 5 > 2)
		{
			if (!tiles[tiles[i]->neighbors[3]]->hasSprite)
			{
				tiles[i]->sprite = frames[7].getSprite();
				tiles[tiles[i]->neighbors[3]]->sprite = frames[8].getSprite();

				tiles[i]->sprite.setPosition(tiles[i]->pos + frames[7].offSet);
				tiles[tiles[i]->neighbors[3]]->sprite.setPosition(tiles[tiles[i]->neighbors[3]]->pos + frames[8].offSet);

				tiles[i]->hasSprite = true;
				tiles[tiles[i]->neighbors[3]]->hasSprite = true;
			}
		}
	}

	for (int i = 1; i < tiles.size(); i+=2)
	{
		if (!tiles[i]->hasSprite)
		{
			tiles[i]->sprite = frames[rand() % 3].getSprite();
			tiles[i]->sprite.setPosition(tiles[i]->pos);
		}
	}
}

void Room::update(Player& player, std::vector<Tear>& tears)
{
	if (hasLeftDoor)
	{
		//Top of doorway
		if (player.pos.y < pos.y + 147 &&
			player.pos.y > pos.y + 137 &&
			player.pos.x < pos.x + (58 - (player.maxSpeed - player.vel.x)))
		{
			player.pos.y = pos.y + 147;
			player.vel.y = 0;
		}
		//Bottom of doorway
		else if (player.pos.y > pos.y + 169 &&
			player.pos.y < pos.y + 179 &&
			player.pos.x < pos.x + (58 - (player.maxSpeed - player.vel.x)))
		{
			player.pos.y = pos.y + 169;
			player.vel.y = 0;
		}
		//Wall
		else if (player.pos.x < pos.x + 58 &&
			player.pos.x > pos.x + 48 &&
			(player.pos.y > pos.y + (169 + (player.maxSpeed - player.vel.y)) || player.pos.y < pos.y + (147 - (player.maxSpeed - player.vel.y))))
		{
			player.pos.x = pos.x + 58;
			player.vel.x = 0;
		}
	}
	else
	{
		if (player.pos.x < pos.x + 58)
		{
			player.pos.x = pos.x + 58;
			player.vel.x = 0;
		}
	}

	if (hasRightDoor)
	{
		//Top of doorway
		if (player.pos.y < pos.y + 147 &&
			player.pos.y > pos.y + 137 &&
			player.pos.x > pos.x + (408 + (player.maxSpeed + player.vel.x)))
		{
			player.pos.y = pos.y + 147;
			player.vel.y = 0;
		}
		//Bottom of doorway
		else if (player.pos.y > pos.y + 169 &&
			player.pos.y < pos.y + 179 &&
			player.pos.x > pos.x + (408 + (player.maxSpeed + player.vel.x)))
		{
			player.pos.y = pos.y + 169;
			player.vel.y = 0;
		}
		//Wall
		else if (player.pos.x < pos.x + 418 &&
			player.pos.x > pos.x + 408 &&
			(player.pos.y > pos.y + (169 + (player.maxSpeed - player.vel.y)) || player.pos.y < pos.y + (147 - (player.maxSpeed - player.vel.y))))
		{
			player.pos.x = pos.x + 408;
			player.vel.x = 0;
		}
	}
	else
	{
		if (player.pos.x > pos.x + 408)
		{
			player.pos.x = pos.x + 408;
			player.vel.x = 0;
		}
	}

	if (hasUpDoor)
	{
		if (player.pos.x > pos.x + 215 &&
			player.pos.x < pos.x + 225 &&
			player.pos.y < pos.y + (58 - (player.maxSpeed - player.vel.y)))
		{
			player.pos.x = pos.x + 225;
			player.vel.x = 0;
		}
		else if (player.pos.x > pos.x + 241 &&
			player.pos.x < pos.x + 251 &&
			player.pos.y < pos.y + (58 - (player.maxSpeed - player.vel.y)))
		{
			player.pos.x = pos.x + 241;
			player.vel.x = 0;
		}
		else if (player.pos.y < pos.y + 58 &&
			player.pos.y > pos.y + 48 &&
			(player.pos.x < pos.x + (225 - (player.maxSpeed - player.vel.x)) || player.pos.x > pos.x + (241 + (player.maxSpeed + player.vel.x))))
		{
			player.pos.y = pos.y + 58;
			player.vel.y = 0;
		}
	}
	else
	{
		if (player.pos.y < pos.y + 58)
		{
			player.pos.y = pos.y + 58;
			player.vel.y = 0;
		}
	}

	if (hasDownDoor)
	{
		if (player.pos.x > pos.x + 215 &&
			player.pos.x < pos.x + 225 &&
			player.pos.y > pos.y + (262 + (player.maxSpeed + player.vel.y)))
		{
			player.pos.x = pos.x + 225;
			player.vel.x = 0;
		}
		else if (player.pos.x > pos.x + 241 &&
			player.pos.x < pos.x + 251 &&
			player.pos.y > pos.y + (262 + (player.maxSpeed + player.vel.y)))
		{
			player.pos.x = pos.x + 241;
			player.vel.x = 0;
		}
		else if (player.pos.y > pos.y + 262 &&
			player.pos.y < pos.y + 272 &&
			(player.pos.x < pos.x + (225 - (player.maxSpeed - player.vel.x)) || player.pos.x > pos.x + (241 + (player.maxSpeed + player.vel.x))))
		{
			player.pos.y = pos.y + 262;
			player.vel.y = 0;
		}
	}
	else
	{
		if (player.pos.y > pos.y + 262)
		{
			player.pos.y = pos.y + 262;
			player.vel.y = 0;
		}
	}
}