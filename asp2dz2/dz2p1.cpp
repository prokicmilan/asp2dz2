#include <iostream>
#include <fstream>
#include "process.h"
#include "twothreefour.h"
#include <string>

using namespace std;

int main(void) {
	TwoThreeFour *tree = new TwoThreeFour();
	ofstream file;
	string names[11] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K" };

	for (int i = 0; i < 11; i++) {
		tree->addKey(new Process(names[i], i * 10, i * 10));
	}

	return 0;
}