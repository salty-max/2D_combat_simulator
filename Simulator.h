//
// Created by Maxime Blanc on 04/09/2021.
//

#pragma once

#include "Level.h"

class Simulator {
public:
	explicit Simulator(const char* levelFileName);
	void simulate();
	~Simulator();
private:
	Level _level;
};
