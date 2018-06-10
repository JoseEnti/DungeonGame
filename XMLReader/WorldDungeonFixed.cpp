#include "WorldDungeonFixed.h"
#include "pugixml.hpp"
#include "DBmanager.h"
#include <time.h>
#include <iostream>
#include <map>
#include <vector>

WorldDungeonFixed::WorldDungeonFixed()
{
}

void WorldDungeonFixed::LoadMap(std::string xml, int habitacion) 
{
	typedef const pugi::char_t* pugiCharArray;

	srand((unsigned)time(NULL));

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(xml.c_str());
	pugi::xml_node nodeMap = doc.child("map");
	
	int players = 0;
	int obstacles = 0;
	int enemies = 0;
	int treasures = 0;
	int doors = 0;
	int vectorIndex = 0;
	int square = 0;
	bool dinamicLoad = false;

	Habitacion h;
	std::vector <Habitacion> temporalVector;

	for (pugi::xml_node nodeRoom = nodeMap.child("room"); nodeRoom; nodeRoom = nodeRoom.next_sibling("room"))
	{
		for (pugi::xml_node nodeSquareMemory = nodeRoom.child("square"); nodeSquareMemory; nodeSquareMemory = nodeSquareMemory.next_sibling("square"))
		{
			pugiCharArray type = nodeSquareMemory.attribute("type").value();
			pugiCharArray positionX = nodeSquareMemory.attribute("x").value();
			pugiCharArray positionY = nodeSquareMemory.attribute("y").value();

			std::string stringType = type;
			std::string stringPositionX = positionX;
			std::string stringPositionY = positionY;

			if (stringType == "player")
			{
				players++;
			}
			else if (stringType == "wall")
			{
				obstacles++;
			}
			else if (stringType == "enemy")
			{
				enemies++;
			}
			else if (stringType == "gold")
			{
				treasures++;
			}
			else if (stringType == "door")
			{
				doors++;
			}
			square++;
		}
		if (!dinamicLoad)
		{
			mapa[habitacion].reserve(players);
			for (int i = 0; i <= players; i++)
			{
				mapa[habitacion][i].allPlayers = new Player;
			}
			for (int i = 0; i <= square; i++)
			{
				mapa[habitacion][i].SpawnPosition = new Square;
			}
			for (int i = 0; i <= enemies; i++)
			{
				mapa[habitacion][i].allEnemies = new Enemy;
			}
			for (int i = 0; i <= doors; i++)
			{
				mapa[habitacion][i].allDoors = new Door;
			}
			for (int i = 0; i <= treasures; i++)
			{
				mapa[habitacion][i].allItems = new Item;
			}
			for (int i = 0; i <= obstacles; i++)
			{
				mapa[habitacion][i].allObstacles = new Obstacle;
			}			
			dinamicLoad = true;
		}
		pugiCharArray sizeX = nodeRoom.attribute("squareAmountX").value();
		pugiCharArray sizeY = nodeRoom.attribute("squareAmountY").value();
		pugiCharArray id = nodeRoom.attribute("id").value();

		std::string stringSizeX = sizeX;
		std::string stringSizeY = sizeY;
		std::string stringId = id;

		h.sizeX = stoi(stringSizeX);
		h.sizeY = stoi(stringSizeX);
		h.id = stoi(stringSizeX);

		for (pugi::xml_node nodeSquare = nodeRoom.child("square"); nodeSquare; nodeSquare = nodeSquare.next_sibling("square"))
		{
			pugiCharArray type = nodeSquare.attribute("type").value();
			pugiCharArray positionX = nodeSquare.attribute("x").value();
			pugiCharArray positionY = nodeSquare.attribute("y").value();

			std::string stringType = type;
			std::string stringPositionX = positionX;
			std::string stringPositionY = positionY;

			if (stringType == "player")
			{
				h.SpawnPosition->X = stoi(stringPositionX);
				h.SpawnPosition->Y = stoi(stringPositionY);
			}
			else if (stringType == "wall")
			{
				h.allObstacles->position.X = stoi(stringPositionX);
				h.allObstacles->position.Y = stoi(stringPositionY);
			}
			else if (stringType == "enemy")
			{
				h.allEnemies->position.X = stoi(stringPositionX);
				h.allEnemies->position.Y = stoi(stringPositionY);
			}
			else if (stringType == "gold")
			{
				h.allTreasures->position.X = stoi(stringPositionX);
				h.allTreasures->position.Y = stoi(stringPositionY);
				h.allTreasures->value = rand() % 100 - 1;
			}
			else if (stringType == "door")
			{
				pugiCharArray teleportTo = nodeSquare.attribute("teleportTo").value();
				std::string tp = teleportTo;

				h.allDoors->position.X = stoi(stringPositionX);
				h.allDoors->position.Y = stoi(stringPositionY);
				h.allDoors->teleportTo = stoi(tp);
			}
			temporalVector.push_back(h);
		}
		mapa[habitacion] = temporalVector;
	}
}

