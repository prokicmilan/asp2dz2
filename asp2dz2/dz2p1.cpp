#include <iostream>
#include "process.h"
#include "twothreefour.h"
#include <string>

int main(void) {
	TwoThreeFour *tree;
	//std::string names[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	std::string names[11] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K" };
	//std::string names[1] = { "A" };
	Process *tst = nullptr;

	tree = new TwoThreeFour();
	for (int i = 0; i < 11; i++) {
		tst = new Process(names[i], i * 10, i * 10);
		tst->setWaitingTime(i * 10);
		tree->addKey(tst);
	}
	std::cout << *tree;
	//std::cout << "Deleting" << std::endl;
	//tst = const_cast<Process *>(tree->findKeyWait(0));
	//tree->delKey(tst);
	//std::cout << *tree;
	delete tree;

	return 0;
}