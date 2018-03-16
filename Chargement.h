#pragma once
#include "Graphe.h"
#include "DonneesArete.h"
#include "DonneesSommet.h"
#include <vector>

class Chargement {
public:
	static void split(string str, string splitBy, vector<string>& tokens);
	static Graphe<DonneesArete, DonneesSommet> charger(string chemin);
};