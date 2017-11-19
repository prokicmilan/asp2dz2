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
	std::array<Process*, 3> getKeys() const;
	std::array<TreeNode*, 4> getSons() const;
	void addKey(Process *key);
	void moveSons(const int disp);
	void setSon(const int pos, TreeNode *node);
	void removeKey(int pos);
	void removeNode(TreeNode *node);
	TreeNode* getBrother(TreeNode *parent, bool left);
	void swap(Process **p1, Process **p2) {
		Process *tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
	}
	int find(Process *p) {
		for (int i = 0; i < keys.size(); i++) {
			if (keys[i] != nullptr && keys[i] == p) {
				return i;
			}
		}
		return -1;
	}
	void sort() {
		for (int i = 0; i < keys.size() - 1; i++) {
			for (int j = i + 1; j < keys.size(); j++) {
				if (keys[i] == nullptr) {
					//swap(&keys[i], &keys[j]);
					std::swap(keys[i], keys[j]);
				}
				else if (keys[j] != nullptr && keys[i]->getWaitingTime() > keys[j]->getWaitingTime()) {
					//swap(&keys[i], &keys[j]);
					std::swap(keys[i], keys[j]);
				}
			}
		}
	}

private:
	std::array<Process*, 3> keys;
	std::array<TreeNode*, 4> sons;
	void copy(const TreeNode &tn);
	void move(TreeNode &tn);
};
