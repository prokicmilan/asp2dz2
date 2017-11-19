#pragma once

#include "twothreefour.h"
#include <vector>

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
				Process *extra = new Process(*keys[1]);
				left->addKey(new Process(*keys[0]));
				right->addKey(new Process(*keys[2]));
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
		while (curr != nullptr && curr->find(p) != -1) {
			auto keys = curr->getKeys();
			auto sons = curr->getSons();
			if (curr != root) {
				int cnt = std::count_if(keys.begin(), keys.end(), [](Process *ptr) {return ptr != nullptr; });
				if (cnt == 1) {
					TreeNode *rightBrother = curr->getBrother(prev, false);
					TreeNode *leftBrother = curr->getBrother(prev, true);
					bool right = false;
					bool left = false;
					bool borrowed = false;
					if (rightBrother != nullptr) {
						auto brotherKeys = rightBrother->getKeys();
						int brotherCnt = std::count_if(brotherKeys.begin(), brotherKeys.end(), [](Process *ptr) { return ptr != nullptr; });
						if (brotherCnt > 1) {
							right = true;
						}
					}
					if (leftBrother != nullptr) {
						auto brotherKeys = leftBrother->getKeys();
						int brotherCnt = std::count_if(brotherKeys.begin(), brotherKeys.end(), [](Process *ptr) { return ptr != nullptr; });
						if (brotherCnt > 1) {
							left = true;
						}
					}
					if (right) {
						auto parentKeys = prev->getKeys();
						int pos;
						for (pos = parentKeys.size() - 1; pos > 0; pos--) {
							if (parentKeys[pos] != nullptr) {
								break;
							}
						}
						curr->addKey(new Process(*parentKeys[pos]));
						prev->removeKey(pos);
						prev->addKey(new Process(*const_cast<Process*>(rightBrother->getKeys()[0])));
						rightBrother->removeKey(0);
						//prevezi pokazivace
					}
					else {
						if (left) {
							curr->addKey(new Process(*const_cast<Process*>(prev->getKeys()[0])));
							prev->removeKey(0);
							auto brotherKeys = leftBrother->getKeys();
							int pos;
							for (pos = brotherKeys.size() - 1; pos > 0; pos--) {
								if (brotherKeys[pos] != nullptr) {
									break;
								}
							}
							prev->addKey(new Process(*brotherKeys[pos]));
							leftBrother->removeKey(pos);
							//prevezi pokazivace
						}
					}
				}
			}
			prev = curr;
			curr = curr->getNextWait(p->getWaitingTime());
		}
		if (curr == nullptr) {
			return;
		}
		else {
			
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


