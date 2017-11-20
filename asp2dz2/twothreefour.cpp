#pragma once

#include "twothreefour.h"
#include <vector>

void TwoThreeFour::borrowRight(TreeNode *prev, TreeNode *curr, TreeNode *rightBrother) {
	int pos;
	auto parentKeys = prev->getKeys();
	auto brotherKeys = rightBrother->getKeys();

	for (pos = parentKeys.size() - 1; pos > 0; pos--) {
		if (parentKeys[pos] != nullptr) {
			break;
		}
	}
	curr->addKey(parentKeys[pos]);
	prev->removeKey(pos);
	prev->addKey(brotherKeys[0]);
	rightBrother->removeKey(0);
	//TODO: prevezi pokazivace
	curr->setSon(2, rightBrother->getSons()[0]);
	rightBrother->removeSon(0);
}

void TwoThreeFour::borrowLeft(TreeNode* prev, TreeNode* curr, TreeNode* leftBrother) {
	int pos;
	auto parentKeys = prev->getKeys();
	auto brotherKeys = leftBrother->getKeys();

	curr->addKey(parentKeys[0]);
	prev->removeKey(0);
	for (pos = brotherKeys.size() - 1; pos > 0; pos--) {
		if (brotherKeys[pos] != nullptr) {
			break;
		}
	}
	prev->addKey(brotherKeys[pos]);
	leftBrother->removeKey(pos);
	//TODO: prevezi pokazivace
	//ovde moze da se pojavi problem, proveri funkciju za pomeranje
	curr->moveSons(1);
	curr->setSon(0, leftBrother->getSons()[pos + 1]);
	leftBrother->removeSon(pos + 1);
}

void TwoThreeFour::mergeRight(TreeNode *prev, TreeNode *curr, TreeNode *rightBrother) {
	int pos;
	auto parentKeys = prev->getKeys();
	auto brotherKeys = rightBrother->getKeys();

	curr->addKey(brotherKeys[0]);
	rightBrother->removeKey(0);
	for (pos = parentKeys.size() - 1; pos > 0; pos--) {
		if (parentKeys[pos] != nullptr && parentKeys[pos]->getWaitingTime() <= brotherKeys[0]->getWaitingTime()) {
			break;
		}
	}
	curr->addKey(parentKeys[pos]);
	prev->removeKey(pos);
	//TODO: prevezi pokazivace i obrisi desnog brata
	curr->setSon(2, rightBrother->getSons()[0]);
	curr->setSon(3, rightBrother->getSons()[1]);
	prev->removeSon(pos + 1);
	delete rightBrother;
}

void TwoThreeFour::mergeLeft(TreeNode *prev, TreeNode *curr, TreeNode *leftBrother) {
	int pos;
	auto parentKeys = prev->getKeys();
	auto brotherKeys = leftBrother->getKeys();

	curr->addKey(brotherKeys[0]);
	leftBrother->removeKey(0);
	for (pos = 0; pos < parentKeys.size(); pos++) {
		if (parentKeys[pos]->getWaitingTime() >= brotherKeys[0]->getWaitingTime()) {
			break;
		}
	}
	curr->addKey(parentKeys[pos]);
	prev->removeKey(pos);
	//TODO: prevezi pokazivace i obrisi levog brata
	//ovde moze da se pojavi problem, proveri funkciju za pomeranje
	curr->moveSons(1);
	curr->moveSons(1);
	curr->setSon(0, leftBrother->getSons()[0]);
	curr->setSon(1, leftBrother->getSons()[1]);
	prev->removeSon(pos);
	delete leftBrother;
}