int WorldDungeonFixed::GetWorldX(int habitacion) {
	return mapa[habitacion][habitacion].sizeX;
}

int WorldDungeonFixed::GetWorldY(int habitacion) {
	return mapa[habitacion][habitacion].sizeY;
}

std::string WorldDungeonFixed::GetObstacleType(int obstacleID, int habitacion) {
	return mapa[habitacion][habitacion].allObstacles[obstacleID].type;
}

int WorldDungeonFixed::GetObstacleX(int obstacleID, int habitacion) {
	return mapa[habitacion][habitacion].allObstacles[obstacleID].position.X;
}

int WorldDungeonFixed::GetObstacleY(int obstacleID, int habitacion) {
	return mapa[habitacion][habitacion].allObstacles[obstacleID].position.Y;
}

bool WorldDungeonFixed::GetTreasurePickedUp(int treasureID, int habitacion) {
	return mapa[habitacion][habitacion].allTreasures[treasureID].pickedUp;
}

void WorldDungeonFixed::SetTreasurePickedUp(int treasureID, bool pickedUp, int habitacion) {
	mapa[habitacion][habitacion].allTreasures[treasureID].pickedUp = pickedUp;
}

int WorldDungeonFixed::GetTreasureValue(int treasureID, int habitacion) {
	return mapa[habitacion][habitacion].allTreasures[treasureID].value;
}

int WorldDungeonFixed::GetTreasureX(int treasureID, int habitacion) {
	return mapa[habitacion][habitacion].allTreasures[treasureID].position.X;
}

int WorldDungeonFixed::GetTreasureY(int treasureID, int habitacion) {
	return mapa[habitacion][habitacion].allTreasures[treasureID].position.Y;
}

int WorldDungeonFixed::GetEnemyX(int enemyID, int habitacion) {
	return mapa[habitacion][habitacion].allEnemies[enemyID].position.X;
}

int WorldDungeonFixed::GetEnemyY(int enemyID, int habitacion) {
	return mapa[habitacion][habitacion].allEnemies[enemyID].position.Y;
}

int WorldDungeonFixed::GetDoorX(int doorID, int habitacion) {
	return mapa[habitacion][habitacion].allDoors[doorID].position.X;
}

int WorldDungeonFixed::GetDoorY(int doorID, int habitacion) {
	return mapa[habitacion][habitacion].allDoors[doorID].position.Y;
}

int WorldDungeonFixed::GetPlayerX(int habitacion) {
	return mapa[habitacion][habitacion].allPlayers[0].position.X;
}

int WorldDungeonFixed::GetPlayerY(int habitacion) {
	return mapa[habitacion][habitacion].allPlayers[0].position.Y;
}

