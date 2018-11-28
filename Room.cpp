#include "Room.h"
#include "Tile.h"
#include "Fly.h"
#include <string>

using namespace tinyxml2;
sf::Texture quee;
std::vector<std::vector<Frame>> temp;

Room::Room(int x, int y, FloorID _floor, sf::Sprite& _sprite)
{
	pos = sf::Vector2f(x, y);
	roomNumber = rand() % 4;
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
	roomNumber = rand() % 4;
	pos = room.pos;
	tiles = room.tiles;
	entities = room.entities;
	backdrop = room.backdrop;
	floor = room.floor;
}

Room Room::operator=(const Room& room)
{
	Room r;
	r.roomNumber = rand() % 4;
	r.pos = room.pos;
	r.tiles = room.tiles;
	r.entities = room.entities;
	r.backdrop = room.backdrop;
	r.floor = room.floor;
	return r;
}

void Room::load(sf::Sprite& _sprite, sf::Sprite& holeSprite)
{
	//Load sprites and animations for use when generating room
	sf::Sprite tsprite;
	Animation flyAnim;
	quee.loadFromFile("resources/gfx/enemies/fly.png");
	tsprite.setTexture(quee);
	frames = {
		Frame(_sprite, 0, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 32, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 64, 0, 32, 32, 1, 1, 0, 0, 0, 0, 0),
		Frame(_sprite, 0, 96, 32, 32, 1, 1, 0, 0, -3, -1, 0),
		Frame(_sprite, 32, 96, 32, 32, 1, 1, 0, 0, 1, -1, 0),
		Frame(_sprite, 0, 128, 32, 32, 1, 1, 0, 0, -3, 1, 0),
		Frame(_sprite, 32, 128, 32, 32, 1, 1, 0, 0, 1, 1, 0),
		Frame(_sprite, 0, 224, 32, 32, 1, 1, 0, 0, 0, -1, 0),
		Frame(_sprite, 32, 224, 32, 32, 1, 1, 0, 0, 4, -2, 0),
		Frame(_sprite, 0, 160, 32, 32, 1, 1, 0, 0, 0, -1, 0),
		Frame(_sprite, 0, 192, 32, 32, 1, 1, 0, 0, 0, 1, 0)
	};
	holeFrames = {
		Frame(holeSprite, 0, 78, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 0, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 0, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 52, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 0, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 26, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 52, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 104, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 0, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 26, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 26, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 52, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 26, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 52, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 78, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 78, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 78, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 104, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 130, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 130, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 130, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 104, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 104, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 130, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 156, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 156, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 156, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 156, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 182, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 26, 182, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 52, 182, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 78, 182, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1),
		Frame(holeSprite, 0, 208, 26, 26, 1.076, 1.115, 0, 0, 0, 0, 1)
	};
	temp = { {
		Frame(tsprite, 0, 0, 32, 32, 0.8, 0.8, 16, 24, 0, -4, 2),
		Frame(tsprite, 32, 0, 32, 32, 0.8, 0.8, 16, 24, 0, -4, 2)
	} };
	flyAnim.load(temp);

	//Choose random room with available doors that match it's neighboring rooms
	doc.LoadFile("resources/rooms/testmap.xml");
	XMLElement* firstRoot = doc.RootElement()->FirstChildElement("room");
	for (int i = 0; i < roomNumber; i++)
		firstRoot = firstRoot->NextSiblingElement("room");
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors[i].doorWall == left && firstRoot->Attribute("leftDoor", "1"))
		{
			if (i == doors.size() - 1)
				loaded = true;
		}
		else if (doors[i].doorWall == up && firstRoot->Attribute("topDoor", "1"))
		{
			if (i == doors.size() - 1)
				loaded = true;
		}
		else if (doors[i].doorWall == down && firstRoot->Attribute("bottomDoor", "1"))
		{
			if (i == doors.size() - 1)
				loaded = true;
		}
		else if (doors[i].doorWall == right && firstRoot->Attribute("rightDoor", "1"))
		{
			if (i == doors.size() - 1)
				loaded = true;
		}
		else
		{
			roomNumber = (roomNumber + 1) % 4;
			break;
		}
	}
	
	//Generate map based on chosen room
	if (loaded)
	{
		XMLElement* root = firstRoot;
		XMLElement* i = root->FirstChildElement("hole");
		while (i != NULL)
		{
			int xx = std::stoi(i->Attribute("x")) - 1;
			int yy = std::stoi(i->Attribute("y")) - 1;
			int x = (pos.x + 52) + (xx * 28);
			int y = (pos.y + 52) + (yy * 29);
			holes.push_back(Hole(x, y, TR, holeFrames[0].sprite));
			i = i->NextSiblingElement("hole");
		}
		for (int i = 0; i < holes.size(); i++)
		{
			for (int j = 0; j < holes.size(); j++)
			{
				if (holes[j].pos.x == holes[i].pos.x - 28 && holes[j].pos.y == holes[i].pos.y - 29)
					holes[i].neighbors[0] = j;
				else if (holes[j].pos.x == holes[i].pos.x && holes[j].pos.y == holes[i].pos.y - 29)
					holes[i].neighbors[1] = j;
				else if (holes[j].pos.x == holes[i].pos.x + 28 && holes[j].pos.y == holes[i].pos.y - 29)
					holes[i].neighbors[2] = j;
				else if (holes[j].pos.x == holes[i].pos.x - 28 && holes[j].pos.y == holes[i].pos.y)
					holes[i].neighbors[3] = j;
				else if (holes[j].pos.x == holes[i].pos.x + 28 && holes[j].pos.y == holes[i].pos.y)
					holes[i].neighbors[4] = j;
				else if (holes[j].pos.x == holes[i].pos.x - 28 && holes[j].pos.y == holes[i].pos.y + 29)
					holes[i].neighbors[5] = j;
				else if (holes[j].pos.x == holes[i].pos.x && holes[j].pos.y == holes[i].pos.y + 29)
					holes[i].neighbors[6] = j;
				else if (holes[j].pos.x == holes[i].pos.x + 28 && holes[j].pos.y == holes[i].pos.y + 29)
					holes[i].neighbors[7] = j;
			}

			{
				// [ ][x][ ]
				// [x][o][ ]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[0] == -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[17].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [x][o][x]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[5].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [ ][o][x]
				// [ ][x][ ]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[5] == -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[20].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [x][o][x]
				// [x][x][ ]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[5] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[30].sprite;
					holes[i].hasSprite = true;
				}

				// [x][x][ ]
				// [x][o][ ]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[0] != -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[3].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [ ][o][x]
				// [ ][x][x]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[7] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[12].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][x]
				// [ ][o][x]
				// [ ][x][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[2] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[7] == -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[14].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][ ]
				// [ ][o][x]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[2] == -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[7] == -858993460 &&
					holes[i].neighbors[5] == -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[18].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][x]
				// [ ][o][x]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[2] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[7] == -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[6].sprite;
					holes[i].hasSprite = true;
				}

				// [x][x][x]
				// [x][o][x]
				// [ ][ ][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[2] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[0] != -858993460 &&
					holes[i].neighbors[6] == -858993460)
				{
					holes[i].sprite = holeFrames[7].sprite;
					holes[i].hasSprite = true;
				}

				// [x][x][ ]
				// [x][o][ ]
				// [x][x][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[0] != -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[11].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [x][o][ ]
				// [x][x][ ]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[5] != -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[9].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][x]
				// [x][o][x]
				// [x][x][x]
				if (holes[i].neighbors[0] == -858993460 &&
					holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[2] != -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[4] != -858993460 &&
					holes[i].neighbors[6] != -858993460 &&
					holes[i].neighbors[7] != -858993460)
				{
					holes[i].sprite = holeFrames[21].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][ ]
				// [ ][o][ ]
				// [ ][x][ ]
				if (holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[10].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [x][o][ ]
				// [ ][ ][ ]
				if (holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[6] == -858993460 &&
					holes[i].neighbors[4] == -858993460)
				{
					holes[i].sprite = holeFrames[1].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][x][ ]
				// [ ][o][ ]
				// [ ][ ][ ]
				if (holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[1] != -858993460 &&
					holes[i].neighbors[6] == -858993460 &&
					holes[i].neighbors[4] == -858993460)
				{
					holes[i].sprite = holeFrames[2].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [ ][o][x]
				// [ ][ ][ ]
				if (holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[6] == -858993460 &&
					holes[i].neighbors[4] != -858993460)
				{
					holes[i].sprite = holeFrames[4].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [x][o][ ]
				// [ ][x][ ]
				if (holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[3] != -858993460 &&
					holes[i].neighbors[2] == -858993460 &&
					holes[i].neighbors[4] == -858993460 &&
					holes[i].neighbors[7] == -858993460 &&
					holes[i].neighbors[5] == -858993460 &&
					holes[i].neighbors[6] != -858993460)
				{
					holes[i].sprite = holeFrames[19].sprite;
					holes[i].hasSprite = true;
				}

				// [ ][ ][ ]
				// [ ][o][ ]
				// [ ][x][ ]
				if (holes[i].neighbors[3] == -858993460 &&
					holes[i].neighbors[1] == -858993460 &&
					holes[i].neighbors[6] != -858993460 &&
					holes[i].neighbors[4] == -858993460)
				{
					holes[i].sprite = holeFrames[8].sprite;
					holes[i].hasSprite = true;
				}
			}
			holes[i].sprite.setPosition(holes[i].pos);
		}

		root = firstRoot;
		roomSize = root->Attribute("size");
		i = root->FirstChildElement("wall");
		while (i != NULL)
		{
			tiles.push_back(std::make_unique<Tile>());
			int xx = std::stoi(i->Attribute("x")) - 1;
			int yy = std::stoi(i->Attribute("y")) - 1;
			int x = (pos.x + 50) + (xx * 28);
			int y = (pos.y + 49) + (yy * 30);
			switch (std::stoi(i->Attribute("id")))
			{
			case 0:
				tiles.push_back(std::make_unique<Wall>(x, y, test, _sprite));
				break;
			case 1:
				tiles.push_back(std::make_unique<Wall>(x, y, black, _sprite));
				break;
			}
			i = i->NextSiblingElement("wall");
		}

		//TODO: Fix entity animations
		/*
		root = firstRoot;
		i = root->FirstChildElement("entity");
		while (i != NULL)
		{
			entities.push_back(std::make_unique<Enemy>());
			int xx = std::stoi(i->Attribute("x")) - 1;
			int yy = std::stoi(i->Attribute("y")) - 1;
			int x = (pos.x + 50) + (xx * 28);
			int y = (pos.y + 49) + (yy * 30);
			if(i->Attribute("id", "0"))
				entities.push_back(std::make_unique<Fly>(x, y, flyAnim));
			i = i->NextSiblingElement("entity");
		}
		*/

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
		for (int i = 1; i < tiles.size(); i += 2)
		{
			for (int j = 1; j < tiles.size(); j += 2)
			{
				if (tiles[i]->pos.x == tiles[j]->pos.x - 28 && tiles[i]->pos.y == tiles[j]->pos.y - 30)
					tiles[i]->neighbors[0] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x && tiles[i]->pos.y == tiles[j]->pos.y - 30)
					tiles[i]->neighbors[1] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x + 28 && tiles[i]->pos.y == tiles[j]->pos.y - 30)
					tiles[i]->neighbors[2] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x - 28 && tiles[i]->pos.y == tiles[j]->pos.y)
					tiles[i]->neighbors[3] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x + 28 && tiles[i]->pos.y == tiles[j]->pos.y)
					tiles[i]->neighbors[4] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x - 28 && tiles[i]->pos.y == tiles[j]->pos.y + 30)
					tiles[i]->neighbors[5] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x && tiles[i]->pos.y == tiles[j]->pos.y + 30)
					tiles[i]->neighbors[6] = j;
				else if (tiles[i]->pos.x == tiles[j]->pos.x + 28 && tiles[i]->pos.y == tiles[j]->pos.y + 30)
					tiles[i]->neighbors[7] = j;
			}

			//Big rocks!!!

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
		}
		for (int i = 1; i < tiles.size(); i += 2)
		{
			if (!tiles[i]->hasSprite)
			{
				tiles[i]->sprite = frames[rand() % 3].getSprite();
				tiles[i]->sprite.setPosition(tiles[i]->pos);
			}
		}
	}
	//If the room didn't fit, try again
	else
	{
		load(_sprite, holeSprite);
	}
}

void Room::update(Player& player, std::vector<Tear>& tears)
{
	//Collision detection for whether room has certain doors or not
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