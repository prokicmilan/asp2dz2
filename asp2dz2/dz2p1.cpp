#include <iostream>
#include <fstream>
#include "process.h"
#include "twothreefour.h"
#include <string>
#include "cfs.h"

using namespace std;

void printMenu() {
	cout << "1. Stvaranje stabla" << endl;
	cout << "2. Unistavanje stabla" << endl;
	cout << "3. Pretrazivanje po trenutnom vremenu cekanja" << endl;
	cout << "4. Pretrazivanje po trenutnom vremenu izvrsavanja" << endl;
	cout << "5. Umetanje procesa u stablo" << endl;
	cout << "6. Brisanje procesa iz stabla" << endl;
	cout << "7. Ispis stabla u 2-3-4 obliku" << endl;
	cout << "8. Ispis stabla u crveno crnom obliku" << endl;
	cout << "9. Ucitavanje stabla iz fajla" << endl;
	cout << "0. Kraj" << endl;
}

void loadFromFile(ifstream &file, TwoThreeFour *tree) {
	if (file.is_open()) {
		string name;
		long maxWait;
		long timeToComplete;

		while (file >> name) {
			file >> maxWait >> timeToComplete;
			tree->addKey(new Process(name, timeToComplete, maxWait));
		}
	}
	else {
		cerr << "Fajl nije otvoren." << endl;
	}
}

int main(void) {
	TwoThreeFour *tree = nullptr;
	Process *p = nullptr;
	bool cont = true;
	int choice;
	long time;
	string name;
	long maxWait;
	long timeToComplete;
	ifstream file;
	const string e = "Stablo ne postoji.";
	
	while (cont) {
		printMenu();
		cin >> choice;
		try {
			switch (choice) {
			case 1:
				if (tree == nullptr) {
					tree = new TwoThreeFour();
				}
				else {
					throw e;
				}
				break;
			case 2:
				if (tree != nullptr) {
					delete tree;
					tree = nullptr;
				}
				else {
					throw e;
				}
				break;
			case 3:
				if (tree != nullptr) {
					cout << "Unesite zeljeno vreme cekanja: ";
					cin >> time;
					p = const_cast<Process*>(tree->findKeyWait(time));
					if (p != nullptr) {
						cout << "Kljuc je pronadjen: " << *p << endl;
					}
					else {
						cout << "Kljuc nije pronadjen." << endl;
					}
				}
				else {
					throw e;
				}
				break;
			case 4:
				if (tree != nullptr) {
					cout << "Unesite zeljeno vreme cekanja: ";
					cin >> time;
					p = const_cast<Process*>(tree->findKeyExec(time));
					if (p != nullptr) {
						cout << "Kljuc je pronadjen: " << *p << endl;
					}
					else {
						cout << "Kljuc nije pronadjen." << endl;
					}
				}
				else {
					throw e;
				}
				break;
			case 5:
				if (tree != nullptr) {
					cout << "Unesite ime procesa, maksimalno vreme cekanja i vreme potrebno da se proces izvrsi: ";
					cin >> name >> maxWait >> timeToComplete;
					p = new Process(name, timeToComplete, maxWait);
					tree->addKey(p);
				}
				else {
					throw e;
				}
				break;
			case 6:
				if (tree != nullptr) {
					cout << "Unesite vreme cekanja: ";
					cin >> time;
					p = const_cast<Process*>(tree->findKeyWait(time));
					if (p != nullptr) {
						tree->delKey(p);
					}
					else {
						cout << "Trazeni kljuc ne postoji u stablu." << endl;
					}
				}
				else {
					throw e;
				}
				break;
			case 7:
				if (tree != nullptr) {
					cout << *tree << endl;
				}
				else {
					throw e;
				}
				break;
			case 8:
				if (tree != nullptr) {
					tree->printRedBlack();
				}
				else {
					throw e;
				}
				break;
			case 9:
				if (tree != nullptr) {
					cout << "Unesite ime fajla: ";
					cin >> name;
					file.open(name);
					loadFromFile(file, tree);
				}
				break;
			case 0:
				cont = false;
				break;
			default:
				cout << "Nepostojeca opcija" << endl;
				break;
			}
		} catch(string ex) {
			cerr << ex << endl;
		}
	}
	delete tree;
	return 0;
}