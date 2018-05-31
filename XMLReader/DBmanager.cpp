#include "DBmanager.h"


DBmanager::DBmanager()
{
}

bool DBmanager::Connect(char* host, char* user, char* pass) {
	bool connectionSuccefull = false;
	for (int actualApptemps = 1;
		(actualApptemps <= numberOfRetries && !connectionSuccefull);
		actualApptemps++)
	{
		try {
			driver = get_driver_instance();
			con = driver->connect(host, user, pass);
			stmt = con->createStatement();
			stmt->execute("USE gamedb");
			connectionSuccefull = true;
		}
		catch (sql::SQLException& e) {
			std::cout << "Code " << e.getErrorCode() <<
				" Error at connecting database\n";

			time(&start);
			std::cout << "Attempting to reconnect in " << secondsToRetry << " seconds.\n" <<
				"attempt " << actualApptemps << " of " << numberOfRetries << "\n" <<
				"----------\n";
			do {
				time(&end);
				pausedTime = difftime(end, start);
			} while (pausedTime < secondsToRetry);
		}
	}

	if (!connectionSuccefull) {
		std::cout << "Can't connect to server.\n" <<
			"Please, wait a moment and try again.\n" << "----------\n";
	}

	return connectionSuccefull;
}

bool DBmanager::Login(std::string user, std::string pass) {
	bool loginResult = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT * FROM Users WHERE user = '" + user + "' AND password = '" + pass + "'";
			result = stmt->executeQuery(query.c_str());

			if (result->next()) {
				std::cout << "Bienvenido " << result->getString("user").c_str() << '!' << std::endl;
				loginResult = true;
			}
			else {
				std::cout << "Error al iniciar sesion, intentalo mas tarde." << std::endl;
				loginResult = false;
			}
			delete(result);
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
			loginResult = false;
		}
		delete(stmt);
		delete(con);
	}

	return loginResult;
}

bool DBmanager::Register(std::string user, std::string pass, std::string passConf) {
	bool registerResult = false;
	if (pass == passConf) {
		if (Connect(HOST, USER, PASSWORD)) {
			try {
				query = "SELECT * FROM Users WHERE mail = '" + user + "'";
				result = stmt->executeQuery(query.c_str());
				if (result->next()) {
					std::cout << "Este correo ya esta en uso, introduce uno diferente por favor" << std::endl;
				}
				else {
					prep_stmt = con->prepareStatement("INSERT INTO Users(`user`, `password`, `mail`) VALUES(?, ?, ?)");
					prep_stmt->setString(1, user.c_str());
					prep_stmt->setString(2, pass.c_str());
					prep_stmt->execute();
					delete (prep_stmt);

					std::cout << "Usuario registrado correctamente" << std::endl;
					registerResult = true;
					std::cout << "Bienvenido " << user << " a nuestro juego de mazmorras." << std::endl << "Parece que es tu primera vez jugando, vamos a crearte un nuevo personaje" << std::endl;
					delete(result);
				}
			}
			catch (sql::SQLException& e) {
				std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
			}
		}

		delete(stmt);
		delete(con);
	}
	else {
		std::cout << "Tu clave de identificacion no coincide" << std::endl;
	}
	return registerResult;
}

void DBmanager::InsertCoin(int id_character, int coin)
{
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			int actualGold = 0;
			query = "SELECT gold FROM `Characters` WHERE id= " + std::to_string(id_character);
			result = stmt->executeQuery(query.c_str());

			if (result->next()) {
				actualGold = result->getInt("gold");

				prep_stmt = con->prepareStatement("UPDATE Characters SET `gold` = ? WHERE `id` = ?");
				prep_stmt->setInt(1, coin + actualGold);
				prep_stmt->setInt(2, id_character);
				prep_stmt->execute();
				delete (prep_stmt);
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
		}
	}
}

