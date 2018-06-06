#include "WorldDungeonFixed.h"
#include "pugixml.hpp"
#include <iostream>
#include "DBmanager.h"

WorldDungeonFixed::WorldDungeonFixed()
{
}

void WorldDungeonFixed::LoadMap(std::string xml) {
	
	int squares = 0;
	int players = 0;
	int enemies = 0;
	int obstacles = 0;
	int items = 0;
	int treasures = 0;

	bool dynamicMemoryLoaded = false;

	int playersCount = 0;
	int enemiesCount = 0;
	int obstaclesCount = 0;
	int itemsCount = 0;
	int treasuresCount = 0;

	typedef const pugi::char_t* pugiCharArray;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(xml.c_str());

	std::cout << "Resultado carga --> " << result.description() << "\n" << std::endl;

	for (int loadNumber = 0; loadNumber <= 1; loadNumber++) {
		pugi::xml_node nodeRoom = doc.child("room");
		pugiCharArray attrRoomSizeX = nodeRoom.attribute("squareAmountX").value();
		pugiCharArray attrRoomSizeY = nodeRoom.attribute("squareAmountY").value();

		std::string roomSizeX(attrRoomSizeX);
		std::string roomSizeY(attrRoomSizeY);

		sizeX = stoi(roomSizeX);
		sizeY = stoi(roomSizeY);

		for (pugi::xml_node nodeSquare = nodeRoom.child("square");
			nodeSquare;
			nodeSquare = nodeSquare.next_sibling("square")) {
			pugiCharArray arrayType = nodeSquare.attribute("type").value();
			pugiCharArray arrayPosX = nodeSquare.attribute("x").value();
			pugiCharArray arrayPosY = nodeSquare.attribute("y").value();

			std::string type(arrayType);
			std::string posX(arrayPosX);
			std::string posY(arrayPosY);

			if (loadNumber == 0) {
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
					obstacles++;
				}
				else if (type == "wall") {
					obstacles++;
				}
			}
			else {
				if (!dynamicMemoryLoaded) {
					SpawnPosition = new Square[players];
					allPlayers = new Player[players];
					allEnemies = new Enemy[enemies];
					allTreasures = new Treasure[treasures];
					allObstacles = new Obstacle[obstacles];
					dynamicMemoryLoaded = true;
				}

				if (type == "player") {
					SpawnPosition[playersCount].X = stoi(posX);
					SpawnPosition[playersCount].Y = stoi(posY);
					allPlayers[playersCount].position.X = stoi(posX);
					allPlayers[playersCount].position.Y = stoi(posY);
					allPlayers[playersCount].gold = 0;
					allPlayers[playersCount].type = type;
					playersCount++;
				}
				else if (type == "enemy") {
					allEnemies[enemiesCount].position.X = stoi(posX);
					allEnemies[enemiesCount].position.Y = stoi(posY);
					allEnemies[enemiesCount].type = type; // TEMPORAL
					enemiesCount++;
				}
				else if (type == "gold") {
					allTreasures[treasuresCount].position.X = stoi(posX);
					allTreasures[treasuresCount].position.Y = stoi(posY);
					allTreasures[treasuresCount].value = rand() % (50 + 1 - 10) + 10; // TEMPORAL
					allTreasures[treasuresCount].pickedUp = false;
					allTreasures[treasuresCount].type = type;
					treasuresCount++;
				}
				else if (type == "door") {
					allObstacles[obstaclesCount].position.X = stoi(posX);
					allObstacles[obstaclesCount].position.Y = stoi(posY);
					allObstacles[obstaclesCount].type = type; // TEMPORAL
					obstaclesCount++;
				}
				else if (type == "wall") {
					allObstacles[obstaclesCount].position.X = stoi(posX);
					allObstacles[obstaclesCount].position.Y = stoi(posY);
					allObstacles[obstaclesCount].type = type; // TEMPORAL
					obstaclesCount++;
				}
				squares++;
				
				
			}
		}
	}
	numberOfSquares = squares;
	numberOfObstacles = obstacles;
	numberOfTreasures = treasures;
	numberOfEnemies = enemies;
	numberOfPlayers = players;
	
}

int WorldDungeonFixed::GetWorldX() {
	return sizeX;
}

int WorldDungeonFixed::GetWorldY() {
	return sizeY;
}

std::string WorldDungeonFixed::GetObstacleType(int obstacleID) {
	return allObstacles[obstacleID].type;
}

int WorldDungeonFixed::GetObstacleX(int obstacleID) {
	return allObstacles[obstacleID].position.X;
}

