#include "TraitementGraphe.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

	Graphe<DonneesArete, DonneesSommet> graph;
	
	DonneesSommet d;
	DonneesArete a;

	Sommet<DonneesSommet> * s12 = graph.creeSommet(DonneesSommet("s12"));
	Sommet<DonneesSommet> * s11 = graph.creeSommet(DonneesSommet("s11"));
	Sommet<DonneesSommet> * s10 = graph.creeSommet(DonneesSommet("s10"));
	Sommet<DonneesSommet> * s9 = graph.creeSommet(DonneesSommet("s9"));
	Sommet<DonneesSommet> * s8 = graph.creeSommet(DonneesSommet("s8"));
	Sommet<DonneesSommet> * s7 = graph.creeSommet(DonneesSommet("s7"));
	Sommet<DonneesSommet> * s6 = graph.creeSommet(DonneesSommet("s6"));
	Sommet<DonneesSommet> * s5 = graph.creeSommet(DonneesSommet("s5"));
	Sommet<DonneesSommet> * s4 = graph.creeSommet(DonneesSommet("s4"));
	Sommet<DonneesSommet> * s3 = graph.creeSommet(DonneesSommet("s3"));
	Sommet<DonneesSommet> * s2 = graph.creeSommet(DonneesSommet("s2"));
	Sommet<DonneesSommet> * s1 = graph.creeSommet(DonneesSommet("s1"));

	graph.creeArete(a, s1, s2);
	graph.creeArete(a, s2, s1);
	graph.creeArete(a, s3, s5);
	graph.creeArete(a, s3, s7);
	graph.creeArete(a, s4, s6);
	graph.creeArete(a, s5, s4);
	graph.creeArete(a, s5, s7);
	graph.creeArete(a, s6, s5);
	graph.creeArete(a, s6, s8);
	graph.creeArete(a, s6, s10);
	graph.creeArete(a, s7, s9);
	graph.creeArete(a, s8, s7);
	graph.creeArete(a, s8, s10);
	graph.creeArete(a, s9, s8);
	graph.creeArete(a, s11, s12);
	graph.creeArete(a, s12, s11);

	TraitementGraphe traitement(&graph);

	traitement.NumeroteGraphe();

	cout << graph << endl;
	//heyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
	system("pause");

	return 0;
}
