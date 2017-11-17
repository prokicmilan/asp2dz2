#pragma once

#include "twothreefour.h"
#include <algorithm>
#include <cmath>

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

void TwoThreeFour::addKey(Process *p) {
	TreeNode *curr = nullptr;
	TreeNode *prev = nullptr;
	
	//ako je stablo prazno, proces se umece u koren
	if (root == nullptr) {
		root = new TreeNode();
		root->addKey(p);
	}
	else {
		curr = root;
		//pronalazenje odgovarajuceg lista u koji treba umetnuti proces
		while (curr != nullptr) {
			prev = curr;
			curr = curr->getNextWait(p->getWaitingTime());
		}
		//broj kljuceva u listu
		auto keys = prev->getKeys();
		const int cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; });
		//ima mesta za dodavanje novog kljuca
		if (cnt < 3) {
			prev->addKey(p);
		}
		//nema mesta, cepanje cvora
		else {
			Process *extra = keys.at(1);
			TreeNode *left = new TreeNode();
			TreeNode *right = new TreeNode();
			bool addLeft = false;

			left->setParent(prev->getParent());
			right->setParent(prev->getParent());
			left->addKey(keys.at(0));
			right->addKey(keys.at(2));
			//novi kljuc se dodaje u onaj cvor cijem je kljucu blizi
			addLeft = abs(keys.at(0)->getWaitingTime() - p->getWaitingTime()) < abs(keys.at(2)->getWaitingTime() - p->getWaitingTime()) ? true : false;
			if (addLeft) {
				left->addKey(p);
			}
			else {
				right->addKey(p);
			}
		}
	}
}



