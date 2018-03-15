#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Erreur.h"

using namespace std;

template <class infoSommet>
class Maillon
{
public:
	infoSommet * valeur;
	Maillon<infoSommet> * suivant;

	Maillon(infoSommet * v, Maillon<infoSommet> * s) :valeur(v), suivant(s) {}

	static const string toString(const Maillon<infoSommet> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const Maillon<infoSommet> * l);

	/**
		* recopie les pointeurs
	**/
	static  Maillon<infoSommet> * copiePointeurs(Maillon<infoSommet> * l);

	/**
	 * recopie  toutes les données *v
	 * */
	static  Maillon<infoSommet> * copieElement(const Maillon<infoSommet> * l);

	/**
	 * recopie  toutes les données *v à l'aide de la méthode v->copie()
	 * */
	static Maillon<infoSommet> * copieAvecMethode(const Maillon<infoSommet> * l);

	/**
	 * concatène l2 à la fin de l1. Ne crée aucun maillon.
	 *
	 * En sortie l1 pointe sur le début de la concaténation
	 *
	 * DONNEES : l1, l2 (peuvent être vides toutes les deux)
	 *
	 * RESULTATS : l1 contenant la concaténation
	 *
	 * Exemple : si en entrée l1 = (2,5,4) et l2 = (7,11) alors en sortie l1 = (2,5,4,7,11) et l2 = (7,11)
	 * */
	static void concatene(Maillon<infoSommet> * & l1, Maillon<infoSommet> *  l2);

	/**
	 * efface toute la liste mais n'efface pas les données *v
	 * */
	static void effacePointeurs(Maillon<infoSommet>* & l);

	/**
	 * efface toute la liste et efface toutes les données *v
	 * */
	static void effaceObjets(Maillon<infoSommet>* & l);

	/**
	 * recherche si a appartient à l
	 * */
	static  Maillon< infoSommet > * appartient(const infoSommet * a, Maillon<infoSommet> * l);

	/**
	 * HYPOTHESES : l'évaluation de condition() produit un booléen
	 * condition est supposée avoir la signature : bool condition( const T * a)
	 *
	 * renvoie un pointeur sur le 1er maillon de l vérifiant la condition "condition"
	 * renvoie NULL si aucun maillon ne vérifie la condition
	 *
	 * */
	template <class FONCTEUR>
	static Maillon< infoSommet > * appartient(Maillon<infoSommet> * l, const FONCTEUR & condition);

	/**
	 * Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
	 * Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
	 *
	 * A l'instar de la méthode précédente (appartient), cette fonction aurait aussi pu être écrite avec un argument foncteur
	 *
	 * Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
	 * Résultats : l modifiée par l'insertion
	 * Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
	 *
	 * */
	static void insertionOrdonnee(infoSommet * a, Maillon<infoSommet> * & l, bool(*estPlusPetitOuEgal)(const infoSommet * a1, const infoSommet * a2));

	/**
	 * retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
	 *
	 * L'élément trouvé n'est pas effacé
	 *
	 * La comparaison est faite sur les pointeurs
	 *
	 * Données : a, l
	 * Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
	 * */
	static bool retire(const infoSommet * a, Maillon<infoSommet> * & l);

	/**
	 * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
	 *
	 * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
	 * lance une exception Erreur si l == NULL à l'appel
	 *
	 * */
	static infoSommet * depiler(Maillon<infoSommet> * & l);

};

template<class infoSommet>
ostream& operator <<(ostream & os, const Maillon<infoSommet> * p) { return os << Maillon<infoSommet>::toString(p); }

template <class infoSommet>
const string Maillon<infoSommet>::toString(const Maillon<infoSommet> * p, const char * debut, const char * separateur, const char * fin) {
	Maillon<infoSommet> * r;
	ostringstream oss;

	for (r = (Maillon<infoSommet>*) p, oss << debut; r; r = r->suivant) {
		oss << *(r->valeur);
		if (r->suivant != nullptr) {
			oss << separateur;
		}
	}

	oss << fin;
	return oss.str();
}

template <class infoSommet>
void Maillon<infoSommet>::concatene(Maillon<infoSommet> * & l1, Maillon<infoSommet> * l2)
{
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concatene(l1->suivant, l2);
}

template <class infoSommet>
int Maillon<infoSommet>::taille(const Maillon<infoSommet> * l)
{
	if (!l) return 0;
	else
		return 1 + Maillon<infoSommet>::taille(l->suivant);
}

template <class infoSommet>
Maillon<infoSommet> * Maillon<infoSommet>::copiePointeurs(Maillon<infoSommet> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<infoSommet>(l->valeur, Maillon<infoSommet>::copiePointeurs(l->suivant));
}

