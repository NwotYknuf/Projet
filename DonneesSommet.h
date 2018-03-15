#pragma once
#include <string>
#include <iostream>

using namespace std;

class DonneesSommet{
public:
	string nom = "";
	unsigned int numerotation = 0;
	unsigned int numerotationPrefixe = 0;
	unsigned int numerotationSuffixe = 0;
	unsigned int lambda = 4294967295;



	DonneesSommet() { }
	DonneesSommet(const string& _nom) { nom = _nom; }
	~DonneesSommet() { };

	friend ostream& operator <<(ostream & os, const DonneesSommet & s);
	
};

