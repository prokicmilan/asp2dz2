#pragma once

#include <array>
#include "process.h"

class TreeNode {
public:
	TreeNode();
	~TreeNode();
	TreeNode(const TreeNode &tn);
	TreeNode(TreeNode &&tn);
	TreeNode& operator=(const TreeNode &tn);
	TreeNode& operator=(TreeNode &&tn);
	const Process* findKeyWait(const long time) const;
	const Process* findKeyExec(const long time) const;
	TreeNode* getNextWait(const long time) const;
	TreeNode* getNextExec(const long time) const;
	TreeNode* getParent() const;
	std::array<Process*, 3> getKeys() const;
	std::array<TreeNode*, 4> getSons() const;
	void setParent(TreeNode *parent);
	void addKey(Process *key);
	void moveSons(const int disp);
	void setSon(const int pos, TreeNode *node);
	void removeKey(const Process *key);
	void removeNode(TreeNode *node);
	inline void swap(Process **p1, Process **p2) {
		Process *tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
	}
	inline int find(Process *p) {
		for (int i = 0; i < keys.size(); i++) {
			if (keys[i] != nullptr && keys[i] == p) {
				return i;
			}
		}
	}

private:
	std::array<Process*, 3> keys;
	std::array<TreeNode*, 4> sons;
	TreeNode *parent;
	void copy(const TreeNode &tn);
	void move(TreeNode &tn);
};
