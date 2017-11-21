#pragma once
#include "treenode.h"

class TwoThreeFour {
public:
	TwoThreeFour();
	~TwoThreeFour();
	const Process* findKeyWait(const long time) const;
	const Process* findKeyExec(const long time) const;
	Process* getMin();
	void updateAll(const long time);
	bool isEmpty() const;
	void addKey(Process *p);
	void delKey(Process *p);
	void printRedBlack() const;

	friend std::ostream& operator<<(std::ostream &os, const TwoThreeFour &t);
private:
	TreeNode *root;

	void borrowRight(TreeNode *prev, TreeNode *curr, TreeNode *rightBrother);
	void borrowLeft(TreeNode *prev, TreeNode *curr, TreeNode *leftBrother);
	void mergeRight(TreeNode *prev, TreeNode *curr, TreeNode *rightBrother);
	void mergeLeft(TreeNode *prev, TreeNode *curr, TreeNode *leftBrother);
	void fixupNode(TreeNode *prev, TreeNode *curr);
	void printSons(TreeNode *curr, int pos) const;
	template<typename T>
	void write(T &t) const;
};
