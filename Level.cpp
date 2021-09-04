//
// Created by Maxime Blanc on 04/09/2021.
//

#include "Level.h"
#include <fstream>
#include <random>

Level::Level() = default;
Level::~Level() {
    for (auto &army : _armies) {
        for (auto &s: army) {
			delete s;
		}
    }
};

void Level::load(const char *fileName) {
	std::ifstream file;
	file.open(fileName);

	if (file.fail()) {
		perror(fileName);
		getchar();
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		_levelData.push_back(line);
		_soldiersGrid.emplace_back();
		_soldiersGrid.back().resize(line.size(), nullptr);
	}

	file.close();

	_setupArmies();
}

void Level::_setupArmies() {
	char tile;
	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			tile = getTile(x, y);
			switch (tile) {
				case '1':
					_armies[0].push_back(new Soldier("Army 1 Grunt", tile, 1, 10, 10, 5, 50, 0));
					_armies[0].back()->setPosition(x, y);
					_soldiersGrid[y][x] = _armies[0].back();
					break;
				case '2':
					_armies[1].push_back(new Soldier("Army 2 Grunt", tile, 1, 10, 10, 5, 50, 1));
					_armies[1].back()->setPosition(x, y);
					_soldiersGrid[y][x] = _armies[1].back();
					break;
				case '#':
				case '.':
					break;
				default:
					printf("WARNING: Unknown tile %c at %d,%d", tile, x, y);
					getchar();
					break;
			}
		}
	}

	std::random_device::result_type seed = std::random_device()();
	std::mt19937 randomEngine(seed);
	Soldier *tmp;

	// Shuffle armies
	for (auto & _army : _armies) {
		for (int j = (int)_army.size() - 1; j > 1; j--) {
			std::uniform_int_distribution<int> randomSwap(0, j - 1);
			int swap = randomSwap(randomEngine);

			tmp = _army[j];
			_army[j] = _army[swap];
			_army[swap] = tmp;
		}
	}
}

void Level::print() {
	printf("%s", std::string(150, '\n').c_str());
	for (int y = 0; y < _levelData.size(); y++) {
		printf("\n");
		for (int x = 0; x < _levelData[y].size(); x++) {
			std::string color;

			if (_levelData[y][x] == '1') {
				color = "\033[1;34m";
			} else if (_levelData[y][x] == '2') {
				color = "\033[1;35m";
			} else {
				color = "\033[1;37m";
			}

			printf("%s%c\033[0m", color.c_str(), _levelData[y][x]);
		}
	}
}

void Level::update() {
	char move;
	int cnt = 0;
	bool isDone = false;

	while (!isDone) {
		isDone = true;
		for (auto &army : _armies) {
			if (cnt < army.size()) {
				move = army[cnt]->getMove(_armies, NUM_ARMIES);
				_processSoldierMove(move, army[cnt]);
				isDone = false;
			}
		}
		cnt++;
	}
}

bool Level::isOver() { return (_armies[0].size() == 0 || _armies[1].size() == 0); }

void Level::_processSoldierMove(char direction, Soldier *soldier) {
	int x, y;
	char nextTile;
	int destX, destY;
	soldier->getPosition(x, y);

	switch (direction) {
		case 'w':
			destX = x;
			destY = y - 1;
			break;
		case 's':
			destX = x;
			destY = y + 1;
			break;
		case 'a':
			destX = x - 1;
			destY = y;
			break;
		case 'd':
			destX = x + 1;
			destY = y;
			break;
		default:
			destX = x;
			destY = y;
			break;
	}

	nextTile = getTile(destX, destY);

	switch (nextTile) {
		case '#':
			break;
		case '.':
			_moveSoldier(soldier, destX, destY);
		default:
			_battle(soldier, destX, destY);
			break;
	}
}

void Level::_moveSoldier(Soldier *soldier, int dx, int dy) {
	int x, y;
	soldier->getPosition(x, y);

	setTile(dx, dy, soldier->getTile(), soldier);
	setTile(x, y, '.', nullptr);
	soldier->setPosition(dx, dy);
}

void Level::_battle(Soldier *attacker, int tx, int ty) {
	int x, y;
	attacker->getPosition(x, y);
	Soldier *defender = getSoldier(tx, ty);
	int defenderArmy = defender->getArmy();

	if (attacker->getArmy() == defenderArmy) return;

	int result = defender->takeDamage(attacker->attack());

	if (result != 0) {
		for (auto & s : _armies[defenderArmy]) {
			if (s == defender) {
				s = _armies[defenderArmy].back();
				_armies[defenderArmy].pop_back();

				setTile(tx, ty, '.', nullptr);
				break;
			}
		}
	}
}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile, Soldier *soldier) {
	_levelData[y][x] = tile;
	_soldiersGrid[y][x] = soldier;
}

Soldier *Level::getSoldier(int x, int y) { return _soldiersGrid[y][x]; }
