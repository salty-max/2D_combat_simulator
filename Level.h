//
// Created by Maxime Blanc on 04/09/2021.
//

#pragma once

#include "Soldier.h"
#include <string>
#include <vector>

class Level {
public:
	Level();
	~Level();
	void load(const char* fileName);
	void print();
	void update();

	char getTile(int x, int y);
	void setTile(int x, int y, char tile);

private:
	void _setupArmies();

private:
	std::vector<std::string> _levelData;
	std::vector<Soldier *> _armies[2];
};
