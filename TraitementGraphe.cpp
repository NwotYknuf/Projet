#include "TraitementGraphe.h"

const unsigned TraitementGraphe::INFINIT = 1000000;

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
		if (!temp->valeur->marque) 
			parcoursComposante(temp->valeur, traitementPrefixe, traitementSuffixe);
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
		temp->valeur->info.cout = INFINIT;
		temp = temp->suivant;
	}
}

void TraitementGraphe::pccDijkstra(Sommet<DonneesSommet> * depart, unsigned (DonneesArete::*critere)(void)) {

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
					unsigned coutSversV = (graphe->trouveAreteParSommets(s, v)->info.*critere)();
					v->info.cout = s->info.cout + coutSversV;
					v->info.etat = DonneesSommet::OUVERT;
					ouverts = new Maillon<Sommet<DonneesSommet>>(v, ouverts);
				}
				else {

					unsigned coutSversV = (graphe->trouveAreteParSommets(s, v)->info.*critere)();

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

unsigned ** TraitementGraphe::matriceDajdacence(unsigned(DonneesArete::*critere)(void)){

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);

	unsigned** matrice = new unsigned*[n];

	for (int i = 0; i < n; i++)
		matrice[i] = new unsigned[n];

	Maillon<Sommet<DonneesSommet>> * temp = graphe->lSommets;
	Maillon<Sommet<DonneesSommet>> * temp2 = graphe->lSommets;

	int i =0,j = 0;

	while (temp != NULL) {
		while (temp2!=NULL){

			Arete<DonneesArete, DonneesSommet> * s = graphe->trouveAreteParSommets(temp->valeur, temp2->valeur);

			if (s != NULL)
				matrice[i][j] = (s->info.*critere)();
			else
				matrice[i][j] = 0;

			temp2 = temp2->suivant;
			j++;
		}

		temp2 = graphe->lSommets;
		temp = temp->suivant;
		i++;
		j = 0;
	}
	return matrice;
}

unsigned ** TraitementGraphe::FloydWarshall(unsigned ** matriceAdjacence, unsigned n){
	
	unsigned** res = new unsigned*[n];
	for (int i = 0; i < n; i++)
		res[i] = new unsigned[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				res[i][j] = 0;
			else {
				if (matriceAdjacence[i][j] != 0)
					res[i][j] = matriceAdjacence[i][j];
				else
					res[i][j] = INFINIT;
			}
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (res[i][j] > res[i][k] + res[k][j])
					res[i][j] = res[i][k] + res[k][j];
			}
		}
	}

	return res;
}

unsigned TraitementGraphe::diametre() {
	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);

	unsigned ** matrice = matriceDajdacence(&DonneesArete::estPresent);

	unsigned ** matricePresence = FloydWarshall(matrice, n);

	unsigned max = matricePresence[0][0];

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (matricePresence[i][j] > max && matricePresence[i][j] < INFINIT)
				max = matricePresence[i][j];
		}
	}

	return max;
}