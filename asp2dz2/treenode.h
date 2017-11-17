#pragma once

#include <vector>
#include "process.h"

class TreeNode {
public:
	TreeNode();
	~TreeNode();
	const Process* findKeyWait(const long time) const;
	const Process* findKeyExec(const long time) const;
	TreeNode* getNextWait(const long time) const;
	TreeNode* getNextExec(const long time) const;
	TreeNode* getParent() const;
	void addKey(const Process *key);
	void addNode(const TreeNode *node);
	void removeKey(const Process *key);
	void removeNode(TreeNode *node);

private:
	std::vector<Process*> keys;
	std::vector<TreeNode*> sons;
	TreeNode *parent;
};
