#include "TraitementGraphe.h"

/*
* traitementPrefixe et traitementSuffixe doivent être des méthodes membres de TraitementGraphe.
* elles doivent respecter la signature : void maFonction(Sommet<DonneesSommet>*)
*/
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

/*
* traitementPrefixe et traitementSuffixe doivent être des méthodes membres de TraitementGraphe.
* elles doivent respecter la signature : void maFonction(Sommet<DonneesSommet>*)
*/
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

	parcoursDFS(	&TraitementGraphe::ordrePefixeInverse, &TraitementGraphe::ordreSuffixeInverse);

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

void TraitementGraphe::libererToutSommet() {

	Maillon<Sommet<DonneesSommet>> * temp = graphe->lSommets;

	while (temp != NULL) {
		temp->valeur->info.etat = DonneesSommet::LIBRE;
		temp->valeur->info.pere = NULL;
		temp->valeur->info.cout = 1000000;
		temp = temp->suivant;
	}
}

void TraitementGraphe::pccDijkstra(Sommet<DonneesSommet> * depart) {

		libererToutSommet();

		Maillon<Sommet<DonneesSommet>> *ouverts = NULL;

		depart->info.cout = 0;
		depart->info.etat = DonneesSommet::OUVERT;
		ouverts = new Maillon<Sommet<DonneesSommet>>(depart, ouverts);
		
		while (ouverts != NULL) {
			Sommet<DonneesSommet> * s = Maillon<Sommet<DonneesSommet>>::depiler(ouverts);
			s->info.etat = DonneesSommet::FERME;

			Maillon<Sommet<DonneesSommet>> * voisins = graphe->sommetsAdjacents(s);
			Maillon<Sommet<DonneesSommet>> * temp2 = voisins;

			while (temp2 != NULL) {
				Sommet<DonneesSommet> * v = temp2->valeur;

				if (v->info.etat == DonneesSommet::LIBRE) {

					v->info.pere = s;
					unsigned coutSversV = graphe->trouveAreteParSommets(s, v)->info.distance;
					v->info.cout = s->info.cout + coutSversV;
					v->info.etat = DonneesSommet::OUVERT;
					ouverts = new Maillon<Sommet<DonneesSommet>>(v, ouverts);
				}
				else {
					unsigned coutSversV = graphe->trouveAreteParSommets(s, v)->info.distance;
					if (v->info.etat == DonneesSommet::OUVERT &&
						s->info.cout < coutSversV + v->info.cout) {

						v->info.pere = s;
						v->info.cout = s->info.cout + coutSversV;
						Maillon<Sommet<DonneesSommet>>::retire(v, ouverts);
						ouverts = new Maillon<Sommet<DonneesSommet>>(v, ouverts);
					}
				}
				temp2 = temp2->suivant;
			}

			Maillon<Sommet<DonneesSommet>>::effacePointeurs(voisins);
		}

}