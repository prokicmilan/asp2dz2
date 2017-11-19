#include "treenode.h"
#include <array>

void TreeNode::copy(const TreeNode& tn) {
	for (int i = 0; i < keys.size(); i++) {
		keys[i] = tn.keys[i];
	}
	for (int i = 0; i < sons.size(); i++) {
		sons[i] = tn.sons[i];
	}
}

void TreeNode::move(TreeNode& tn) {
	keys = tn.keys;
	for (auto &key : tn.keys) {
		key = nullptr;
	}
	sons = tn.sons;
	for (auto &son : tn.sons) {
		son = nullptr;
	}
}

TreeNode::TreeNode() {
	for (auto &key : keys) {
		key = nullptr;
	}
	for (auto &son : sons) {
		son = nullptr;
	}
}

TreeNode::TreeNode(const TreeNode& tn) {
	copy(tn);
}

TreeNode::TreeNode(TreeNode&& tn) {
	move(tn);
}

TreeNode& TreeNode::operator=(const TreeNode &tn) {
	if (this != &tn) {
		copy(tn);
	}
	return *this;
}

TreeNode& TreeNode::operator=(TreeNode &&tn) {
	if (this != &tn) {
		move(tn);
	}
	return *this;
}

TreeNode::~TreeNode() {
	for (auto &key : keys) {
		delete key;
	}
	for (auto &son : sons) {
		son = nullptr;
	}
}

const Process* TreeNode::findKeyWait(const long time) const {
	for (auto key : keys) {
		if (key != nullptr && key->getWaitingTime() == time) {
			return key;
		}
	}
	return nullptr;
}

const Process* TreeNode::findKeyExec(const long time) const {
	for (auto key : keys) {
		if (key != nullptr && key->getExecutionTime() == time) {
			return key;
		}
	}
	return nullptr;
}

std::array<Process*, 3> TreeNode::getKeys() const {
	return keys;
}

std::array<TreeNode*, 4> TreeNode::getSons() const {
	return sons;
}

void TreeNode::addKey(Process* key) {
	keys[2] = key;
	for (int i = 0; i < keys.size() - 1; i++) {
		for (int j = i + 1; j < keys.size(); j++) {
			if (keys[i] == nullptr) {
				swap(&keys[i], &keys[j]);
			}
			else if (keys[j] != nullptr && keys[i]->getWaitingTime() > keys[j]->getWaitingTime()) {
				swap(&keys[i], &keys[j]);
			}
		}
	}
}

//metoda koja vraca pokazivac na sledeci cvor u kom se potencijalno moze naci trazeni kljuc
TreeNode* TreeNode::getNextWait(const long time) const {
	//ako je trazeni kljuc manji od prvog, vraca se pokazivac na krajnji levi cvor
	if (time < keys[0]->getWaitingTime()) {
		return sons[0];
	}
	for (auto i = 0; i < keys.size() - 1; i++) {
		if (keys[i + 1] != nullptr) {
			if (keys[i]->getWaitingTime() < time && keys[i + 1]->getWaitingTime() > time) {
				//ako je trazeni kljuc izmedju dva kljuca, vraca se pokazivac na cvor izmedju njih
				return sons[i + 1];
			}
		}
		else {
			//ako naredni kljuc ne postoji, vraca se pokazivac na cvor desno od prethodnog
			return sons[i + 1];
		}
	}
	return sons[sons.size() - 1];
}

void TreeNode::moveSons(const int disp) {
	int d = disp;

	if (disp == 1 && sons.size() == 2 || disp == 2 && sons.size() == 3) {
		while (disp >= 0) {
			sons[d + 1] = sons[d];
			d--;
		}
	}
	else {
		d = 2;
		while (d > 0) {
			sons[d + 1] = sons[d];
			d--;
		}
	}
}

void TreeNode::setSon(const int pos, TreeNode* node) {
	sons[pos] = node;
}

