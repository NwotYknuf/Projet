#pragma once

#include <utility>
#include "Maillon.h"
#include "Erreur.h"
#include "Sommet.h"
#include "Arete.h"

template <class infoArete, class infoSommet>
class Graphe {
protected:

	int prochaineClef;

public:

	Maillon< Sommet<infoSommet> > * lSommets; // liste de sommets
	Maillon< Arete<infoArete, infoSommet> > * lAretes; // liste d'arêtes

private:

	void majProchaineClef(const int clef) { prochaineClef = max(1 + clef, prochaineClef); }
	
	Sommet<infoSommet> * creeSommetSansMAJ(const int clef, const infoSommet & info);

	Arete<infoArete, infoSommet> * creeAreteSansMAJ(const int clef, const infoArete & info, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin);
	
	Sommet<infoSommet> * creeSommet(const int clef, const infoSommet & info) { majProchaineClef(clef); return creeSommetSansMAJ(clef, info); }

	Arete<infoArete, infoSommet> * creeArete(const int clef, const infoArete & info, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin) {
		majProchaineClef(clef);
		return creeAreteSansMAJ(clef, info, debut, fin);
	}

public:
	Sommet<infoSommet> * creeSommet(const infoSommet & info) { return creeSommetSansMAJ(prochaineClef++, info); }

	Arete<infoArete, infoSommet> * creeArete(const infoArete & info, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin) { return creeAreteSansMAJ(prochaineClef++, info, debut, fin); }

private:

	void copie(const Graphe<infoArete, infoSommet> & graphe);

	void effaceTout();

public:

	Graphe() : prochaineClef(0), lSommets(NULL), lAretes(NULL) {}

	Graphe(const Graphe<infoArete, infoSommet> & graphe) : Graphe() { this->copie(graphe); }

	const Graphe<infoArete, infoSommet> & operator = (const Graphe<infoArete, infoSommet> & graphe) { this->effaceTout(); this->copie(graphe); return *this; }

	~Graphe() { this->effaceTout(); }

	int nombreSommets() const { return Maillon< Sommet<infoSommet> >::taille(lSommets); }

	int nombreAretes() const { return Maillon< Arete<infoArete, infoSommet> >::taille(lAretes); }

	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > >  *  listeAdjacence(const Sommet<infoSommet> * sommet) const;

	Maillon< Arete<infoArete, infoSommet> > *  aretesAdjacentes(const Sommet<infoSommet> * sommet) const;

	Maillon< Sommet<infoSommet> > *  sommetsAdjacents(const Sommet<infoSommet> * sommet) const;

	Arete<infoArete, infoSommet> * trouveAreteParSommets(const Sommet<infoSommet> * s1, const Sommet<infoSommet> * s2) const;

	operator string() const;

	template< class FENETRE>
	bool dessineToutesAretes(FENETRE & fenetre) const;

	template< class FENETRE>
	bool dessineTousSommets(FENETRE & fenetre) const;

	template  <class FENETRE>
	bool dessine(FENETRE & fenetre) const;

	template<class Traitement>
	void parcoursComposantes(Sommet<infoSommet> * sommet, Traitement traitementPrefixe, Traitement traitementSuffixe);

	template<class Traitement>
	void parcoursDFS(Traitement traitementPrefixe, Traitement traitementSuffixe);

};

template <class infoArete, class infoSommet>
ostream & operator << (ostream & os, const Graphe<infoArete, infoSommet> & gr) { return os << (string)gr; }

template <class infoArete, class infoSommet>
Sommet<infoSommet> * Graphe<infoArete, infoSommet>::creeSommetSansMAJ(const int clef, const infoSommet & info)
{
	Sommet<infoSommet> * sommetCree = new Sommet<infoSommet>(clef, info);
	lSommets = new Maillon< Sommet<infoSommet> >(sommetCree, lSommets);

	return sommetCree;
}

template <class infoArete, class infoSommet>
Arete<infoArete, infoSommet> * Graphe<infoArete, infoSommet>::creeAreteSansMAJ(const int clef, const infoArete & info, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin)
{

	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!Maillon< Sommet<infoSommet> >::appartient(debut, lSommets)) throw Erreur("début d'arête non défini");
	if (!Maillon< Sommet<infoSommet> >::appartient(fin, lSommets)) throw Erreur("fin d'arête non définie");

	Arete<infoArete, infoSommet> *  nouvelleArete = new Arete<infoArete, infoSommet>(clef, info, debut, fin);

	lAretes = new Maillon< Arete<infoArete, infoSommet> >(nouvelleArete, lAretes);

	return nouvelleArete;
}

