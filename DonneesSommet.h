#pragma once
#include <string>
#include <iostream>
#include "Sommet.h"

using namespace std;

class DonneesSommet{
public:
	string nom = "";
	int x;
	int y;
	unsigned int numerotation = 0;
	unsigned int numerotationPrefixe = 0;
	unsigned int numerotationSuffixe = 0;
<<<<<<< HEAD
	unsigned int lambda = 4294967295;
	
=======

	//Dijkstra
	static const unsigned LIBRE;
	static const unsigned OUVERT;
	static const unsigned FERME;

	Sommet<DonneesSommet> * pere;
	unsigned cout;
	unsigned etat;

>>>>>>> ca87077731c422e73f14c60b324a766bcbeb96f1
	DonneesSommet() { }
	DonneesSommet(const string& _nom, int _x = 0, int _y = 0) :nom(_nom), x(_x), y(_y) {}
	~DonneesSommet() { };

	friend ostream& operator <<(ostream & os, const DonneesSommet & s);
	
};

