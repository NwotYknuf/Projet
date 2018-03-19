#pragma once
#include <iostream>

using namespace std;

class DonneesArete{
public:
	string name = "arete";
	unsigned distance;
	unsigned duree;

	DonneesArete() { distance = 0; duree = 0; }
	DonneesArete(unsigned _distance, unsigned _duree):distance(_distance), duree(_duree){}
	DonneesArete(string _name, unsigned _distance, unsigned _duree) :distance(_distance), duree(_duree), name(_name) {}
	~DonneesArete() { }

	unsigned getDistance() { return distance; }
	unsigned getDuree() { return duree; }
	unsigned estPresent() { return 1; }

	friend ostream& operator <<(ostream & os, const DonneesArete & a);
};

