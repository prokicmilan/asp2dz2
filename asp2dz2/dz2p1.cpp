#include <iostream>
#include "process.h"
#include "twothreefour.h"
#include <string>

int main(void) {
	TwoThreeFour *tree;
	std::string names[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	tree = new TwoThreeFour();
	for (int i = 0; i < 26; i++) {
		tree->addKey(new Process(names[i], i * 10, i * 10));
	}
	std::cout << *tree;
	delete tree;

	return 0;
}