void TwoThreeFour::fixupNode(TreeNode *prev, TreeNode *curr) {
	TreeNode *rightBrother = curr->getBrother(prev, false);
	TreeNode *leftBrother = curr->getBrother(prev, true);
	auto parentKeys = prev->getKeys();
	bool right = false;
	bool left = false;

	//da li desni brat postoji i ima za pozajmicu
	if (rightBrother != nullptr) {
		auto brotherKeys = rightBrother->getKeys();
		int brotherCnt = std::count_if(brotherKeys.begin(), brotherKeys.end(), [](Process *ptr) { return ptr != nullptr; });
		if (brotherCnt > 1) {
			right = true;
		}
	}
	//da li levi brat postoji i ima za pozajmicu
	if (leftBrother != nullptr) {
		auto brotherKeys = leftBrother->getKeys();
		int brotherCnt = std::count_if(brotherKeys.begin(), brotherKeys.end(), [](Process *ptr) { return ptr != nullptr; });
		if (brotherCnt > 1) {
			left = true;
		}
	}
	//desni postoji i ima za pozajmicu
	if (right) {
		borrowRight(prev, curr, rightBrother);
	}
	//desni ne postoji ili nema za pozajmicu
	else {
		//levi postoji i ima za pozajmicu
		if (left) {
			borrowLeft(prev, curr, leftBrother);
		}
		//ni levi ni desni nemaju za pozajmicu
		else {
			//desni postoji, spajaju se trenutni, desni i kljuc iz oca
			if (rightBrother != nullptr) {
				mergeRight(prev, curr, rightBrother);
			}
			//levi postoji, spajaju se trenutni, levi i kljuc iz oca
			else {
				mergeLeft(prev, curr, leftBrother);
			}
			//posto je jedan cvor uzet od oca, proveriti da li je otac koren
			//ako jeste, proveriti da li je ovom pozajmicom potpuno ispraznjen
			//ako je ispraznjen, brise se i novi koren postaje tekuci cvor
			if (prev == root) {
				if (std::count_if(parentKeys.begin(), parentKeys.end(), [](Process *ptr) { return ptr != nullptr; }) - 1 == 0) {
					delete root;
					root = curr;
				}
			}
		}
	}
}

TwoThreeFour::TwoThreeFour() {
	root = nullptr;
}

TwoThreeFour::~TwoThreeFour() {
	TreeNode *curr = nullptr;
	std::vector<TreeNode*> next;

	if (root != nullptr) {
		next.insert(next.begin(), root);
		while (!next.empty()) {
			curr = next.back();
			next.pop_back();
			auto sons = curr->getSons();
			for (auto son : sons) {
				if (son != nullptr) {
					next.insert(next.begin(), son);
				}
			}
			delete curr;
		}
		root = nullptr;
	}
}

const Process* TwoThreeFour::findKeyWait(const long time) const {
	TreeNode *curr = nullptr;

	curr = root;
	while (curr != nullptr && curr->findKeyWait(time) == nullptr) {
		curr = curr->getNextWait(time);
	}
	if (curr != nullptr) {
		return curr->findKeyWait(time);
	}
	else {
		return nullptr;
	}
}

const Process* TwoThreeFour::findKeyExec(const long time) const {
	TreeNode *curr = nullptr;
	std::vector<TreeNode*> next;

	if (root != nullptr) {
		next.insert(next.begin(), root);
		while (!next.empty()) {
			curr = next.front();
			const Process *proc = curr->findKeyExec(time);
			if (proc != nullptr) {
				return proc;
			}
			else {
				auto sons = curr->getSons();
				next.erase(next.begin());
				for (auto son : sons) {
					if (son != nullptr) {
						next.insert(next.begin(), son);
					}
				}
			}
		}
	}
	return nullptr;
}

void TwoThreeFour::addKey(Process* p) {
	TreeNode *curr = nullptr;
	TreeNode *prevDel = nullptr;
	TreeNode *prev = nullptr;

	if (root == nullptr) {
		root = new TreeNode();
		root->addKey(p);
	}
	else {
		curr = root;
		while (curr != nullptr) {
			auto keys = curr->getKeys();
			auto sons = curr->getSons();
			int cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; });
			if (cnt == 3) {
				TreeNode *left = new TreeNode();
				TreeNode *right = new TreeNode();
				Process *extra = keys[1];
				left->addKey(keys[0]);
				right->addKey(keys[2]);
				curr->emptyNode();
				left->setSon(0, sons[0]);
				left->setSon(1, sons[1]);
				right->setSon(0, sons[2]);
				right->setSon(1, sons[3]);
				if (curr != root) {
					auto parentKeys = prev->getKeys();
					prev->addKey(extra);
					int pos = prev->find(extra);
					int disp = std::count_if(parentKeys.begin(), parentKeys.end(), [](Process *ptr) { return ptr != nullptr; }) - pos - 1;
					prev->moveSons(disp);
					prev->setSon(pos, left);
					prev->setSon(pos + 1, right);
					bool addLeft = abs(keys[0]->getWaitingTime() - p->getWaitingTime()) < abs(keys[2]->getWaitingTime() - p->getWaitingTime()) ? true : false;
					prevDel = curr;
					curr = addLeft ? left : right;
				}
				else {
					TreeNode *newRoot = new TreeNode();
					newRoot->addKey(extra);
					newRoot->setSon(0, left);
					newRoot->setSon(1, right);
					root = newRoot;
					prevDel = curr;
					curr = newRoot;
				}
			}
			prev = curr;
			curr = curr->getNextWait(p->getWaitingTime());
			if (prevDel != nullptr) {
				delete prevDel;
				prevDel = nullptr;
			}
		}
		prev->addKey(p);
	}
}

