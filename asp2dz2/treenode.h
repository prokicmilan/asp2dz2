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
	std::vector<Process*> getKeys() const;
	std::vector<TreeNode*> getSons() const;
	void setParent(TreeNode *parent);
	void addKey(Process *key);
	void moveSons(const int disp);
	void setSon(const int pos, TreeNode *node);
	void removeKey(const Process *key);
	void removeNode(TreeNode *node);

private:
	std::vector<Process*> keys;
	std::vector<TreeNode*> sons;
	TreeNode *parent;
};
