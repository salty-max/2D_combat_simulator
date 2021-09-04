//
// Created by Maxime Blanc on 04/09/2021.
//

#pragma once

#include <string>

class Soldier {
public:
	Soldier(std::string name, char tile, int level, int health, int attack,
	      int defense, int xpValue);
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);
	std::string getName();

	int attack();
	int takeDamage(int attackValue);

	char getMove(int playerX, int playerY);

private:
	std::string _name;
	char _tile;
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _xpValue;

	// Position
	int _x;
	int _y;
};