void TwoThreeFour::delKey(Process* p) {
	TreeNode *curr = nullptr;
	TreeNode *prev = nullptr;

	if (root != nullptr) {
		curr = root;
		while (curr != nullptr && curr->find(p) == -1) {
			auto keys = curr->getKeys();
			if (curr != root) {
				int cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) {return ptr != nullptr; });
				if (cnt == 1) {
					fixupNode(prev, curr);
				}
			}
			prev = curr;
			curr = curr->getNextWait(p->getWaitingTime());
		}
		if (curr != nullptr) {
			//ako je list
			if (curr->getSons()[0] == nullptr) {
				auto keys = curr->getKeys();
				int pos = curr->find(p);
				/*for (pos = 0; pos < keys.size(); pos++) {
					if (keys[pos] == p) {
						break;
					}
				}*/
				curr->deleteKey(pos);
				p = nullptr;
				if (std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; }) - 1 == 0) {
					fixupNode(prev, curr);
				}
			}
			//nije list, spustamo se do inorder sledbenika i spajamo cvorove
			else {
				TreeNode *found = curr;
				TreeNode *parent = nullptr;
				int pos = curr->find(p);
				auto keys = curr->getKeys();

				prev = curr;
				curr = curr->getSons()[pos + 1];
				while (curr != nullptr) {
					auto currKeys = curr->getKeys();
					int cnt = std::count_if(currKeys.begin(), currKeys.end(), [](Process *ptr) {return ptr != nullptr; });
					if (cnt == 1) {
						fixupNode(prev, curr);
					}
					if (prev == found && found->find(p) == -1) {
						found = curr;
						pos = found->find(p);
						prev = curr;
						curr = curr->getSons()[pos + 1];
						continue;
					}
					parent = prev;
					prev = curr;
					curr = curr->getSons()[0];
				}
				curr = prev;
				auto leafKeys = curr->getKeys();
				found->deleteKey(pos);
				p = nullptr;
				found->addKey(leafKeys[0]);
				curr->removeKey(0);
				int cnt = std::count_if(leafKeys.begin(), leafKeys.end(), [](Process *ptr) { return ptr != nullptr; });
				//ako je uklonjen poslednji kljuc
				if (cnt == 0) {
					fixupNode(curr, parent);
				}
			}
		}
	}
}

std::ostream& operator<<(std::ostream &os, const TwoThreeFour &t) {
	int level = 1;
	int cnt = 0;
	int cntNext = 0;
	std::vector<TreeNode*> next;
	TreeNode *curr = nullptr;

	if (t.root != nullptr) {
		next.insert(next.begin(), t.root);
		cntNext = 1;
		while (!next.empty()) {
			cnt = cntNext;
			cntNext = 0;
			os << "Nivo: " << level++ << ":" << std::endl;
			for (int i = 0; i < cnt; i++) {
				curr = next.back();
				next.erase(next.end() - 1);
				auto keys = curr->getKeys();
				for (auto key : keys) {
					if (key != nullptr) {
						os << *key << std::endl;
					}
				}
				auto sons = curr->getSons();
				for (auto son : sons) {
					if (son != nullptr) {
						next.insert(next.begin(), son);
						cntNext++;
					}
				}
			}
		}
	}
	return os;
}


