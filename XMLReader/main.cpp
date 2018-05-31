#include "DBmanager.h"
#include "../XMLReader/Globals.h"

bool loggedIn = false;
bool createRace = false;
bool raceCreated = false;
bool connectionSuccefull = false;
bool playableCharacterChoosen = false;

void NotLoggedMenu(bool& exit);
void LoggedMenu(bool &exit);
void ChooseCharacter();
void CreateNewCharacter();

DBmanager database;

std::string mail;
std::string user;
std::string pass;
std::string confirmPass;
int optionChoosen;

int main1() {
	bool exit = false;

	while (!loggedIn && !exit) {
		NotLoggedMenu(exit);
	}

	while (loggedIn && !exit) {
		LoggedMenu(exit);
	}

	system("pause");
	return 0;
}

void NotLoggedMenu(bool& exit) {
	std::cout << "Choose an option\n" <<
		"1- Login\n" <<
		"2- Register\n" <<
		"0- Exit\n\n" <<
		"-->";
	std::cin >> optionChoosen;

	switch (optionChoosen) {
	case 1:
		std::cout << "Insert mail -> ";
		std::cin >> mail;
		std::cout << "Insert password -> ";
		std::cin >> pass;

		loggedIn = database.Login(mail, pass);
		if (loggedIn) {
			LoggedMenu(exit);
		}
		break;
	case 2:
		std::cout << "Insert a new mail -> ";
		std::cin >> mail;
		std::cout << "Insert a new username -> ";
		std::cin >> user;
		std::cout << "Insert some password -> ";
		std::cin >> pass;
		std::cout << "Confirm that password -> ";
		std::cin >> confirmPass;

		loggedIn = database.Register(mail, user, pass, confirmPass);
		if (loggedIn) {
			CreateNewCharacter();
		}
		break;
	case 0:
		std::cout << "Closing program\n";
		exit = true;
		break;
	default:
		std::cout << "Error reading the option.\n" <<
			"Try again.";
		break;
	}
}

void LoggedMenu(bool &exit) {
	std::cout << "Welcome to the game\n" <<
		"1- Play\n" <<
		"2- Create character\n" <<
		"0- Logout\n\n" <<
		"-->";
	std::cin >> optionChoosen;

	switch (optionChoosen) {
	case 1:
		ChooseCharacter();
		break;
	case 2:
		CreateNewCharacter();
		break;
	case 0:
		std::cout << "Logout succefull\n";
		NotLoggedMenu(exit);
		break;
	default:
		std::cout << "Error reading the option.\n" <<
			"Try again.";
		break;
	}
}

void ChooseCharacter() {
	int racesFound = database.ShowUserCharacters(mail);

	std::cout << "Choose a character to play by it's number -> ";
	std::cin >> optionChoosen;
	// Aun no funciona bien
	playableCharacterChoosen = database.SelectUserCharacter(mail, optionChoosen);

	if (playableCharacterChoosen) {
		std::cout << "Ahora deberias poder jugar xDDD\n";
		game();
	}
}

void CreateNewCharacter() {
	std::cout << "\n";

	while (!raceCreated) {
		std::string characterName;
		int optionChoosen = 0;
		connectionSuccefull = database.ShowRaces();

		if (connectionSuccefull) {
			std::cout << "Choose Race by it's number --> ";
			std::cin >> optionChoosen;

			//Mejor no poner espacios. Palabrita del sufidor
			std::cout << "Ok. now name your new character. --> ";
			std::cin >> characterName;

			std::cout << "Creating character...\n";
			raceCreated = database.AddCharacterToUser(optionChoosen, characterName, mail);
		}
		else {
			std::cout << "unexpected error ocurred. Try again later.\n";
			system("pause");
		}
	}
}