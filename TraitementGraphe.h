#pragma once
#include <vector>
#include "Graphe.h"
#include "DonneesArete.h"
#include "DonneesSommet.h"

using namespace std;

class TraitementGraphe{

private:
	Graphe<DonneesArete, DonneesSommet>* graphe;

	Maillon<Sommet<DonneesSommet>> * prefixeInverse = NULL;
	Maillon<Sommet<DonneesSommet>> * suffixeInverse = NULL;

public:

	static const unsigned INFINI;
		
	TraitementGraphe() = delete;
	TraitementGraphe(const TraitementGraphe&) = delete;
	TraitementGraphe(Graphe<DonneesArete, DonneesSommet>* _graphe) : graphe(_graphe) { };
	~TraitementGraphe() { }
	
	template<class Traitement>
	void parcoursComposante(Sommet<DonneesSommet> * sommet, Traitement traitementPrefixe, Traitement traitementSuffixe);

	template<class Traitement>
	void parcoursDFS(Traitement traitementPrefixe, Traitement traitementSuffixe);

	void affiche(Sommet<DonneesSommet> * sommet);

	void neFaisRien(Sommet<DonneesSommet> * sommet) { }

	void ordrePrefixeInverse(Sommet<DonneesSommet> * sommet);

	void ordreSuffixeInverse(Sommet<DonneesSommet> * sommet);

	void NumeroteGraphe();

	void libererToutSommet();

	void pccDijkstra(Sommet<DonneesSommet> * depart, unsigned(DonneesArete::*critere)(void) );

	void pccFord(Sommet<DonneesSommet> * depart, unsigned(DonneesArete::*critere)(void));

	unsigned** matriceAjdacence(unsigned(DonneesArete::*critere)(void));

	vector<Maillon<Sommet<DonneesSommet>>*> composantesFortementConnexes();

	unsigned** FloydWarshall(unsigned ** matriceAdjacence, unsigned n);

	unsigned diametre();

	bool estSansCycle();

	static Sommet<DonneesSommet>* trouverSommetParNom(Maillon<Sommet<DonneesSommet>>* & lSommet, const string& nom);
};
