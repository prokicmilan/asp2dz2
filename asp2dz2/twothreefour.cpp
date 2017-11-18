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

/*void TwoThreeFour::addKey(Process *p) {
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
		//da li ovo moze sa keys.size()?
		//int cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; });
		int cnt = keys.size();
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
			curr = prev->getParent();
			while (curr != nullptr) {
				keys = curr->getKeys();
				cnt = keys.size();
				//cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; });
				//cvor otac ima dovoljno mesta za visak
				if (cnt < 3) {
					curr->addKey(extra);
					int newPos = std::find(keys.begin(), keys.end(), extra) - keys.begin();
					int disp = keys.size() - 1 - newPos;
					curr->moveSons(disp);
					curr->setSon(newPos, left);
					curr->setSon(newPos + 1, right);
					break;
				}
				//cvor otac nema dovoljno mesta, mora da se cepa
				else {

				}
			}
		}
	}
}*/
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
				TreeNode *parent = nullptr;
				Process *extra = keys.at(1);
				left->addKey(keys[0]);
				right->addKey(keys[2]);
				left->setSon(0, sons[0]);
				left->setSon(1, sons[1]);
				right->setSon(0, sons[2]);
				right->setSon(1, sons[3]);
				if (curr != root) {
					auto parentKeys = curr->getParent()->getKeys();
					left->setParent(curr->getParent());
					right->setParent(curr->getParent());
					curr->getParent()->addKey(extra);
					int pos = curr->getParent()->find(extra);
					int disp = std::count_if(keys.begin(), keys.end(), [](Process *ptr) { return ptr != nullptr; }) - pos - 2;
					curr->getParent()->moveSons(disp);
					curr->getParent()->setSon(pos, left);
					curr->getParent()->setSon(pos + 1, right);
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