int WorldDungeonFixed::GetObstacleY(int obstacleID) {
	return allObstacles[obstacleID].position.Y;
}

bool WorldDungeonFixed::GetTreasurePickedUp(int treasureID) {
	return allTreasures[treasureID].pickedUp;
}

void WorldDungeonFixed::SetTreasurePickedUp(int treasureID, bool pickedUp) {
	allTreasures[treasureID].pickedUp = pickedUp;
}

int WorldDungeonFixed::GetTreasureValue(int treasureID) {
	return allTreasures[treasureID].value;
}

int WorldDungeonFixed::GetTreasureX(int treasureID) {
	return allTreasures[treasureID].position.X;
}

int WorldDungeonFixed::GetTreasureY(int treasureID) {
	return allTreasures[treasureID].position.Y;
}

int WorldDungeonFixed::GetEnemyX(int enemyID) {
	return allEnemies[enemyID].position.X;
}

int WorldDungeonFixed::GetEnemyY(int enemyID) {
	return allEnemies[enemyID].position.Y;
}

int WorldDungeonFixed::GetPlayerX() {
	return allPlayers[0].position.X;
}

int WorldDungeonFixed::GetPlayerY() {
	return allPlayers[0].position.Y;
}

void WorldDungeonFixed::SetPlayerX(int new_positionX) {
	if (new_positionX < GetWorldX() && new_positionX >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < numberOfObstacles; i++) {
			if (GetObstacleX(i) == new_positionX && GetObstacleY(i) == GetPlayerY()) {
				if (GetObstacleType(i) == "wall") {
					wallCrash = true;
					i = numberOfObstacles;
				}
				else if (GetObstacleType(i) == "door") {
					wallCrash = false;
					if (new_positionX > GetPlayerX()) {
						new_positionX += 1;
					}
					else if (new_positionX < GetPlayerX()) {
						new_positionX -= 1;
					}
					i = numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			allPlayers[0].position.X = new_positionX;
		}
		playerHasCrashedWithEnemy();
	}
}

void WorldDungeonFixed::SetPlayerY(int new_positionY) {
	if (new_positionY < GetWorldY() && new_positionY >= 0) {
		bool wallCrash = false;
		for (int i = 0; i < numberOfObstacles; i++) {
			if (GetObstacleX(i) == GetPlayerX() && GetObstacleY(i) == new_positionY) {
				if (GetObstacleType(i) == "wall") {
					wallCrash = true;
					i = numberOfObstacles;
				}
				else if (GetObstacleType(i) == "door") {
					wallCrash = false;
					if (new_positionY > GetPlayerY()) {
						new_positionY += 1;
					}
					else if (new_positionY < GetPlayerY()) {
						new_positionY -= 1;
					}
					i = numberOfObstacles;
				}
			}
			else {
				wallCrash = false;
			}
		}

		if (wallCrash == false) {
			allPlayers[0].position.Y = new_positionY;
		}
		playerHasCrashedWithEnemy();
	}
}

void WorldDungeonFixed::playerHasCrashedWithEnemy() {
	for (int i = 0; i < numberOfEnemies; i++) {
		if (GetEnemyX(i) == GetPlayerX() && GetEnemyY(i) == GetPlayerY()) {
			allPlayers[0].position.X = SpawnPosition[0].X;
			allPlayers[0].position.Y = SpawnPosition[0].Y;
			i = numberOfEnemies;
		}
	}
}

int WorldDungeonFixed::PickUpTreasure() {
	int treasureValue = 0;
	for (int i = 0; i < numberOfTreasures; i++) {
		if (GetTreasureX(i) == GetPlayerX() && GetTreasureY(i) == GetPlayerY()) {
			if (!GetTreasurePickedUp(i)) {
				SetTreasurePickedUp(i, true);
				treasureValue = GetTreasureValue(i);
				allPlayers[0].gold += treasureValue;
				std::cout << "Gold picked == " << treasureValue << "\n";
				i = numberOfTreasures;
			}
		}
	}
	return treasureValue;
}

void WorldDungeonFixed::DrawMap(sf::RenderWindow &window) {
	window.clear(sf::Color::Black);

	int chestPlaced = 0;
	int enemyPlaced = 0;
	int obstaclePlaced = 0;
	int playerPlaced = 0;

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
	for (int i = 0; i <= 4; i++) {
		for (int y = 0; y < GetWorldY(); y++) {
			for (int x = 0; x < GetWorldX(); x++) {
				if (i == 0) {
					{
						groundField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(groundField);
					}
				}
				else if (i == 1) {
					if ((allTreasures[chestPlaced].position.X) == x && (allTreasures[chestPlaced].position.Y) == y) {
						if (allTreasures[chestPlaced].pickedUp == false) {
							chestField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(chestField);
						}
						else {
							if ((allTreasures[chestPlaced].position.X) == GetPlayerX() && (allTreasures[chestPlaced].position.Y) == GetPlayerY()) {
								playerField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(playerField);
							}
							else if (allTreasures[chestPlaced].pickedUp == true) {
								groundField.setPosition(sf::Vector2f(x * 32, y * 32));
								window.draw(groundField);
							}
						}
						chestPlaced++;
					}
				}
				else if (i == 2) {
					if ((allEnemies[enemyPlaced].position.X) == x && (allEnemies[enemyPlaced].position.Y) == y) {
						enemyField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(enemyField);
						enemyPlaced++;
					}
				}
				else if (i == 3) {
					if ((allObstacles[obstaclePlaced].position.X) == x && (allObstacles[obstaclePlaced].position.Y) == y) {
						if (allObstacles[obstaclePlaced].type == "wall") {
							wallField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(wallField);
						}
						else if (allObstacles[obstaclePlaced].type == "door") {
							doorField.setPosition(sf::Vector2f(x * 32, y * 32));
							window.draw(doorField);
						}
						obstaclePlaced++;
					}
				}
				else if (i == 4) {
					if ((allPlayers[playerPlaced].position.X) == x && (allPlayers[playerPlaced].position.Y) == y) {
						playerField.setPosition(sf::Vector2f(x * 32, y * 32));
						window.draw(playerField);
						playerPlaced++;
					}
				}
			}
		}
	}
}

void WorldDungeonFixed::saveGame() {
	typedef const pugi::char_t* pugiCharArray;

	int playersCount = 0;
	int enemiesCount = 0;
	int obstaclesCount = 0;
	int itemsCount = 0;
	int treasuresCount = 0;

	std::string mapName;
	std::cout << "Introduce el nombre del mapa que quieres guardar." << std::endl;
	std::cin >> mapName;
	
	DBmanager db;
	
	std::string query = "<room squareAmountX='";
	sql::PreparedStatement *prep_stmt;
	prep_stmt = con->prepareStatement("INSERT INTO maps(`MapName`, `MapContent`) VALUES(?, ?)");
	prep_stmt->setString(1, mapName);

	pugi::xml_document doc;
	pugi::xml_node nodeRoom = doc.append_child("room");
	query += std::to_string(GetWorldX());
		
	query += "' squareAmountY='";
	query += std::to_string(GetWorldY());
	query += "'>";

	for (int i = 0; i < numberOfSquares; i++) 
	{
		pugi::xml_node nodeSquare = nodeRoom.append_child("square");

		if (playersCount < numberOfPlayers) 
		{
			query += "<square type='";
			query += allPlayers[playersCount].type.c_str();
			
			query += "' x='";
			query += allPlayers[playersCount].position.X;

			query += "' y='";
			query += allPlayers[playersCount].position.Y;

			query += "' />";
			playersCount++;
		}
		else if (obstaclesCount < numberOfObstacles) 
		{
			query += "<square type='";
			query += allObstacles[obstaclesCount].type.c_str();

			query += "' x='";
			query += allObstacles[obstaclesCount].position.X;

			query += "' y='";
			query += allObstacles[obstaclesCount].position.Y;

			query += "' />";
			obstaclesCount++;
		}
		else if (enemiesCount < numberOfEnemies) 
		{
			query += "<square type='";
			query += allEnemies[enemiesCount].type.c_str();

			query += "' x='";
			query += allEnemies[enemiesCount].position.X;

			query += "' y='";
			query += allEnemies[enemiesCount].position.Y;

			query += "' />";
			enemiesCount++;
		}
		else if (treasuresCount < numberOfTreasures) 
		{
			query += "<square type='";
			query += allTreasures[treasuresCount].type.c_str();

			query += "' x='";
			query += allTreasures[treasuresCount].position.X;

			query += "' y='";
			query += allTreasures[treasuresCount].position.Y;

			query += "' />";
			treasuresCount++;
		}
		query += "</room>";
	}
	prep_stmt->setString(2, query);
	prep_stmt->execute();
	delete (prep_stmt);
}

WorldDungeonFixed::~WorldDungeonFixed()
{
	delete[] SpawnPosition;
	delete[] allEnemies;
	delete[] allTreasures;
	delete[] allObstacles;
}
