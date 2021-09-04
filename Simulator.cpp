//
// Created by Maxime Blanc on 04/09/2021.
//

#include "Simulator.h"
#include "unistd.h"

Simulator::Simulator(const char *levelFileName) {
	_level.load(levelFileName);
}

void Simulator::simulate() {
	while(!_level.isOver()) {
		_level.print();
		_level.update();
		usleep(30000);
	}
}

Simulator::~Simulator() = default;
