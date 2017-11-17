#pragma once
#include "treenode.h"

class TwoThreeFour {
public:
	TwoThreeFour();
	~TwoThreeFour();
	const Process* findKeyWait(const long time) const;
	const Process* findKeyExec(const long time) const;
	void addKey(Process *p);
private:
	TreeNode *root;
};
