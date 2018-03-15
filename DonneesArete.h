#pragma once
#include <iostream>

using namespace std;

class DonneesArete{
public:
	unsigned distance;
	unsigned duree;

	DonneesArete() { distance = 0; duree = 0; }
	~DonneesArete() { };

	friend ostream& operator <<(ostream & os, const DonneesArete & a);
};

