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
	TreeNode* getNextWait(const Process *p) const;
	TreeNode* getNextWait(const long time) const;
	std::array<Process*, 3> getKeys() const;
	std::array<TreeNode*, 4> getSons() const;
	void addKey(Process *key);
	void moveSons(const int disp);
	void setSon(const int pos, TreeNode *node);
	void removeKey(int pos);
	void emptyNode();
	void deleteKey(int pos);
	void removeSon(int pos);
	TreeNode* getBrother(TreeNode *parent, bool left);
	int find(Process *p);
	friend std::ostream& operator<<(std::ostream &os, const TreeNode &t);

private:
	std::array<Process*, 3> keys;
	std::array<TreeNode*, 4> sons;
	void copy(const TreeNode &tn);
	void move(TreeNode &tn);
	template<typename T>
	void write(T &t) const;
	inline void sort() {
		for (unsigned int i = 0; i < keys.size() - 1; i++) {
			for (unsigned int j = i + 1; j < keys.size(); j++) {
				if (keys[i] == nullptr) {
					std::swap(keys[i], keys[j]);
				}
				else if (keys[j] != nullptr && keys[i]->getWaitingTime() >= keys[j]->getWaitingTime()) {
					if (keys[i]->getWaitingTime() == keys[j]->getWaitingTime()) {
						if (keys[i]->getPid() > keys[j]->getPid()) {
							std::swap(keys[i], keys[j]);
						}
					}
					else {
						std::swap(keys[i], keys[j]);
					}
				}
			}
		}
	}
};
