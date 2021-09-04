//
// Created by Maxime Blanc on 04/09/2021.
//

#include "Soldier.h"
#include <ctime>
#include <random>

Soldier::Soldier(std::string name, char tile, int level, int health, int attack,
             int defense, int xpValue, int army) {
	_name = name;
	_tile = tile;
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_xpValue = xpValue;
	_army = army;
}

void Soldier::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Soldier::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

std::string Soldier::getName() { return _name; }

int Soldier::attack() {
	static std::default_random_engine randomEngine(time(nullptr));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Soldier::takeDamage(int attackValue) {
	attackValue -= _defense;

	if (attackValue > 0) {
		_health -= attackValue;

		if (_health <= 0) {
			return _xpValue;
		}
	}

	return 0;
}

char Soldier::getMove(std::vector<Soldier *> armies[], int numArmies) {
	Soldier *closestEnemy = _getClosestEnemy(armies, numArmies);
	if (closestEnemy == nullptr) return 0;

	int tx, ty;
	closestEnemy->getPosition(tx, ty);

	int dx = _x - tx;
	int dy = _y - ty;
	int adx = abs(dx);
	int ady = abs(dy);

	if (adx > ady) { // Moving along X axis
		// If dx is positive, target is to the left
		if (dx > 0) {
			return 'a';
		} else {
			return 'd';
		}
	} else { // Moving along Y axis
		// If dy is positive, target is upwards
		if (dy > 0) {
			return 'w';
		} else {
			return 's';
		}
	}
}

Soldier *Soldier::_getClosestEnemy(std::vector<Soldier *> armies[], int numArmies) const {
	Soldier *closestEnemy = nullptr;
	int closestDistance = INT_MAX;
	int tx, ty;
	int distance;

	for (int a = 0; a < armies->size(); a++) {
		if (a != _army) {
			for (auto & e : armies[a]) {
				e->getPosition(tx, ty);
				distance = abs(tx - _x) + abs(ty - _y);
				if (distance < closestDistance) {
					closestEnemy = e;
					closestDistance = distance;
				}
			}
		}
	}

	return closestEnemy;
}
