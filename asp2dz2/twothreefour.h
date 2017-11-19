#pragma once
#include "treenode.h"

class TwoThreeFour {
public:
	TwoThreeFour();
	~TwoThreeFour();
	const Process* findKeyWait(const long time) const;
	const Process* findKeyExec(const long time) const;
	void addKey(Process *p);
	void delKey(Process *p);

	friend std::ostream& operator<<(std::ostream &os, const TwoThreeFour &t);
private:
	TreeNode *root;
};