template <class infoSommet>
Maillon<infoSommet> * Maillon<infoSommet>::copieElement(const Maillon<infoSommet> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<infoSommet>(new infoSommet(*(l->valeur)), Maillon<infoSommet>::copieElement(l->suivant));
}

template <class infoSommet>
Maillon<infoSommet> * Maillon<infoSommet>::copieAvecMethode(const Maillon<infoSommet> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<infoSommet>(l->valeur->copie(), Maillon<infoSommet>::copieAvecMethode(l->suivant));
}

template <class infoSommet>
void Maillon<infoSommet>::effacePointeurs(Maillon<infoSommet>* & l)
{
	if (l)
	{
		Maillon<infoSommet>::effacePointeurs(l->suivant);
		delete l; l = NULL;
	}
}

template <class infoSommet>
void Maillon<infoSommet>::effaceObjets(Maillon<infoSommet>* & l)
{
	if (l)
	{
		Maillon<infoSommet>::effaceObjets(l->suivant);
		delete l->valeur; delete l; l = NULL;
	}
}

template <class infoSommet>
Maillon< infoSommet > * Maillon< infoSommet >::appartient(const infoSommet * a, Maillon<infoSommet> * l)
{
	for (; l; l = l->suivant)
		if (a == l->valeur)
			return l;

	return l;
}

template <class infoSommet>
template <class FONCTEUR>
Maillon< infoSommet > * Maillon< infoSommet >::appartient(Maillon<infoSommet> * l, const FONCTEUR & condition)
{
	for (; l; l = l->suivant)
		if (condition(l->valeur))
			return l;

	return l;
}

template<class infoSommet>
void Maillon<infoSommet>::insertionOrdonnee(infoSommet * a, Maillon<infoSommet> * & l, bool(*estPlusPetitOuEgal)(const infoSommet * a1, const infoSommet * a2))
{
	if (!l || estPlusPetitOuEgal(a, l->valeur))
		l = new Maillon<infoSommet>(a, l);
	else
		Maillon<infoSommet>::insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
}

template<class infoSommet>
bool Maillon<infoSommet>::retire(const infoSommet * a, Maillon<infoSommet> * & l)
{
	if (!l)
		return false;
	else
		if (a == l->valeur)
		{
			Maillon<infoSommet> * r = l; l = l->suivant; delete r;
			return true;
		}
		else
			return Maillon<infoSommet>::retire(a, l->suivant);
}

template <class infoSommet>
infoSommet * Maillon<infoSommet>::depiler(Maillon<infoSommet> * & l)
{
	if (!l) throw Erreur("impossible de dépiler une pile vide");
	infoSommet * a = l->valeur;
	Maillon<infoSommet> * tete = l;

	l = l->suivant; delete tete;
	return a;

}

template <class infoSommet>
Maillon<infoSommet> * reunion(Maillon<infoSommet> * l1, Maillon<infoSommet> * l2)
{
	Maillon<infoSommet> * r = Maillon<infoSommet>::copiePointeurs(l2);
	Maillon<infoSommet> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->suivant)
		if (!Maillon<infoSommet>::appartient(pl1->valeur, r))
			r = new Maillon<infoSommet>(pl1->valeur, r);

	return r;
}

template <class infoSommet>
void partage(Maillon<infoSommet> * & p, Maillon<infoSommet> * & p1)
{
	if (p == NULL || p->suivant == NULL)
		p1 = NULL;
	else
	{
		Maillon<infoSommet> *  r1, *r2;

		r1 = p->suivant;
		r2 = r1->suivant;

		partage(r2, p1);

		r1->suivant = p1;
		p->suivant = r2;
		p1 = r1;
	}
}

template <class infoSommet>
void fusion(Maillon<infoSommet> * & p1, Maillon<infoSommet> * & p2, bool(*estPlusPetitOuEgal)(const infoSommet * a1, const infoSommet * a2))
{
	if (!p2) return; // p2 est vide, il n'y a rien à faire

	if (!p1) // p1 est vide et p2 ne l'est pas
	{
		p1 = p2; p2 = NULL;
		return;
	}

	// à présent, p1 et p2 sont non vides

	if (estPlusPetitOuEgal(p1->valeur, p2->valeur)) // p1->v <= p2->v
	{
		Maillon<infoSommet> * r;
		r = p1->suivant;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->suivant = r;
	}
	else // p1->v > p2->v
	{
		Maillon<infoSommet> * r;
		r = p2->suivant;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->suivant = p1;
		p1 = p2;
		p2 = NULL;
	}
}

template <class infoSommet>
void tri(Maillon<infoSommet>* & p, bool(*estPlusPetitOuEgal)(const infoSommet * a1, const infoSommet * a2))
{
	if (p != NULL && p->suivant != NULL)
	{
		Maillon<infoSommet> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}




