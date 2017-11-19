#include <iostream>
#include "process.h"
#include "twothreefour.h"
#include <string>

int main(void) {
	TwoThreeFour *tree;
	//std::string names[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	std::string names[9] = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
	Process *tst = nullptr;
	Process *in = nullptr;

	tree = new TwoThreeFour();
	for (int i = 0; i < 9; i++) {
		if (names[i] == "E") {
			tst = new Process(names[i], i * 10, i * 10);
			tst->setWaitingTime(i * 10);
			tree->addKey(tst);
		}
		else {
			in = new Process(names[i], i * 10, i * 10);
			in->setWaitingTime(i * 10);
			tree->addKey(in);
		}

	}
	std::cout << *tree;
	std::cout << "Deleting I" << std::endl;
	tree->delKey(tst);
	std::cout << *tree;
	delete tree;

	return 0;
}