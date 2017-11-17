#pragma once

#include "twothreefour.h"

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

void TwoThreeFour::addKey(Process *p) {
	TreeNode *curr = nullptr;
	TreeNode *prev = nullptr;
	
	if (root == nullptr) {
		root = new TreeNode();
		root->addKey(p);
	}
	else {
		curr = root;
		while (curr != nullptr) {
			
		}
	}
}