template <class infoSommet>
class SommetDejaPresentDansLaCopie
{
public:
	const Sommet<infoSommet> * s;
	SommetDejaPresentDansLaCopie(const Sommet<infoSommet> * s) :s(s) {}
	bool operator () (const Sommet<infoSommet> * sommet) const { return sommet->clef == s->clef; }
};

template <class infoArete, class infoSommet>
void Graphe<infoArete, infoSommet>::copie(const Graphe<infoArete, infoSommet> & graphe)
{
	const Maillon<Sommet<infoSommet>> * pS;

	// -------------- d'abord on recopie les sommets --------------------

	for (pS = graphe.lSommets; pS; pS = pS->suivant)
	{									// parcourt les sommets du graphe "graphe" et les crée un par un dans *this en tant que sommets isolés
		const Sommet<infoSommet> * sommet = pS->valeur;				// sommet courant à recopier
		this->creeSommet(sommet->clef, sommet->v);		// on crée la copie du sommet courant avec la même clef
	}


	// -------------------- et maintenant on recopie les arêtes --------------------

	// attention, la recopie des arêtes est plus compliquée car il faut rebrancher les arêtes sur les nouveaux sommets qui viennent d'être créés.
	// Pour retrouver les "bons sommets" on utilise les clefs qui ont été conservées

	const Maillon<Arete<infoArete, infoSommet>> * pA;
	for (pA = graphe.lAretes; pA; pA = pA->suivant)	// parcourt les arêtes de l'ancien graphe et les recopie une par une
	{
		const Arete<infoArete, infoSommet> * a = pA->valeur;			// arête courante à recopier
		Sommet<infoSommet> * d, *f;						// le début et la fin de la nouvelle arête qui va être créée
		Maillon< Sommet<infoSommet> > * p;				// pour retrouver d et f dans la nouvelle liste de sommets grâce aux clefs qui ont été conservées

		// on recherche d dans la nouvelle liste de sommets grâce à sa clef
		SommetDejaPresentDansLaCopie<infoSommet> conditionDebut(a->debut);
		p = Maillon< Sommet<infoSommet> >::appartient(lSommets, conditionDebut);
		d = p->valeur;

		// on recherche f dans la nouvelle liste de sommets grâce à sa clef
		SommetDejaPresentDansLaCopie<infoSommet> conditionFin(a->fin);
		p = Maillon< Sommet<infoSommet> >::appartient(lSommets, conditionFin);
		f = p->valeur;

		this->creeArete(a->clef, a->v, d, f);
	}
}

template <class infoArete, class infoSommet>
void Graphe<infoArete, infoSommet>::effaceTout()
{
	Maillon< Arete<infoArete, infoSommet>>::effaceObjets(this->lAretes);
	Maillon<Sommet<infoSommet> >::effaceObjets(this->lSommets);
	this->prochaineClef = 0;
}

template <class infoArete, class infoSommet>
Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > >  *  Graphe<infoArete, infoSommet>::listeAdjacence(const Sommet<infoSommet> * sommet) const
{
	const Maillon< Arete<infoArete, infoSommet> > * l;

	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > > * r;

	for (l = lAretes, r = NULL; l; l = l->suivant)

		if (sommet == l->valeur->debut)
			r = new Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > >(new pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* >(l->valeur->fin, l->valeur), r);
	
	return r;
}

template <class infoArete, class infoSommet>
Maillon< Arete<infoArete, infoSommet> > *  Graphe<infoArete, infoSommet>::aretesAdjacentes(const Sommet<infoSommet> * sommet) const
{
	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > > * ladj = this->listeAdjacence(sommet);
	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > > * l;

	Maillon< Arete<infoArete, infoSommet> > * r;

	for (l = ladj, r = NULL; l; l = l->suivant)
		r = new Maillon< Arete<infoArete, infoSommet> >(l->valeur->second, r);

	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > >::effaceObjets(ladj);

	return r;
}

template <class infoArete, class infoSommet>
Maillon< Sommet<infoSommet> > *  Graphe<infoArete, infoSommet>::sommetsAdjacents(const Sommet<infoSommet> * sommet) const
{
	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > > * ladj = this->listeAdjacence(sommet);
	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > > * l;

	Maillon< Sommet<infoSommet> > * r;

	for (l = ladj, r = NULL; l; l = l->suivant)
		r = new Maillon< Sommet<infoSommet> >(l->valeur->first, r);

	Maillon< pair< Sommet<infoSommet> *, Arete<infoArete, infoSommet>* > >::effaceObjets(ladj);

	return r;
}

