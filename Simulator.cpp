//
// Created by Maxime Blanc on 04/09/2021.
//

#include "Simulator.h"

Simulator::Simulator(const char *levelFileName) {
	_level.load(levelFileName);
}

void Simulator::simulate() {
	bool playing = true;

	while(playing) {
		_level.print();
		_level.update();
	}
}

Simulator::~Simulator() = default;
