#include "WorldDungeonFixed.h"
#include <iostream>
#include <fstream>
#include "DBmanager.h"

int actualPlayerY = NULL;
int actualPlayerX = NULL;

bool loggedIn = false;
bool createRace = false;
bool raceCreated = false;
bool connectionSuccefull = false;
bool playableCharacterChoosen = false;

void game(int characterChoosen);
void NotLoggedMenu(bool& exit);
void LoggedMenu(bool &exit);
void ChooseCharacter();
void CreateNewCharacter();

DBmanager database;

std::string user;
std::string pass;
std::string confirmPass;
int optionChoosen;

int main() {
	bool exit = false;

	while (!loggedIn && !exit) {
		NotLoggedMenu(exit);
	}

	while (loggedIn && !exit) {
		LoggedMenu(exit);
	}
	return 0;
}

void NotLoggedMenu(bool& exit) {
	std::cout << "1 - Inicio de sesion " << "2 - Registrar usuario " << "0 - Cerrar el programa" << std::endl;
	std::cin >> optionChoosen;

	switch (optionChoosen) {
	case 1:
		std::cout << "Introduce tu nombre de usuario" << std::endl;
		std::cin >> user;
		std::cout << "Introduce clave de identificacion" << std::endl;
		std::cin >> pass;

		loggedIn = database.Login(user, pass);
		if (loggedIn) {
			LoggedMenu(exit);
		}
		break;
	case 2:
		std::cout << "Inserta un nuevo nombre de usuario" << std::endl;
		std::cin >> user;
		std::cout << "Inserta una nueva clave de identificacion" << std::endl;
		std::cin >> pass;
		std::cout << "Confirma la clave de identificacion" << std::endl;
		std::cin >> confirmPass;

		loggedIn = database.Register(user, pass, confirmPass);
		if (loggedIn) {
			CreateNewCharacter();
		}
		break;
	case 0:
		std::cout << "Cerrando programa..." << std::endl;
		exit = true;
		break;
	default:
		std::cout << "Esa opcion no esta disponible" << std::endl << "Intentalo de nuevo.";
		break;
	}
}

void LoggedMenu(bool &exit) {
	std::cout << "Bienvenido" << std::endl << "1 - Jugar\n" << std::endl << "2 - Crear personaje" << std::endl << "0 - Cerrar sesion" << std::endl;
	std::cin >> optionChoosen;

	switch (optionChoosen) {
	case 1:
		ChooseCharacter();
		break;
	case 2:
		CreateNewCharacter();
		break;
	case 0:
		std::cout << "Sesion cerrada correctamente" << std::endl;
		NotLoggedMenu(exit);
		break;
	default:
		std::cout << "Esa opcion no esta disponible" << std::endl  << "Intentalo de nuevo.";
		break;
	}
}

void ChooseCharacter() {
	int racesFound = database.ShowUserCharacters(user);

	std::cout << "Elije el id del personaje que quieres seleccionar" << std::endl;
	std::cin >> optionChoosen;
	// Aun no funciona bien
	playableCharacterChoosen = database.SelectUserCharacter(user, optionChoosen);
	
	int mapInput = NULL;
	
	std::cout << "Introduce el id del mapa al que quieres jugar" << std::endl;
	std::cin >> mapInput;

	std::string xml = database.SelectMap(mapInput);
	
	std::ofstream xmlFile;
	xmlFile.open("dungeon.xml");
	xmlFile << xml;
	xmlFile.close();
	if (playableCharacterChoosen) {
		std::cout << "Iniciando el juego..." << std::endl;
		game(optionChoosen);
	}
}

void CreateNewCharacter() {
	std::cout << std::endl;

	while (!raceCreated) {
		std::string characterName;
		int optionChoosen = 0;
		connectionSuccefull = database.ShowRaces();

		if (connectionSuccefull) {
			std::cout << "Elije el id de la raza que quieres seleccionar" << std::endl;
			std::cin >> optionChoosen;

			//Mejor no poner espacios. Palabrita del sufidor
			std::cout << "Elije el nombre de tu personaje" << std::endl;
			std::cin >> characterName;

			std::cout << "Creando personaje..." << std::endl;
			raceCreated = database.AddCharacterToUser(optionChoosen, characterName, user);
		}
		else {
			std::cout << "El proceso ha fallado, intentalo de nuevo" << std::endl;
		}
	}
}


void game(int characterChoosen) {

	WorldDungeonFixed world;
	world.LoadMap("RetoDungeon.xml");
	sf::RenderWindow window(sf::VideoMode(world.GetWorldX() * 32, world.GetWorldY() * 32), "BloodBorne 2");

	int treasureValue = 0;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				actualPlayerY = world.GetPlayerY();
				world.SetPlayerY(actualPlayerY -= 1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				actualPlayerY = world.GetPlayerY();
				world.SetPlayerY(actualPlayerY += 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				actualPlayerX = world.GetPlayerX();
				world.SetPlayerX(actualPlayerX -= 1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				actualPlayerX = world.GetPlayerX();
				world.SetPlayerX(actualPlayerX += 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cout << "Tesoro encontrado!" << std::endl;
				treasureValue = world.PickUpTreasure();
				if (treasureValue > 0) {
					database.InsertCoin(characterChoosen, treasureValue);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				database.SelectMap(characterChoosen);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				database.ShowCharacterInventory(characterChoosen);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				database.ShowCharacterStats(characterChoosen, user);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				std::cout << "Guardando partida..." << std::endl;
				world.saveGame();
			}
		}
		world.DrawMap(window);

		window.display();
	}
}