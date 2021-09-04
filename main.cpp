#include "Simulator.h"

int main() {
	Simulator simulator("battlefield.txt");

	simulator.simulate();

	getchar();
	return 0;
}
