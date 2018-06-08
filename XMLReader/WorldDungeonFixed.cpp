#include "WorldDungeonFixed.h"
#include "pugixml.hpp"
#include <iostream>
#include "DBmanager.h"

WorldDungeonFixed::WorldDungeonFixed()
{
}

void WorldDungeonFixed::LoadMap(std::string xml, int habitacion) {
	
	int squares = 0;
	int players = 0;
	int enemies = 0;
	int obstacles = 0;
	int items = 0;
	int treasures = 0;
	int doors = 0;

	bool dynamicMemoryLoaded = false;

	int playersCount = 0;
	int enemiesCount = 0;
	int obstaclesCount = 0;
	int itemsCount = 0;
	int treasuresCount = 0;
	int doorsCount = 0;
	int mapCount = 0;
	int loadNumber = 0;

	typedef const pugi::char_t* pugiCharArray;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(xml.c_str());

	std::cout << "Resultado carga --> " << result.description() << "\n" << std::endl;
	pugi::xml_node nodeMap = doc.child("map");

	pugi::xml_node nodeRoom = nodeMap.child("room");
	
	pugiCharArray attrRoomSizeX = nodeRoom.attribute("squareAmountX").value();
	pugiCharArray attrRoomSizeY = nodeRoom.attribute("squareAmountY").value();

	std::string roomSizeX(attrRoomSizeX);
	std::string roomSizeY(attrRoomSizeY);

	mapa[habitacion].sizeX = stoi(roomSizeX);
	mapa[habitacion].sizeY = stoi(roomSizeY);

	for (pugi::xml_node nodeSquare = nodeRoom.child("square"); nodeSquare; nodeSquare = nodeSquare.next_sibling("square")) 
	{
		pugiCharArray arrayType = nodeSquare.attribute("type").value();
		pugiCharArray arrayPosX = nodeSquare.attribute("x").value();
		pugiCharArray arrayPosY = nodeSquare.attribute("y").value();
		pugiCharArray arrayId = nodeSquare.attribute("id").value();

				std::string type(arrayType);
				std::string posX(arrayPosX);
				std::string posY(arrayPosY);
				std::string id(arrayId);

				if (loadNumber == 0) 
				{
					if (type == "player") {
						players++;
					}
					else if (type == "enemy") {
						enemies++;
					}
					else if (type == "gold") {
						treasures++;
					}
					else if (type == "door") {
						doors++;
					}
					else if (type == "wall") {
						obstacles++;
					}
				}
				else 
				{
					if (!dynamicMemoryLoaded) {
						mapa[mapCount].SpawnPosition = new Square[players];
						mapa[mapCount].allPlayers = new Player[players];
						mapa[mapCount].allEnemies = new Enemy[enemies];
						mapa[mapCount].allTreasures = new Treasure[treasures];
						mapa[mapCount].allObstacles = new Obstacle[obstacles];
						mapa[mapCount].allDoors = new Door[doors];
						dynamicMemoryLoaded = true;
					}

					if (type == "player") {
						mapa[mapCount].SpawnPosition[playersCount].X = stoi(posX);
						mapa[mapCount].SpawnPosition[playersCount].Y = stoi(posY);
						mapa[mapCount].allPlayers[playersCount].position.X = stoi(posX);
						mapa[mapCount].allPlayers[playersCount].position.Y = stoi(posY);
						mapa[mapCount].allPlayers[playersCount].gold = 0;
						mapa[mapCount].allPlayers[playersCount].type = type;
						playersCount++;
					}
					else if (type == "enemy") {
						mapa[mapCount].allEnemies[enemiesCount].position.X = stoi(posX);
						mapa[mapCount].allEnemies[enemiesCount].position.Y = stoi(posY);
						mapa[mapCount].allEnemies[enemiesCount].type = type; //TEMPORAL
						enemiesCount++;
					}
					else if (type == "gold") {
						mapa[mapCount].allTreasures[treasuresCount].position.X = stoi(posX);
						mapa[mapCount].allTreasures[treasuresCount].position.Y = stoi(posY);
						mapa[mapCount].allTreasures[treasuresCount].value = rand() % (50 + 1 - 10) + 10; // TEMPORAL
						mapa[mapCount].allTreasures[treasuresCount].pickedUp = false;
						mapa[mapCount].allTreasures[treasuresCount].type = type;
						treasuresCount++;
					}
					else if (type == "door") {
						mapa[mapCount].allDoors[doorsCount].position.X = stoi(posX);
						mapa[mapCount].allDoors[doorsCount].position.Y = stoi(posY);
						mapa[mapCount].allDoors[doorsCount].type = type; // TEMPORAL
						doorsCount++;
					}
					else if (type == "wall") {
						mapa[mapCount].allObstacles[obstaclesCount].position.X = stoi(posX);
						mapa[mapCount].allObstacles[obstaclesCount].position.Y = stoi(posY);
						mapa[mapCount].allObstacles[obstaclesCount].type = type; // TEMPORAL
						obstaclesCount++;
					}
					squares++;
				}
			}
		}
		mapa[mapCount].numberOfSquares = squares;
		mapa[mapCount].numberOfObstacles = obstacles;
		mapa[mapCount].numberOfTreasures = treasures;
		mapa[mapCount].numberOfEnemies = enemies;
		mapa[mapCount].numberOfPlayers = players;
		mapa[mapCount].numberOfDoors = doors;
		mapCount++;
		loadNumber++;
	}

