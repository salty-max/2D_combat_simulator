//
// Created by Maxime Blanc on 04/09/2021.
//

#pragma once

#include <string>
#include <vector>

class Soldier {
public:
	Soldier(std::string name, char tile, int level, int health, int attack,
	      int defense, int xpValue, int army);
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);
	std::string getName();

	int attack();
	int takeDamage(int attackValue);

	char getMove(std::vector<Soldier *> armies[], int numArmies);

private:
	Soldier *_getClosestEnemy(std::vector<Soldier *> armies[], int numArmies) const;
private:
	std::string _name;
	char _tile;
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _xpValue;
	int _army;

	// Position
	int _x;
	int _y;
};
