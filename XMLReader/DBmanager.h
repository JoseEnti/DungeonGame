#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <mysql_connection.h>
#include <cppconn\driver.h>
#include <cppconn\exception.h>
#include <cppconn\statement.h>
#include <cppconn\prepared_statement.h>
#include <cppconn\resultset.h>

#define HOST "192.168.122.2:3306"
#define USER "root"
#define PASSWORD "enti" // Poner una contraseña aqui es de ****

class DBmanager
{
public:
	DBmanager();
	~DBmanager();
	
	bool Login(std::string mail, std::string pass);
	bool Register(std::string user, std::string pass, std::string passConf);
	bool ShowRaces();
	int ShowUserCharacters(std::string mail);
	bool SelectUserCharacter(std::string mail, int characterID);
	bool AddCharacterToUser(int race, std::string name, std::string mail);
	void InsertCoin(int id_character, int coin);
	bool ShowCharacterInventory(int id_character);
	bool ShowCharacterStats(int id_character, std::string mail);
	void SelectMap(int mapNumber);

private:
	bool Connect(char* host, char* user, char* pass);

	int numberOfRetries = 5;
	float secondsToRetry = 2.0f;
	double pausedTime;
	time_t start, end;

	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::PreparedStatement *prep_stmt;
	sql::ResultSet *result;

	std::string query;
};