bool DBmanager::ShowCharacterInventory(int id_character) {
	bool inventoryFound = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT Inventories.id, Inventories.name, Inventories.attack, Inventories.defense, Inventories.value ";
			query += "FROM Inventories ";
			query += "INNER JOIN Characters_inventories ";
			query += "ON Inventories.id = Characters_inventories.inventories_id_inventory ";
			query += "INNER JOIN Characters ";
			query += "ON Characters_inventories.characters_id_character = Characters.id";
			query += "WHERE Characters.id= " + std::to_string(id_character);
			result = stmt->executeQuery(query.c_str());

			int sellValue = 0;
			std::cout << "Your inventory:\n";
			while (result->next()) {
				inventoryFound = true;
				sellValue = result->getInt("value");
				std::cout <<
					"Numero de inventario -> " << result->getString("id").c_str() << "\t" <<
					"Nombre -> " << result->getString("name").c_str() << "\t" <<
					"Ataque -> " << result->getString("attack").c_str() << "\t" <<
					"Defensa -> " << result->getString("defense").c_str() << "\t" <<
					"Valor -> " << (sellValue / 3) << "\t" <<
					"\n--------------------------------------------------------------------\n";
			}
			if (!inventoryFound) {
				std::cout << "Tu inventario esta vacio actualmente." << std::endl;
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
		}
	}
	return inventoryFound;
}

bool DBmanager::ShowCharacterStats(int id_character, std::string user) {
	bool searchResult = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT `id`, Characters.name AS 'Character_name' , `level`, `XP`, `gold`, Races.name AS 'Race_name' ";
			query += "FROM `Characters` ";
			query += "INNER JOIN Races ";
			query += "ON Characters.races_id_race = Races.id ";
			query += "INNER JOIN Characters_users ";
			query += "ON Characters.id = Characters_users.characters_id_character ";
			query += "INNER JOIN Users ";
			query += "ON Characters_users.users_id_user = Users.id";
			query += "WHERE Users.user = '" + user + "' AND `id` = " + std::to_string(id_character);
			result = stmt->executeQuery(query.c_str());

			if (result->next()) {
				std::cout << "Stats of " << result->getString("Character_name").c_str() <<
					"Nivel -> " << result->getString("level").c_str() << "\t" <<
					"XP -> " << result->getString("XP").c_str() << "\t" <<
					"Oro -> " << result->getString("gold").c_str() << "\t" <<
					"Raza -> " << result->getString("Race_name").c_str() << "\n";
				searchResult = true;
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
		}
	}
	return searchResult;
}


bool DBmanager::ShowRaces() {
	bool showResult = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT * FROM `Races`";
			result = stmt->executeQuery(query.c_str());

			std::cout << "List of existing races:\n";
			while (result->next()) {
				std::cout <<
					"Numero -> " << result->getString("id").c_str() << "\t" <<
					"Nombre -> " << result->getString("name").c_str() << "\t" <<
					"Ataque -> " << result->getString("base_attack").c_str() << "\t" <<
					"Defensa -> " << result->getString("base_defense").c_str() << "\n";
			}
			showResult = true;
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
		}
	}

	delete(stmt);
	delete(con);

	return showResult;
}

int DBmanager::ShowUserCharacters(std::string user) {
	int charactersFound = -1;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT `id_character`, Characters.name AS 'Character_name' , `level`, `XP`, `gold`, Races.name AS 'Race_name' ";
			query += "FROM `Characters` ";
			query += "INNER JOIN Races ";
			query += "ON Characters.races_id_race = Races.id";
			query += "INNER JOIN Characters_users ";
			query += "ON Characters.id= Characters_users.characters_id_character ";
			query += "INNER JOIN Users ";
			query += "ON Characters_users.users_id_user = Users.id";
			query += "WHERE Users.user = '" + user + "'";
			result = stmt->executeQuery(query.c_str());

			charactersFound = 0;
			std::cout << "List of created characters:\n";
			while (result->next()) {
				charactersFound++;
				std::cout <<
					"Id de personaje -> " << result->getString("id").c_str() << "\t" <<
					"Nombre -> " << result->getString("Character_name").c_str() << "\t" <<
					"Nivel -> " << result->getString("level").c_str() << "\t" <<
					"Oro -> " << result->getString("gold").c_str() << "\t" <<
					"Raza -> " << result->getString("Race_name").c_str() << "\t";
			}
			if (charactersFound == 0) {
				std::cout << "No tienes personajes registrados" << std::endl << "Crea un nuevo personaje para poder jugar";
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << e.getErrorCode() << std::endl << "Error en la conexion" << std::endl;
		}
	}

	return charactersFound;
}

