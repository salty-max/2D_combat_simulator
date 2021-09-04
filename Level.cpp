//
// Created by Maxime Blanc on 04/09/2021.
//

#include "Level.h"
#include <fstream>

Level::Level() = default;
Level::~Level() = default;

void Level::load(const char *fileName) {
	std::ifstream file;
	file.open(fileName);

	if (file.fail()) {
		perror(fileName);
		getchar();
		exit(1);
	}

	std::string line;
	while(std::getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	_setupArmies();
}

void Level::print() {
	for(int y = 0; y < _levelData.size(); y ++) {
		printf("\n");
		for (int x = 0; x < _levelData[y].size(); x++) {
			printf("%c", _levelData[y][x]);
		}
	}
}

void Level::update() {

}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void Level::_setupArmies() {
	char tile;
	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			tile = getTile(x, y);
			switch(tile) {
				case '1':
					_armies[0].push_back(new Soldier("Army 1 Grunt", tile, 1, 20, 10, 5, 50));
					_armies[0].back()->setPosition(x, y);
					break;
				case '2':
					_armies[1].push_back(new Soldier("Army 2 Grunt", tile, 1, 20, 10, 5, 50));
					_armies[1].back()->setPosition(x, y);
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
}
