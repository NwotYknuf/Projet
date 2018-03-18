#include "TraitementGraphe.h"
#include <string>
#include <iostream>

using namespace std;

void affiche(unsigned ** matrice, unsigned n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)	{
			if (matrice[i][j] < TraitementGraphe::INFINI)
				cout << matrice[i][j] << " , ";
			else
				cout << "I , ";
		}
		cout << endl;
	}
}

int main() {
	/*
#pragma region graph22
	Graphe<DonneesArete, DonneesSommet> graph22;
	DonneesArete a(1,1);

	Sommet<DonneesSommet> * s12 = graph22.creeSommet(DonneesSommet("s12"));
	Sommet<DonneesSommet> * s11 = graph22.creeSommet(DonneesSommet("s11"));
	Sommet<DonneesSommet> * s10 = graph22.creeSommet(DonneesSommet("s10"));
	Sommet<DonneesSommet> * s9 = graph22.creeSommet(DonneesSommet("s9"));
	Sommet<DonneesSommet> * s8 = graph22.creeSommet(DonneesSommet("s8"));
	Sommet<DonneesSommet> * s7 = graph22.creeSommet(DonneesSommet("s7"));
	Sommet<DonneesSommet> * s6 = graph22.creeSommet(DonneesSommet("s6"));
	Sommet<DonneesSommet> * s5 = graph22.creeSommet(DonneesSommet("s5"));
	Sommet<DonneesSommet> * s4 = graph22.creeSommet(DonneesSommet("s4"));
	Sommet<DonneesSommet> * s3 = graph22.creeSommet(DonneesSommet("s3"));
	Sommet<DonneesSommet> * s2 = graph22.creeSommet(DonneesSommet("s2"));
	Sommet<DonneesSommet> * s1 = graph22.creeSommet(DonneesSommet("s1"));

	graph22.creeArete(a, s1, s2);
	graph22.creeArete(a, s2, s1);
	graph22.creeArete(a, s3, s5);
	graph22.creeArete(a, s3, s7);
	graph22.creeArete(a, s4, s6);
	graph22.creeArete(a, s5, s4);
	graph22.creeArete(a, s5, s7);
	graph22.creeArete(a, s6, s5);
	graph22.creeArete(a, s6, s8);
	graph22.creeArete(a, s6, s10);
	graph22.creeArete(a, s7, s9);
	graph22.creeArete(a, s8, s7);
	graph22.creeArete(a, s8, s10);
	graph22.creeArete(a, s9, s8);
	graph22.creeArete(a, s11, s12);
	graph22.creeArete(a, s12, s11);
	
	TraitementGraphe traitement22(&graph22);

	traitement22.NumeroteGraphe();
	traitement22.pccDijkstra(s3, &DonneesArete::getDistance);

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graph22.lSommets);
	unsigned ** matrice = traitement22.matriceDajdacence(&DonneesArete::estPresent);
	unsigned ** floyd = traitement22.FloydWarshall(matrice, n);
	affiche(matrice, n);
	cout << endl << endl;
	affiche(floyd, n);
	system("pause");
#pragma endregion
*/
#pragma region graph Tauro
	Graphe<DonneesArete, DonneesSommet> graphTauro;
	DonneesArete a(1, 1);

	Sommet<DonneesSommet> * s5 = graphTauro.creeSommet(DonneesSommet("s5"));
	Sommet<DonneesSommet> * s4 = graphTauro.creeSommet(DonneesSommet("s4"));
	Sommet<DonneesSommet> * s3 = graphTauro.creeSommet(DonneesSommet("s3"));
	Sommet<DonneesSommet> * s2 = graphTauro.creeSommet(DonneesSommet("s2"));
	Sommet<DonneesSommet> * s1 = graphTauro.creeSommet(DonneesSommet("s1"));

	graphTauro.creeArete(a, s1, s2);
	graphTauro.creeArete(a, s2, s1);
	graphTauro.creeArete(a, s2, s3);
	graphTauro.creeArete(a, s3, s2);
	graphTauro.creeArete(a, s2, s4);
	graphTauro.creeArete(a, s3, s4);
	graphTauro.creeArete(a, s4, s5);

	TraitementGraphe traiteTauro(&graphTauro);

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphTauro.lSommets);
	unsigned ** matriceAdjacence = traiteTauro.matriceAjdacence(&DonneesArete::estPresent);
	unsigned ** floyd = traiteTauro.FloydWarshall(matriceAdjacence, n);
	affiche(matriceAdjacence, n);
	cout << endl;
	affiche(floyd, n);
	cout << endl << traiteTauro.diametre() << endl;

	vector<Maillon<Sommet<DonneesSommet>>*> compConnexe = traiteTauro.composantesConnexes();
	
	for (Maillon<Sommet<DonneesSommet>>* liste : compConnexe) {
		cout << "BONJOUR" << liste << endl;
	}

	system("pause");
#pragma endregion

	return 0;
}
