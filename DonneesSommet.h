#pragma once
#include <string>
#include <iostream>

using namespace std;

class DonneesSommet{
public:
	string nom;
	bool marque;
	unsigned int numerotationPrefixe = 0;
	unsigned int numerotationSuffixe = 0;

	DonneesSommet() { nom = ""; marque = false; }
	DonneesSommet(const string& _nom) { nom = _nom; marque = false; }
	~DonneesSommet() { };

	friend ostream& operator <<(ostream & os, const DonneesSommet & s);
	
};

