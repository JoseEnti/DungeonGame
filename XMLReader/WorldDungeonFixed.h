#pragma once
#include "Globals.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <vector>

struct Habitacion
{
	int sizeX;
	int sizeY;

	int id;
	int numberOfSquares;
	int numberOfObstacles;
	int numberOfTreasures;
	int numberOfEnemies;
	int numberOfPlayers;
	int numberOfDoors;

	Square *SpawnPosition;
	Player *allPlayers;
	Enemy *allEnemies;
	Obstacle *allObstacles;
	Item *allItems;
	Treasure *allTreasures;
	Door *allDoors;
};

class WorldDungeonFixed
{
public:
	WorldDungeonFixed();
	void LoadMap(std::string xml, int habitacion);
	~WorldDungeonFixed();

	void DrawMap(sf::RenderWindow &window, int habitacion);

	int GetWorldX(int habitacion);
	int GetWorldY(int habitacion);

	std::string GetObstacleType(int obstacleID, int habitacion);
	int GetObstacleX(int obstacleID, int habitacion);
	int GetObstacleY(int obstacleID, int habitacion);

	bool GetTreasurePickedUp(int treasureID, int habitacion);
	int GetTreasureValue(int treasureID, int habitacion);
	int GetTreasureX(int treasureID, int habitacion);
	int GetTreasureY(int treasureID, int habitacion);

	void SetTreasurePickedUp(int treasureID, bool pickedUp, int habitacion);

	int GetEnemyX(int enemyID, int habitacion);
	int GetEnemyY(int enemyID, int habitacion);

	int GetPlayerX(int habitacion);
	int GetPlayerY(int habitacion);

	int GetDoorX(int doorID, int habitacion);
	int GetDoorY(int doorID, int habitacion);


	void SetPlayerX(int new_positionX, int habitacion);
	void SetPlayerY(int new_positionY, int habitacion);

	int PickUpTreasure(int habitacion);

	void saveGame(int habitacion);

private:

	std::map<int, std::vector <Habitacion>> mapa;
	int maxHabitaciones;
	void playerHasCrashedWithEnemy(int habitacion);
	void playerInDoor(int habitacion);
};

