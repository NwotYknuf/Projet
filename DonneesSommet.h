#pragma once
#include <string>
#include <iostream>
#include "Sommet.h"

using namespace std;

class DonneesSommet{
public:
	string nom = "";
	unsigned int numerotation = 0;
	unsigned int numerotationPrefixe = 0;
	unsigned int numerotationSuffixe = 0;

	//Dijkstra
	static const unsigned LIBRE;
	static const unsigned OUVERT;
	static const unsigned FERME;

	Sommet<DonneesSommet> * pere;
	unsigned cout;
	unsigned etat;

	DonneesSommet() { }
	DonneesSommet(const string& _nom) { nom = _nom; }
	~DonneesSommet() { };

	friend ostream& operator <<(ostream & os, const DonneesSommet & s);
	
};