int WorldDungeonFixed::GetWorldX(int habitacion) {
	return mapa[habitacion].sizeX;
}

int WorldDungeonFixed::GetWorldY(int habitacion) {
	return mapa[habitacion].sizeY;
}

std::string WorldDungeonFixed::GetObstacleType(int obstacleID, int habitacion) {
	return mapa[habitacion].allObstacles[obstacleID].type;
}

int WorldDungeonFixed::GetObstacleX(int obstacleID, int habitacion) {
	return mapa[habitacion].allObstacles[obstacleID].position.X;
}

int WorldDungeonFixed::GetObstacleY(int obstacleID, int habitacion) {
	return mapa[habitacion].allObstacles[obstacleID].position.Y;
}

bool WorldDungeonFixed::GetTreasurePickedUp(int treasureID, int habitacion) {
	return mapa[habitacion].allTreasures[treasureID].pickedUp;
}

void WorldDungeonFixed::SetTreasurePickedUp(int treasureID, bool pickedUp, int habitacion) {
	mapa[habitacion].allTreasures[treasureID].pickedUp = pickedUp;
}

int WorldDungeonFixed::GetTreasureValue(int treasureID, int habitacion) {
	return mapa[habitacion].allTreasures[treasureID].value;
}

int WorldDungeonFixed::GetTreasureX(int treasureID, int habitacion) {
	return mapa[habitacion].allTreasures[treasureID].position.X;
}

int WorldDungeonFixed::GetTreasureY(int treasureID, int habitacion) {
	return mapa[habitacion].allTreasures[treasureID].position.Y;
}

int WorldDungeonFixed::GetEnemyX(int enemyID, int habitacion) {
	return mapa[habitacion].allEnemies[enemyID].position.X;
}

int WorldDungeonFixed::GetEnemyY(int enemyID, int habitacion) {
	return mapa[habitacion].allEnemies[enemyID].position.Y;
}

int WorldDungeonFixed::GetDoorX(int doorID, int habitacion) {
	return mapa[habitacion].allDoors[doorID].position.X;
}

int WorldDungeonFixed::GetDoorY(int doorID, int habitacion) {
	return mapa[habitacion].allDoors[doorID].position.Y;
}

int WorldDungeonFixed::GetPlayerX(int habitacion) {
	return mapa[habitacion].allPlayers[0].position.X;
}

