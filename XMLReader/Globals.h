#pragma once
#include <string>

struct Square {
	int X;
	int Y;
};

struct Player {
	Square position;
	int gold;
	std::string type;
};

struct Enemy {
	Square position;
	std::string type;
};

struct Obstacle {
	Square position;
	std::string type;
};

struct Item {
	Square position;
	std::string type;
};

struct Treasure {
	Square position;
	int value;
	bool pickedUp;
	std::string type;
};
struct Door {
	Square position;
	int value;
	std::string type;
};