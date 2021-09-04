//
// Created by Maxime Blanc on 04/09/2021.
//

#pragma once

#include "Soldier.h"
#include <string>
#include <vector>

const int NUM_ARMIES = 2;

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
	void _processSoldierMove(char direction, Soldier *soldier);
	void _moveSoldier(Soldier *soldier, int dx, int dy);

	std::vector<std::string> _levelData;
	std::vector<Soldier *> _armies[NUM_ARMIES];
};
