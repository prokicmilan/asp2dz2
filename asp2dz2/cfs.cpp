#include "cfs.h"
#include <fstream>
#include <iostream>

cfs* cfs::instance = nullptr;

cfs::cfs() {
	tree = nullptr;
}

cfs::~cfs() {
	delete tree;
}

cfs* cfs::getInstance() {
	if (instance == nullptr) {
		instance = new cfs();
	}
	return instance;
}

bool cfs::hasTree() const {
	return tree != nullptr;
}

void cfs::setTree(TwoThreeFour* tree) {
	this->tree = tree;
}

void cfs::reset() {
	delete tree;
	tree = nullptr;
}

void cfs::reset(std::ifstream &inFile) {
	if (!inFile.is_open()) {
		std::cerr << "Greska! Fajl nije otvoren." << std::endl;
	}
	else {
		std::string name;
		int maxWaitTime;
		int timeToComplete;
		delete tree;
		tree = new TwoThreeFour();
		while (inFile >> name) {
			inFile >> maxWaitTime;
			inFile >> timeToComplete;
			Process *p = new Process(name, timeToComplete, maxWaitTime);
			tree->addKey(p);
		}
	}
}

void cfs::singleStep(const long timeSlice, const bool rb) {
	if (!hasTree()) {
		std::cerr << "Greska! Stablo nije definisano." << std::endl;
	}
	else {
		bool stop = false;
		char choice;
		long execTime = 0;
		while (!tree->isEmpty() && !stop) {
			Process *exec = nullptr;
			long update;
			if (!rb) {
				std::cout << *tree;
			}
			else {
				tree->printRedBlack();
			}
			exec = tree->getMin();
			std::cout << "Vreme rada = " << execTime << ". Izvrsava se proces " << *exec << std::endl;
			Process *tmp = new Process(*exec);
			int pid = exec->getPid();
			tmp->setPid(pid);
			tree->delKey(exec);
			update = tmp->updateExecutionTime(timeSlice);
			tmp->updateWaitingTime(update);
			if (tmp->getWaitingTime() >= tmp->getMaxWaitingTime()) {
				tmp->setWaitingTime(tmp->getWaitingTime() - tmp->getMaxWaitingTime());
			}
			tree->updateAll(update);
			if (tmp->getExecutionTime() != tmp->getTimeToComplete()) {
				tree->addKey(tmp);
			}
			else {
				delete tmp;
			}
			execTime += update;
			if (!tree->isEmpty()) {
				std::cout << "Nastavak (y/n)?";
				std::cin >> choice;
				if (choice != 'y') {
					stop = true;
				}
			}
		}
	}
}

void cfs::simulate(std::ofstream& outFile, const long timeSlice, bool rb) {
	if (!outFile.is_open()) {
		std::cerr << "Greska! Fajl nije otvoren." << std::endl;
	}
	else if (!hasTree()) {
		std::cerr << "Greska! Stablo nije definisano." << std::endl;
	}
	else {
		int execTime = 0;
		while(!tree->isEmpty()) {
			Process *exec = nullptr;
			long update;
			if (!rb) {
				outFile << *tree;
			}
			else {
				//ispisi crveno crno stablo u fajl :'(
			}
			exec = tree->getMin();
			outFile << "Vreme rada = " << execTime << ". Izvrsava se proces " << *exec << std::endl;
			update = exec->updateExecutionTime(timeSlice);
			exec->updateWaitingTime(update);
			if (exec->getWaitingTime() > exec->getMaxWaitingTime()) {
				exec->setWaitingTime(exec->getWaitingTime() - exec->getMaxWaitingTime());
			}
			Process *tmp = new Process(*exec);
			int pid = exec->getPid();
			tmp->setPid(pid);
			tree->updateAll(update);
			if (tmp->getExecutionTime() != tmp->getTimeToComplete()) {
				tree->addKey(tmp);
			}
		}
	}
}