template <class infoArete, class infoSommet>
Arete<infoArete, infoSommet> * Graphe<infoArete, infoSommet>::trouveAreteParSommets(const Sommet<infoSommet> * s1, const Sommet<infoSommet> * s2) const
{
	Maillon<Arete<infoArete, infoSommet> > * l;

	for (l = this->lAretes; l; l = l->suivant)
		if (l->valeur->estEgal(s1, s2))
			return l->valeur;

	return NULL;
}

template <class infoArete, class infoSommet>
Graphe<infoArete, infoSommet>::operator string() const
{
	ostringstream oss;
	oss << "Graphe" << endl << endl;
	oss << "- prochaine clef = " << this->prochaineClef << endl<<endl;
	oss << "- nombre de sommets = " << this->nombreSommets() << endl << endl;
	oss << "- nombre d'aretes = " << this->nombreAretes() << endl << endl;
	oss << "- Liste des sommets : " << endl<<endl;

	oss << Maillon<Sommet<infoSommet> >::toString(lSommets, "", "\n", "\n");

	oss << "- Liste des arretes : " << endl;

	oss << Maillon<Arete<infoArete, infoSommet> >::toString(lAretes, "", "\n", "\n");
	return oss.str();
}

template <class infoArete, class infoSommet>
template< class FENETRE>
bool Graphe<infoArete, infoSommet>::dessineToutesAretes(FENETRE & fenetre) const
{

	// ------------------------ on dessine les arêtes --------------------------

	Maillon< Arete<infoArete, infoSommet>> * pA;
	for (pA = this->lAretes; pA; pA = pA->suivant)
		if (!fenetre.dessine(pA->valeur)) return false; // tente de dessiner puis retourne false en cas d'échec

	return true;
}

template <class infoArete, class infoSommet>
template< class FENETRE>
bool Graphe<infoArete, infoSommet>::dessineTousSommets(FENETRE & fenetre) const
{

	// ------------------------ on dessine les sommets --------------------------

	Maillon< Sommet<infoSommet>> * pS;
	for (pS = this->lSommets; pS; pS = pS->suivant)
		if (!fenetre.dessine(pS->valeur)) return false;	// tente de dessiner puis retourne false en cas d'échec

	return true;
}

template <class infoArete, class infoSommet>
template< class FENETRE>
bool Graphe<infoArete, infoSommet>::dessine(FENETRE & fenetre) const
{

	// ------------------------ on dessine les arêtes --------------------------

	if (!this->dessineToutesAretes(fenetre)) return false;

	// ------------------------ on dessine les sommets --------------------------

	return this->dessineTousSommets(fenetre);
}

template<class infoArete, class infoSommet>
template<class Traitement>
inline void Graphe<infoArete, infoSommet>::parcoursComposantes(Sommet<infoSommet>* sommet, Traitement traitementPrefixe, Traitement traitementSuffixe) {

	sommet->marque = true;
	
	traitementPrefixe(sommet);

	Maillon<Sommet<infoSommet>> * voisins = this->sommetsAdjacents(sommet);
	Maillon<Sommet<infoSommet>> * temp = voisins;

	while (temp != NULL) {
		if (!temp->valeur->marque) 
			parcoursComposantes(temp->valeur, traitementPrefixe, traitementSuffixe);
		temp = temp->suivant;
	}

	traitementSuffixe(sommet);


	Maillon<Sommet<infoSommet>>::effacePointeurs(voisins);
}

template<class infoArete, class infoSommet>
template<class Traitement>
inline void Graphe<infoArete, infoSommet>::parcoursDFS(Traitement traitementPrefixe, Traitement traitementSuffixe)
{
	Maillon<Sommet<infoSommet>>* temp = lSommets;
	while (temp != NULL) {
		if (!temp->valeur->marque) parcoursComposantes(temp->valeur, traitementPrefixe, traitementSuffixe);
		temp = temp->suivant;
	}
}

template <class infoSommet, class FENETRE>
bool dessine(const Maillon<Sommet<infoSommet>> * chemin, FENETRE & fenetre, const unsigned int couleur)
{
	if (!(chemin && chemin->suivant)) // le chemin est vide ou ne contient qu'un sommet : il n'y  a rien à dessiner
		return true;

	else		// le chemin contient au moins une arête
	{
		// on dessine d'abord la 1ère arête

		fenetre.dessine(chemin->valeur, chemin->suivant->valeur, couleur);

		return dessine(chemin->suivant, fenetre, couleur);		// puis on dessine les arêtes suivantes
	}
}
