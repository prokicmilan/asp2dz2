#pragma once
#include "twothreefour.h"

class cfs {
public:
	static cfs* getInstance();
	bool hasTree() const;
	void setTree(TwoThreeFour *tree);
	void reset();
	void reset(std::ifstream &inFile);
	void singleStep(const long timeSlice, const bool rb = false);
	void simulate(std::ofstream &outFile, const long timeSlice, bool rb = false);
private:
	static cfs *instance;
	TwoThreeFour *tree;

	cfs();
	~cfs();
};
