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
	static Maillon<Sommet<DonneesSommet>>* chargerSommetGPR(const string& chemin);
	static Maillon<Arete<DonneesArete, DonneesSommet>>* chargerAreteGPR(const string& chemin, Maillon<Sommet<DonneesSommet>>* lSommets);
	static void chargerSourceOuPuitGPR(const string& chemin, Maillon<Sommet<DonneesSommet>>* lSommets, const string& sourceOuPuit);
};