int WorldDungeonFixed::GetPlayerY(int habitacion) {
	return mapa[habitacion].allPlayers[0].position.Y;
}

void WorldDungeonFixed::SetPlayerX(int new_positionX, int habitacion) {
	if (new_positionX < GetWorldX(habitacion) && new_positionX >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < mapa[habitacion].numberOfObstacles; i++) {
			if (GetObstacleX(i, habitacion) == new_positionX && GetObstacleY(i, habitacion) == GetPlayerY(habitacion)) {
				if (GetObstacleType(i, habitacion) == "wall") {
					wallCrash = true;
					i = mapa[habitacion].numberOfObstacles;
				}
				else if (GetObstacleType(i, habitacion) == "door") {
					wallCrash = false;
					if (new_positionX > GetPlayerX(habitacion)) {
						new_positionX += 1;
					}
					else if (new_positionX < GetPlayerX(habitacion)) {
						new_positionX -= 1;
					}
					i = mapa[habitacion].numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			mapa[habitacion].allPlayers[0].position.X = new_positionX;
		}
		playerHasCrashedWithEnemy(habitacion);
	}
}

void WorldDungeonFixed::SetPlayerY(int new_positionY, int habitacion) {
	if (new_positionY < GetWorldY(habitacion) && new_positionY >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < mapa[habitacion].numberOfObstacles; i++) {
			if (GetObstacleX(i, habitacion) == GetPlayerX(habitacion) && GetObstacleY(i, habitacion) == new_positionY) {
				if (GetObstacleType(i, habitacion) == "wall") {
					wallCrash = true;
					i = mapa[habitacion].numberOfObstacles;
				}
				else if (GetObstacleType(i, habitacion) == "door") {
					wallCrash = false;
					if (new_positionY > GetPlayerY(habitacion)) {
						new_positionY += 1;
					}
					else if (new_positionY < GetPlayerY(habitacion)) {
						new_positionY -= 1;
					}
					i = mapa[habitacion].numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			mapa[habitacion].allPlayers[0].position.Y = new_positionY;
		}
		playerHasCrashedWithEnemy(habitacion);
	}
}

void WorldDungeonFixed::playerHasCrashedWithEnemy(int habitacion) {
	for (int i = 0; i < mapa[habitacion].numberOfEnemies; i++) {
		if (GetEnemyX(i, habitacion) == GetPlayerX(habitacion) && GetEnemyY(i, habitacion) == GetPlayerY(habitacion)) {
			mapa[habitacion].allPlayers[0].position.X = mapa[habitacion].SpawnPosition[0].X;
			mapa[habitacion].allPlayers[0].position.Y = mapa[habitacion].SpawnPosition[0].Y;
			i = mapa[habitacion].numberOfEnemies;
		}
	}
}

void WorldDungeonFixed::playerInDoor(int habitacion) {
	for (int i = 0; i < mapa[habitacion].numberOfDoors; i++) {
		if (GetDoorX(i, habitacion) == GetPlayerX(habitacion) && GetDoorY(i, habitacion) == GetPlayerY(habitacion)) {
			mapa[habitacion].allPlayers[0].position.X = mapa[habitacion].SpawnPosition[0].X;
			mapa[habitacion].allPlayers[0].position.Y = mapa[habitacion].SpawnPosition[0].Y;
			i = mapa[habitacion].numberOfEnemies;
		}
	}
}

int WorldDungeonFixed::PickUpTreasure(int habitacion) {
	int treasureValue = 0;
	for (int i = 0; i < mapa[habitacion].numberOfTreasures; i++) {
		if (GetTreasureX(i, habitacion) == GetPlayerX(habitacion) && GetTreasureY(i, habitacion) == GetPlayerY(habitacion)) {
			if (!GetTreasurePickedUp(i, habitacion)) {
				SetTreasurePickedUp(i, true, habitacion);
				treasureValue = GetTreasureValue(i, habitacion);
				mapa[habitacion].allPlayers[0].gold += treasureValue;
				std::cout << "Gold picked == " << treasureValue << "\n";
				i = mapa[habitacion].numberOfTreasures;
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
					if ((mapa[habitacion].allTreasures[chestPlaced].position.X) == x && (mapa[habitacion].allTreasures[chestPlaced].position.Y) == y) {
						if (mapa[habitacion].allTreasures[chestPlaced].pickedUp == false) {
							chestField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(chestField);
						}
						else {
							if ((mapa[habitacion].allTreasures[chestPlaced].position.X) == GetPlayerX(habitacion) && (mapa[habitacion].allTreasures[chestPlaced].position.Y) == GetPlayerY(habitacion)) {
								playerField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(playerField);
							}
							else if (mapa[habitacion].allTreasures[chestPlaced].pickedUp == true) {
								groundField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(groundField);
							}
						}
						chestPlaced++;
					}
				}
				else if (i == 2) {
					if ((mapa[habitacion].allEnemies[enemyPlaced].position.X) == x && (mapa[habitacion].allEnemies[enemyPlaced].position.Y) == y) {
						enemyField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(enemyField);
						enemyPlaced++;
					}
				}
				else if (i == 3) {
					if ((mapa[habitacion].allObstacles[obstaclePlaced].position.X) == x && (mapa[habitacion].allObstacles[obstaclePlaced].position.Y) == y) {
						if (mapa[habitacion].allObstacles[obstaclePlaced].type == "wall") {
							wallField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(wallField);
							obstaclePlaced++;
						}
					}
				}
				else if (i == 4) {
					if ((mapa[habitacion].allDoors[doorPlaced].position.X) == x && (mapa[habitacion].allDoors[doorPlaced].position.Y) == y) {
								doorField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(doorField);
								doorPlaced++;
						}
					}
				else if (i == 5) {
					if ((mapa[habitacion].allPlayers[playerPlaced].position.X) == x && (mapa[habitacion].allPlayers[playerPlaced].position.Y) == y) {
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

		for (int i = 0; i < mapa[habitacion].numberOfSquares; i++)
		{

			if (playersCount < mapa[habitacion].numberOfPlayers)
			{
				query += "<square type=\"";
				query += mapa[habitacion].allPlayers[playersCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion].allPlayers[playersCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion].allPlayers[playersCount].position.Y);

				query += "\" />";
				playersCount++;
			}
			if (obstaclesCount < mapa[habitacion].numberOfObstacles)
			{
				query += "<square type=\"";
				query += mapa[habitacion].allObstacles[obstaclesCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion].allObstacles[obstaclesCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion].allObstacles[obstaclesCount].position.Y);

				query += "\" />";
				obstaclesCount++;
			}
			if (doorCount < mapa[habitacion].numberOfDoors)
			{
				query += "<square type=\"";
				query += mapa[habitacion].allDoors[doorCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion].allDoors[doorCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion].allDoors[doorCount].position.Y);

				query += "\" />";
				doorCount++;
			}
			if (enemiesCount < mapa[habitacion].numberOfEnemies)
			{
				query += "<square type=\"";
				query += mapa[habitacion].allEnemies[enemiesCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion].allEnemies[enemiesCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion].allEnemies[enemiesCount].position.Y);

				query += "\" />";
				enemiesCount++;
			}
			if (treasuresCount < mapa[habitacion].numberOfTreasures)
			{
				query += "<square type=\"";
				query += mapa[habitacion].allTreasures[treasuresCount].type.c_str();

				query += "\" x=\"";
				query += std::to_string(mapa[habitacion].allTreasures[treasuresCount].position.X);

				query += "\" y=\"";
				query += std::to_string(mapa[habitacion].allTreasures[treasuresCount].position.Y);

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
