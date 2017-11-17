#include "treenode.h"
#include <algorithm>

TreeNode::TreeNode() {
	parent = nullptr;
	for (auto i = 0; i < 3; i++) {
		keys.at(i) = nullptr;
	}
	for (auto i = 0; i < 4; i++) {
		keys.at(i) = nullptr;
	}
}

const Process* TreeNode::findKeyWait(const long time) const {
	for (auto key : keys) {
		if (key->getWaitingTime() == time) {
			return key;
		}
	}
	return nullptr;
}


const Process* TreeNode::findKeyExec(const long time) const {
	for (auto key : keys) {
		if (key->getExecutionTime() == time) {
			return key;
		}
	}
	return nullptr;
}

TreeNode* TreeNode::getParent() const {
	return parent;
}

std::vector<Process*> TreeNode::getKeys() const {
	return keys;
}

std::vector<TreeNode*> TreeNode::getSons() const {
	return sons;
}

void TreeNode::setParent(TreeNode *parent) {
	this->parent = parent;
}


void TreeNode::addKey(Process* key) {
	keys.push_back(key);
	std::sort(keys.begin(), keys.end(), [](Process *ptrA, Process *ptrB) { if (ptrA != nullptr && ptrB != nullptr) { return ptrA->getWaitingTime() < ptrB->getWaitingTime(); }});
}

//metoda koja vraca pokazivac na sledeci cvor u kom se potencijalno moze naci trazeni kljuc
TreeNode* TreeNode::getNextWait(const long time) const {
	//ako je trazeni kljuc manji od prvog, vraca se pokazivac na krajnji levi cvor
	if (time < keys.at(0)->getWaitingTime()) {
		return sons.at(0);
	}
	for (auto i = 0; i < keys.size() - 1; i++) {
		if (keys.at(i + 1) != nullptr) {
			if (keys.at(i)->getWaitingTime() < time && keys.at(i + 1)->getWaitingTime() > time) {
				//ako je trazeni kljuc izmedju dva kljuca, vraca se pokazivac na cvor izmedju njih
				return sons.at(i + 1);
			}
		}
		else {
			//ako naredni kljuc ne postoji, vraca se pokazivac na cvor desno od prethodnog
			return sons.at(i + 1);
		}
	}
	return sons.at(sons.size());
}

TreeNode* TreeNode::getNextExec(const long time) const {
	if (time < keys.at(0)->getExecutionTime()) {
		return sons.at(0);
	}
	for (int i = 0; i < keys.size() - 1; i++) {
		if (keys.at(i + 1) != nullptr) {
			if (keys.at(i)->getExecutionTime() < time && keys.at(i + 1)->getWaitingTime() > time) {
				return sons.at(i + 1);
			}
		}
		else {
			return sons.at(i + 1);
		}
	}
	return sons.at(sons.size());
}
