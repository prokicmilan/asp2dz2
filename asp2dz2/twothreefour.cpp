#pragma once

#include "twothreefour.h"
#include <algorithm>

TwoThreeFour::TwoThreeFour() {
	root = nullptr;
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

//ovo ne radi ovako, kljucevi su sortirani iskljucivo po vremenu cekanja,
//da bi se vrsila pretraga prema vremenu izvrsavanja, mora da se prodje kroz celo stablo
const Process* TwoThreeFour::findKeyExec(const long time) const {
	TreeNode *curr = nullptr;

	curr = root;
	while (curr != nullptr && curr->findKeyExec(time) == nullptr) {
		curr = curr->getNextExec(time);
	}
	if (curr != nullptr) {
		return curr->findKeyExec(time);
	}
	else {
		return nullptr;
	}
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
				left->setSon(0, sons[0]);
				left->setSon(1, sons[1]);
				right->setSon(0, sons[2]);
				right->setSon(1, sons[3]);
				if (curr != root) {
					auto parentKeys = prev->getKeys();
					left->setParent(prev);
					right->setParent(prev);
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
					left->setParent(newRoot);
					right->setParent(newRoot);
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




