#include <iostream>
#include <fstream>
#include "process.h"
#include "twothreefour.h"
#include <string>
#include "cfs.h"

using namespace std;

int main(void) {
	TwoThreeFour *tree = new TwoThreeFour();
	cfs *instance;
	ofstream file;
	string names[11] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K" };

	for (int i = 0; i < 11; i++) {
		tree->addKey(new Process(names[i], (i + 1) * 10, (i + 1) * 10));
	}
	instance = cfs::getInstance();
	instance->setTree(tree);
	instance->singleStep(10);

	return 0;
}