#pragma once
#include "Graphe.h"
#include "DonneesArete.h"
#include "DonneesSommet.h"
#include <vector>

class Chargement {
public:
	static void split(string str, string splitBy, vector<string>& tokens);
	static Graphe<DonneesArete, DonneesSommet> * charger(const string& chemin);
	static int nbreLignes(const string& chemin);
	static int trouverLigneCommencantParS(const string& s, const string& chemin);
	static void erase(vector<string>& v, string str);
	static void chargerSommetGPR(const string& chemin, Graphe<DonneesArete, DonneesSommet> * graph);
	static void chargerAreteGPR(const string& chemin, Graphe<DonneesArete, DonneesSommet> * graph);
	static void chargerSourceGPR(const string& chemin, Maillon<Sommet<DonneesSommet>>* lSommets);
};