#pragma once
#include "Globals.h"

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class WorldDungeonFixed
{
public:
	WorldDungeonFixed();
	void LoadMap(std::string xml);
	~WorldDungeonFixed();

	void DrawMap(sf::RenderWindow &window);

	int GetWorldX();
	int GetWorldY();

	std::string GetObstacleType(int obstacleID);
	int GetObstacleX(int obstacleID);
	int GetObstacleY(int obstacleID);

	bool GetTreasurePickedUp(int treasureID);
	int GetTreasureValue(int treasureID);
	int GetTreasureX(int treasureID);
	int GetTreasureY(int treasureID);

	void SetTreasurePickedUp(int treasureID, bool pickedUp);

	int GetEnemyX(int enemyID);
	int GetEnemyY(int enemyID);

	int GetPlayerX();
	int GetPlayerY();

	void SetPlayerX(int new_positionX);
	void SetPlayerY(int new_positionY);

	int PickUpTreasure();

	void saveGame();

private:
	int sizeX;
	int sizeY;

	int numberOfSquares;
	int numberOfObstacles;
	int numberOfTreasures;
	int numberOfEnemies;
	int numberOfPlayers;

	Square *SpawnPosition;
	Player *allPlayers;
	Enemy *allEnemies;
	Obstacle *allObstacles;
	Item *allItems;
	Treasure *allTreasures;

	void playerHasCrashedWithEnemy();
};

