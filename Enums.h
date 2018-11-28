#pragma once

enum TileID {wall, hole, entity};
enum TearFlag {normal, bloody, scythe};
enum WallID {test, black};
enum EntityID {
	player, 
	enemy, 
	itemPedestal, 
	tear
};
enum PlayerID {first};
enum ItemID {
	cryingOnion, 
	cricketsHead,
	bookOfBelial,
	necronomicon
};
enum EnemyID {
	fly
};
enum FloorID {basement};
enum DoorID {_normal, boss, secret, locked, chained, barred};
enum DoorWall {up, down, left, right};
enum HoleID {TL, T, TR, L, M, R, BL, B, BR};