bool DBmanager::SelectUserCharacter(std::string mail, int characterID) {
	int searchResult = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT `id_character`, Characters.name AS 'Character_name' , `level`, `XP`, `gold`, Races.name AS 'Race_name' ";
			query += "FROM `Characters` ";
			query += "INNER JOIN Races ";
			query += "ON Characters.races_id_race = Races.id";
			query += "INNER JOIN Characters_users ";
			query += "ON Characters.id= Characters_users.characters_id_character ";
			query += "INNER JOIN Users ";
			query += "ON Characters_users.users_id_user = Users.id";
			query += "WHERE Users.mail = '" + mail + "' AND `id` = " + std::to_string(characterID);
			result = stmt->executeQuery(query.c_str());

			
			if (result->next()) {
				searchResult = true;
			}

			if (searchResult) {
				std::cout << result->getString("Character_name").c_str() << " seleccionado" << std::endl << "Preparate";
			}
			else {
				std::cout << "Personaje no encontrado" << std::endl << "Probablemente el id introducido es erroneo." << std::endl;
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Ninguna personaje ha sido encontrado" << std::endl << "Probablemente el id introducido no existe" << std::endl;
		}
	}

	return searchResult;
}

bool DBmanager::AddCharacterToUser(int race, std::string name, std::string user) {
	bool insertResult = false;
	if (Connect(HOST, USER, PASSWORD)) {
		try {
			query = "SELECT * FROM `Races` WHERE id = " + std::to_string(race);
			result = stmt->executeQuery(query.c_str());
			if (result->next()) {
				int initialAttack = result->getInt("base_attack");
				int initialDefense = result->getInt("base_defense");

				query = "SELECT `id_user` FROM `Users` WHERE `user` = '" + user + "'";
				result = stmt->executeQuery(query.c_str());

				if (result->next()) {
					int idUser = result->getInt("id");

					prep_stmt = con->prepareStatement("INSERT INTO Characters(`name`, `level`, `races_id_race`) VALUES(?, ?, ?)");
					prep_stmt->setString(1, name.c_str());
					prep_stmt->setInt(2, 1);
					prep_stmt->setInt(3, race);
					prep_stmt->execute();
					delete (prep_stmt);

					query = "SELECT `id_character`, `name` FROM Characters WHERE `name` = '" + name + "'";
					result = stmt->executeQuery(query.c_str());
					int idCharacter = 0;
					if (result->next()) {
						idCharacter = result->getInt("id");
					}

					prep_stmt = con->prepareStatement("INSERT INTO Stats(`characters_id_character`, `attack`, `defense`) VALUES(?, ?, ?)");
					prep_stmt->setInt(1, idCharacter);
					prep_stmt->setInt(2, initialAttack);
					prep_stmt->setInt(3, initialDefense);
					prep_stmt->execute();
					delete (prep_stmt);

					prep_stmt = con->prepareStatement("INSERT INTO Characters_users(`users_id_user`, `characters_id_character`) VALUES (?, ?)");
					prep_stmt->setInt(1, idUser);
					prep_stmt->setInt(2, idCharacter);
					prep_stmt->execute();
					delete (prep_stmt);

					std::cout << "Personaje creado satisfactoriamente" <<std::endl;
					insertResult = true;
				}
				else {
					std::cout << "Error: El usuario introducido no existe" << std::endl;
				}
			}
			else {
				std::cout << "Error: La raza introducida no existe" << std::endl;
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "Codigo de error: " << std::endl << e.getErrorCode() << std::endl << "Error at some point on connection\n";
		}
	}

	delete(stmt);
	delete(con);
	return insertResult;
}


DBmanager::~DBmanager()
{
}