void WorldDungeonFixed::SetPlayerX(int new_positionX, int habitacion) {
	if (new_positionX < GetWorldX(habitacion) && new_positionX >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < mapa[habitacion][i].numberOfObstacles; i++) {
			if (GetObstacleX(i, habitacion) == new_positionX && GetObstacleY(i, habitacion) == GetPlayerY(habitacion)) {
				if (GetObstacleType(i, habitacion) == "wall") {
					wallCrash = true;
					i = mapa[habitacion][i].numberOfObstacles;
				}
				else if (GetObstacleType(i, habitacion) == "door") {
					wallCrash = false;
					if (new_positionX > GetPlayerX(habitacion)) {
						new_positionX += 1;
					}
					else if (new_positionX < GetPlayerX(habitacion)) {
						new_positionX -= 1;
					}
					i = mapa[habitacion][i].numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			mapa[habitacion][habitacion].allPlayers[0].position.X = new_positionX;
		}
		playerHasCrashedWithEnemy(habitacion);
	}
}

void WorldDungeonFixed::SetPlayerY(int new_positionY, int habitacion) {
	if (new_positionY < GetWorldY(habitacion) && new_positionY >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < mapa[habitacion][habitacion].numberOfObstacles; i++) {
			if (GetObstacleX(i, habitacion) == GetPlayerX(habitacion) && GetObstacleY(i, habitacion) == new_positionY) {
				if (GetObstacleType(i, habitacion) == "wall") {
					wallCrash = true;
					i = mapa[habitacion][i].numberOfObstacles;
				}
				else if (GetObstacleType(i, habitacion) == "door") {
					wallCrash = false;
					if (new_positionY > GetPlayerY(habitacion)) {
						new_positionY += 1;
					}
					else if (new_positionY < GetPlayerY(habitacion)) {
						new_positionY -= 1;
					}
					i = mapa[habitacion][habitacion].numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			mapa[habitacion][habitacion].allPlayers[0].position.Y = new_positionY;
		}
		playerHasCrashedWithEnemy(habitacion);
	}
}

void WorldDungeonFixed::playerHasCrashedWithEnemy(int habitacion) {
	for (int i = 0; i < mapa[habitacion][habitacion].numberOfEnemies; i++) {
		if (GetEnemyX(i, habitacion) == GetPlayerX(habitacion) && GetEnemyY(i, habitacion) == GetPlayerY(habitacion)) {
			mapa[habitacion][i].allPlayers[0].position.X = mapa[habitacion][habitacion].SpawnPosition[0].X;
			mapa[habitacion][i].allPlayers[0].position.Y = mapa[habitacion][habitacion].SpawnPosition[0].Y;
			i = mapa[habitacion][habitacion].numberOfEnemies;
		}
	}
}

void WorldDungeonFixed::playerInDoor(int habitacion) {
	for (int i = 0; i < mapa[habitacion][habitacion].numberOfDoors; i++) {
		if (GetDoorX(i, habitacion) == GetPlayerX(habitacion) && GetDoorY(i, habitacion) == GetPlayerY(habitacion)) {
			mapa[habitacion][habitacion].allPlayers[0].position.X = mapa[habitacion][habitacion].SpawnPosition[0].X;
			mapa[habitacion][habitacion].allPlayers[0].position.Y = mapa[habitacion][habitacion].SpawnPosition[0].Y;
			i = mapa[habitacion][habitacion].numberOfEnemies;
		}
	}
}

int WorldDungeonFixed::PickUpTreasure(int habitacion) {
	int treasureValue = 0;
	for (int i = 0; i < mapa[habitacion][habitacion].numberOfTreasures; i++) {
		if (GetTreasureX(i, habitacion) == GetPlayerX(habitacion) && GetTreasureY(i, habitacion) == GetPlayerY(habitacion)) {
			if (!GetTreasurePickedUp(i, habitacion)) {
				SetTreasurePickedUp(i, true, habitacion);
				treasureValue = GetTreasureValue(i, habitacion);
				mapa[habitacion][habitacion].allPlayers[0].gold += treasureValue;
				std::cout << "Gold picked == " << treasureValue << "\n";
				i = mapa[habitacion][habitacion].numberOfTreasures;
			}
		}
	}
	return treasureValue;
}

void WorldDungeonFixed::DrawMap(sf::RenderWindow &window, int habitacion) {
	window.clear(sf::Color::Black);

	int chestPlaced = 0;
	int enemyPlaced = 0;
	int obstaclePlaced = 0;
	int playerPlaced = 0;
	int doorPlaced = 0;
	//Draw something here
	sf::Texture textureTerrain;
	if (!textureTerrain.loadFromFile("Suelo.png"))
	{
		std::cout << "Error loading suelo.png" << std::exit;
	}

	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("Enemigo.png"))
	{
		std::cout << "Error loading Enemigo.png" << std::exit;
	}

	sf::Texture textureWall;
	if (!textureWall.loadFromFile("Wall.png"))
	{
		std::cout << "Error loading Wall.png" << std::exit;
	}

	sf::Texture textureDoor;
	if (!textureDoor.loadFromFile("Door.png"))
	{
		std::cout << "Error loading Door.png" << std::exit;
	}

	sf::Texture texturePlayer;
	if (!texturePlayer.loadFromFile("Heroe.png"))
	{
		std::cout << "Error loading Heroe.png" << std::exit;
	}

	sf::Texture textureChest;
	if (!textureChest.loadFromFile("chest_2_closed.png"))
	{
		std::cout << "Error loading chest_2_closed.png" << std::exit;
	}

	sf::RectangleShape groundField;

	groundField.setSize(sf::Vector2f(32.f, 32.f));
	groundField.setTexture(&textureTerrain);
	groundField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::RectangleShape enemyField;

	enemyField.setSize(sf::Vector2f(32.f, 32.f));
	enemyField.setTexture(&textureEnemy);
	enemyField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::RectangleShape wallField;

	wallField.setSize(sf::Vector2f(32.f, 32.f));
	wallField.setTexture(&textureWall);
	wallField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::RectangleShape doorField;

	doorField.setSize(sf::Vector2f(32.f, 32.f));
	doorField.setTexture(&textureDoor);
	doorField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::RectangleShape playerField;

	playerField.setSize(sf::Vector2f(32.f, 32.f));
	playerField.setTexture(&texturePlayer);
	playerField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::RectangleShape chestField;

	chestField.setSize(sf::Vector2f(32.f, 32.f));
	chestField.setTexture(&textureChest);
	chestField.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Draw the dungeon
	for (int i = 0; i <= 5; i++) {
		for (int y = 0; y < GetWorldY(habitacion); y++) {
			for (int x = 0; x < GetWorldX(habitacion); x++) {
				if (i == 0) {
					{
						groundField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(groundField);
					}
				}
				else if (i == 1) {
					if ((mapa[habitacion][x].allTreasures[chestPlaced].position.X) == x && (mapa[habitacion][habitacion].allTreasures[chestPlaced].position.Y) == y) {
						if (mapa[habitacion][habitacion].allTreasures[chestPlaced].pickedUp == false) {
							chestField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(chestField);
						}
						else {
							if ((mapa[habitacion][habitacion].allTreasures[chestPlaced].position.X) == GetPlayerX(habitacion) && (mapa[habitacion][habitacion].allTreasures[chestPlaced].position.Y) == GetPlayerY(habitacion)) {
								playerField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(playerField);
							}
							else if (mapa[habitacion][habitacion].allTreasures[chestPlaced].pickedUp == true) {
								groundField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(groundField);
							}
						}
						chestPlaced++;
					}
				}
				else if (i == 2) {
					if ((mapa[habitacion][habitacion].allEnemies[enemyPlaced].position.X) == x && (mapa[habitacion][habitacion].allEnemies[enemyPlaced].position.Y) == y) {
						enemyField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(enemyField);
						enemyPlaced++;
					}
				}
				else if (i == 3) {
					if ((mapa[habitacion][habitacion].allObstacles[obstaclePlaced].position.X) == x && (mapa[habitacion][habitacion].allObstacles[obstaclePlaced].position.Y) == y) {
						if (mapa[habitacion][habitacion].allObstacles[obstaclePlaced].type == "wall") {
							wallField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(wallField);
							obstaclePlaced++;
						}
					}
				}
				else if (i == 4) {
					if ((mapa[habitacion][habitacion].allDoors[doorPlaced].position.X) == x && (mapa[habitacion][habitacion].allDoors[doorPlaced].position.Y) == y) {
								doorField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(doorField);
								doorPlaced++;
						}
					}
				else if (i == 5) {
					if ((mapa[habitacion][habitacion].allPlayers[playerPlaced].position.X) == x && (mapa[habitacion][habitacion].allPlayers[playerPlaced].position.Y) == y) {
						playerField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(playerField);
						playerPlaced++;
					}
				}
			}
		}
	}
}

void WorldDungeonFixed::saveGame(int habitacion) {
	typedef const pugi::char_t* pugiCharArray;

	int playersCount = 0;
	int enemiesCount = 0;
	int obstaclesCount = 0;
	int itemsCount = 0;
	int treasuresCount = 0;
	int doorCount = 0;

	
	DBmanager db;
	std::string query;
	for (int j = 1; j <= 3; j++)
	{
		query += "<map><room squareAmountX=\"";

		query += std::to_string(GetWorldX(habitacion));

		query += "\" squareAmountY=\"";
		query += std::to_string(GetWorldY(habitacion));
		query += "\">";

		for (int i = 0; i < mapa[habitacion][habitacion].numberOfSquares; i++)
		{

			if (playersCount < mapa[habitacion][habitacion].numberOfPlayers)
			{
				query += "<square type=\"";
				query += mapa[habitacion][habitacion].allPlayers[playersCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion][habitacion].allPlayers[playersCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion][habitacion].allPlayers[playersCount].position.Y);

				query += "\" />";
				playersCount++;
			}
			if (obstaclesCount < mapa[habitacion][habitacion].numberOfObstacles)
			{
				query += "<square type=\"";
				query += mapa[habitacion][habitacion].allObstacles[obstaclesCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion][habitacion].allObstacles[obstaclesCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion][habitacion].allObstacles[obstaclesCount].position.Y);

				query += "\" />";
				obstaclesCount++;
			}
			if (doorCount < mapa[habitacion][habitacion].numberOfDoors)
			{
				query += "<square type=\"";
				query += mapa[habitacion][habitacion].allDoors[doorCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion][habitacion].allDoors[doorCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion][habitacion].allDoors[doorCount].position.Y);

				query += "\" />";
				doorCount++;
			}
			if (enemiesCount < mapa[habitacion][habitacion].numberOfEnemies)
			{
				query += "<square type=\"";
				query += mapa[habitacion][habitacion].allEnemies[enemiesCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion][habitacion].allEnemies[enemiesCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion][habitacion].allEnemies[enemiesCount].position.Y);

				query += "\" />";
				enemiesCount++;
			}
			if (treasuresCount < mapa[habitacion][habitacion].numberOfTreasures)
			{
				query += "<square type=\"";
				query += mapa[habitacion][habitacion].allTreasures[treasuresCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion][habitacion].allTreasures[treasuresCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion][habitacion].allTreasures[treasuresCount].position.Y);

				query += "\" />";
				treasuresCount++;
			}
		}
	}
	query += "</room></map>";
	db.SaveMapDb(query, std::to_string(1));
}

WorldDungeonFixed::~WorldDungeonFixed()
{
}
