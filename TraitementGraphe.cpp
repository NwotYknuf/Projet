#include "TraitementGraphe.h"

template<class Traitement>
void inline TraitementGraphe::parcoursComposante(Sommet<DonneesSommet>* sommet, Traitement traitementPrefixe, Traitement traitementSuffixe) {
	sommet->marque = true;

	(this->*traitementPrefixe)(sommet);

	Maillon<Sommet<DonneesSommet>> * voisins = graphe->sommetsAdjacents(sommet);
	Maillon<Sommet<DonneesSommet>> * temp = voisins;

	while (temp != NULL) {
		if (!temp->valeur->marque)
			parcoursComposante(temp->valeur, traitementPrefixe, traitementSuffixe);
		temp = temp->suivant;
	}

	(this->*traitementSuffixe)(sommet);
	
	Maillon<Sommet<DonneesSommet>>::effacePointeurs(voisins);
}

template<class Traitement>
void inline TraitementGraphe::parcoursDFS(Traitement traitementPrefixe, Traitement traitementSuffixe) {
	Maillon<Sommet<DonneesSommet>>* temp = graphe->lSommets;
	while (temp != NULL) {
		if (!temp->valeur->marque) parcoursComposante(temp->valeur, traitementPrefixe, traitementSuffixe);
		temp = temp->suivant;
	}
}

void TraitementGraphe::affiche(Sommet<DonneesSommet>* sommet){
	cout << *sommet;
}

void TraitementGraphe::ordrePefixeInverse(Sommet<DonneesSommet>* sommet){
	prefixeInverse = new Maillon<Sommet<DonneesSommet>>(sommet, prefixeInverse);
}

void TraitementGraphe::ordreSuffixeInverse(Sommet<DonneesSommet>* sommet){
	suffixeInverse = new Maillon<Sommet<DonneesSommet>>(sommet, suffixeInverse);
}

void TraitementGraphe::NumeroteGraphe(){
	Maillon<Sommet<DonneesSommet>> * temp;
	Maillon<Sommet<DonneesSommet>> * temp2;
	int num = 0;

	temp = graphe->lSommets;

	while (temp != NULL) {
		temp->valeur->info.numerotation = ++num;
		temp = temp->suivant;
	}

	parcoursDFS(&TraitementGraphe::ordrePefixeInverse, &TraitementGraphe::ordreSuffixeInverse);

	int n = Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);
	temp = prefixeInverse;
	temp2 = suffixeInverse;

	while (temp != NULL) {
		temp->valeur->info.numerotationPrefixe = n;
		temp2->valeur->info.numerotationSuffixe = n;
		n--;
		temp = temp->suivant;
		temp2 = temp2->suivant;
	}
}
