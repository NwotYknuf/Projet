#include "TraitementGraphe.h"

const unsigned TraitementGraphe::INFINI = 4000000;

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
	libererToutSommet();
	Maillon<Sommet<DonneesSommet>>* temp = graphe->lSommets;
	while (temp != NULL) {
		if (!temp->valeur->marque) 
			parcoursComposante(temp->valeur, traitementPrefixe, traitementSuffixe);
		temp = temp->suivant;
	}
}

template<class Type>
bool TraitementGraphe::valeurEstDansVector(vector<Type> conteneur, const Type& valeur)
{
	auto iterator = find(conteneur.begin(), conteneur.end(), valeur);
	return (iterator != conteneur.end());
}

void TraitementGraphe::affiche(Sommet<DonneesSommet>* sommet){
	cout << *sommet;
}

void TraitementGraphe::ordrePrefixeInverse(Sommet<DonneesSommet>* sommet){
	prefixeInverse = new Maillon<Sommet<DonneesSommet>>(sommet, prefixeInverse);
}

void TraitementGraphe::ordreSuffixeInverse(Sommet<DonneesSommet>* sommet){
	suffixeInverse = new Maillon<Sommet<DonneesSommet>>(sommet, suffixeInverse);
}

void TraitementGraphe::NumeroteGraphe(){
	Maillon<Sommet<DonneesSommet>> * temp;
	Maillon<Sommet<DonneesSommet>> * temp2;
	int num = 0;

	parcoursDFS(&TraitementGraphe::ordrePrefixeInverse, &TraitementGraphe::ordreSuffixeInverse);

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
		temp->valeur->info.cout = INFINI;
		temp->valeur->marque = false;

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

unsigned ** TraitementGraphe::matriceAjdacence(unsigned(DonneesArete::*critere)(void)){

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);

	unsigned** matrice = new unsigned*[n];

	for (unsigned i = 0; i < n; i++)
		matrice[i] = new unsigned[n];

	Maillon<Sommet<DonneesSommet>> * temp = graphe->lSommets;
	Maillon<Sommet<DonneesSommet>> * temp2 = graphe->lSommets;

	int i =0,j = 0;

	while (temp != NULL) {
		temp->valeur->info.etat = DonneesSommet::LIBRE;
		temp->valeur->info.pere = NULL;
		temp->valeur->info.cout = INFINI;
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
					res[i][j] = INFINI;
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

	unsigned ** matrice = matriceAjdacence(&DonneesArete::estPresent);

	unsigned ** matricePresence = FloydWarshall(matrice, n);

	unsigned max = matricePresence[0][0];

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (matricePresence[i][j] > max && matricePresence[i][j] < INFINI)
				max = matricePresence[i][j];
		}
	}
	return max;
}

bool TraitementGraphe::estSansCycle(){

	Maillon<Sommet<DonneesSommet>> * temp = graphe->lSommets;
	unsigned nbSommet = 0;

	while (temp != NULL) {
		Maillon<Arete<DonneesArete, DonneesSommet>> * temp1 = graphe->lAretes;

		while (temp1 != NULL) {
			if (temp1->valeur->fin == temp->valeur)
				temp->valeur->info.degreEntrant++;
			temp1 = temp1->suivant;
		}
		temp = temp->suivant;
	}

	temp = graphe->lSommets;
	Maillon<Sommet<DonneesSommet>> * aTraiter = NULL;
	
	while (temp != NULL) {

		if (temp->valeur->info.degreEntrant == 0) {
			aTraiter = new Maillon<Sommet<DonneesSommet>>(temp->valeur, aTraiter);
			nbSommet++;
		}
		temp = temp->suivant;
	}
	
	while (aTraiter != NULL) {
		Sommet<DonneesSommet> *s = Maillon<Sommet<DonneesSommet>>::depiler(aTraiter);

		Maillon<Sommet<DonneesSommet>> * voisinsS = graphe->sommetsAdjacents(s);
		Maillon<Sommet<DonneesSommet>> * temp2 = voisinsS;

		while (temp2 != NULL) {			
			temp2->valeur->info.degreEntrant--;

			if (temp2->valeur->info.degreEntrant == 0) {
				aTraiter = new Maillon<Sommet<DonneesSommet>>(temp2->valeur, aTraiter);
				nbSommet++;
			}

			temp2 = temp2->suivant;
		}
		
		Maillon<Sommet<DonneesSommet>>::effacePointeurs(voisinsS);
	}

	return nbSommet == Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);
}

vector<Maillon<Sommet<DonneesSommet>>*> TraitementGraphe::composantesFortementConnexes() {

	libererToutSommet();

	unsigned n = Maillon<Sommet<DonneesSommet>>::taille(graphe->lSommets);
	unsigned ** matriceAdjacence = matriceAjdacence(&DonneesArete::getDistance);
	unsigned** matriceFloyd = FloydWarshall(matriceAdjacence, n);

	int i=0, j=0;

	Maillon<Sommet<DonneesSommet>> * temp = graphe->lSommets;
	Maillon<Sommet<DonneesSommet>> * composante = NULL;
	vector<Maillon<Sommet<DonneesSommet>>*> compConnexes;

	while (temp != NULL) {
		
		if (!graphe->lSommets->get(j)->marque) {

			composante = new Maillon<Sommet<DonneesSommet>>(temp->valeur, NULL);
			temp->valeur->marque = true;

			while (i < n) {

				if (matriceFloyd[i][j] != INFINI && matriceFloyd[i][j] != 0
					&& matriceFloyd[j][i] != INFINI && matriceFloyd[j][i] != 0) {

					if (!graphe->lSommets->get(i)->marque) {
						composante = new Maillon<Sommet<DonneesSommet>>(
							graphe->lSommets->get(i), composante);
						graphe->lSommets->get(i)->marque = true;
					}
				}

				i++;
			}

		}

		if (composante != NULL) {
			compConnexes.push_back(composante);
			composante = NULL;
		}

		j++;
		i = 0;
		temp = temp->suivant;
	}


	return compConnexes;
}

Sommet<DonneesSommet>* TraitementGraphe::trouverSommetParNom(Maillon<Sommet<DonneesSommet>>* lSommets, const string& nom) {

	Maillon<Sommet<DonneesSommet>> * temp = lSommets;

	while (temp != NULL) {
		if (temp->valeur->info.nom == nom)
			return temp->valeur;

		temp = temp->suivant;
	}

	throw Erreur("Aucun sommet ne porte ce nom");

}

vector<string> TraitementGraphe::listeNomsSommets()
{
	vector<string> lNoms;
	Maillon<Sommet<DonneesSommet>>* temp = graphe->lSommets;
	while (temp != NULL) {
		lNoms.push_back(temp->valeur->info.nom);
		temp = temp->suivant;
	}
	return lNoms;
}


