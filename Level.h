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
	void setTile(int x, int y, char tile, Soldier *soldier);
	Soldier *getSoldier(int x, int y);

private:
	void _setupArmies();
	void _processSoldierMove(char direction, Soldier *soldier);
	void _moveSoldier(Soldier *soldier, int dx, int dy);
	void _battle(Soldier *attacker, int tx, int ty);

	std::vector<std::string> _levelData;
	std::vector<std::vector<Soldier *> > _soldiersGrid;
	std::vector<Soldier *> _armies[NUM_ARMIES];
};
