#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Erreur.h"

using namespace std;

template <class Element>
class Maillon
{
public:
	Element * valeur;
	Maillon<Element> * suivant;

	Maillon(Element * v, Maillon<Element> * s) :valeur(v), suivant(s) {}

	static const string toString(const Maillon<Element> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const Maillon<Element> * l);

	/**
		* recopie les pointeurs
	**/
	static  Maillon<Element> * copiePointeurs(Maillon<Element> * l);

	/**
	 * recopie  toutes les données *v
	 * */
	static  Maillon<Element> * copieElement(const Maillon<Element> * l);

	/**
	 * recopie  toutes les données *v à l'aide de la méthode v->copie()
	 * */
	static Maillon<Element> * copieAvecMethode(const Maillon<Element> * l);

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
	static void concatene(Maillon<Element> * & l1, Maillon<Element> *  l2);

	/**
	 * efface toute la liste mais n'efface pas les données *v
	 * */
	static void effacePointeurs(Maillon<Element>* & l);

	/**
	 * efface toute la liste et efface toutes les données *v
	 * */
	static void effaceObjets(Maillon<Element>* & l);

	/**
	 * recherche si a appartient à l
	 * */
	static  Maillon< Element > * appartient(const Element * a, Maillon<Element> * l);

	/**
	 * HYPOTHESES : l'évaluation de condition() produit un booléen
	 * condition est supposée avoir la signature : bool condition( const T * a)
	 *
	 * renvoie un pointeur sur le 1er maillon de l vérifiant la condition "condition"
	 * renvoie NULL si aucun maillon ne vérifie la condition
	 *
	 * */
	template <class FONCTEUR>
	static Maillon< Element > * appartient(Maillon<Element> * l, const FONCTEUR & condition);

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
	static void insertionOrdonnee(Element * a, Maillon<Element> * & l, bool(*estPlusPetitOuEgal)(const Element * a1, const Element * a2));

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
	static bool retire(const Element * a, Maillon<Element> * & l);

	/**
	 * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
	 *
	 * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
	 * lance une exception Erreur si l == NULL à l'appel
	 *
	 * */
	static Element * depiler(Maillon<Element> * & l);

	Element * get(int i);

};

template<class Element>
ostream& operator <<(ostream & os, const Maillon<Element> * p) { return os << Maillon<Element>::toString(p); }

template <class Element>
const string Maillon<Element>::toString(const Maillon<Element> * p, const char * debut, const char * separateur, const char * fin) {
	Maillon<Element> * r;
	ostringstream oss;

	for (r = (Maillon<Element>*) p, oss << debut; r; r = r->suivant) {
		oss << *(r->valeur);
		if (r->suivant != nullptr) {
			oss << separateur;
		}
	}

	oss << fin;
	return oss.str();
}

template <class Element>
void Maillon<Element>::concatene(Maillon<Element> * & l1, Maillon<Element> * l2)
{
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concatene(l1->suivant, l2);
}

template <class Element>
int Maillon<Element>::taille(const Maillon<Element> * l)
{
	if (!l) return 0;
	else
		return 1 + Maillon<Element>::taille(l->suivant);
}

template <class Element>
Maillon<Element> * Maillon<Element>::copiePointeurs(Maillon<Element> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<Element>(l->valeur, Maillon<Element>::copiePointeurs(l->suivant));
}

template <class Element>
Maillon<Element> * Maillon<Element>::copieElement(const Maillon<Element> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<Element>(new Element(*(l->valeur)), Maillon<Element>::copieElement(l->suivant));
}

template <class Element>
Maillon<Element> * Maillon<Element>::copieAvecMethode(const Maillon<Element> * l)
{
	if (!l)
		return NULL;
	else
		return new Maillon<Element>(l->valeur->copie(), Maillon<Element>::copieAvecMethode(l->suivant));
}

template <class Element>
void Maillon<Element>::effacePointeurs(Maillon<Element>* & l)
{
	if (l)
	{
		Maillon<Element>::effacePointeurs(l->suivant);
		delete l; l = NULL;
	}
}

template <class Element>
void Maillon<Element>::effaceObjets(Maillon<Element>* & l)
{
	if (l)
	{
		Maillon<Element>::effaceObjets(l->suivant);
		delete l->valeur; delete l; l = NULL;
	}
}

template <class Element>
Maillon< Element > * Maillon< Element >::appartient(const Element * a, Maillon<Element> * l)
{
	for (; l; l = l->suivant)
		if (a == l->valeur)
			return l;

	return l;
}

template <class Element>
template <class FONCTEUR>
Maillon< Element > * Maillon< Element >::appartient(Maillon<Element> * l, const FONCTEUR & condition)
{
	for (; l; l = l->suivant)
		if (condition(l->valeur))
			return l;

	return l;
}

template<class Element>
void Maillon<Element>::insertionOrdonnee(Element * a, Maillon<Element> * & l, bool(*estPlusPetitOuEgal)(const Element * a1, const Element * a2))
{
	if (!l || estPlusPetitOuEgal(a, l->valeur))
		l = new Maillon<Element>(a, l);
	else
		Maillon<Element>::insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
}

template<class Element>
bool Maillon<Element>::retire(const Element * a, Maillon<Element> * & l)
{
	if (!l)
		return false;
	else
		if (a == l->valeur)
		{
			Maillon<Element> * r = l; l = l->suivant; delete r;
			return true;
		}
		else
			return Maillon<Element>::retire(a, l->suivant);
}

template <class Element>
Element * Maillon<Element>::depiler(Maillon<Element> * & l)
{
	if (!l) throw Erreur("impossible de dépiler une pile vide");
	Element * a = l->valeur;
	Maillon<Element> * tete = l;

	l = l->suivant; delete tete;
	return a;

}

template<class Element>
inline Element * Maillon<Element>::get(int i)
{
	int j = 0;

	Maillon<Element> * temp = this;

	for (int j = 0; j < i; j++){
		temp = temp->suivant;
	}

	return temp->valeur;
}

template <class Element>
Maillon<Element> * reunion(Maillon<Element> * l1, Maillon<Element> * l2)
{
	Maillon<Element> * r = Maillon<Element>::copiePointeurs(l2);
	Maillon<Element> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->suivant)
		if (!Maillon<Element>::appartient(pl1->valeur, r))
			r = new Maillon<Element>(pl1->valeur, r);

	return r;
}

template <class Element>
void partage(Maillon<Element> * & p, Maillon<Element> * & p1)
{
	if (p == NULL || p->suivant == NULL)
		p1 = NULL;
	else
	{
		Maillon<Element> *  r1, *r2;

		r1 = p->suivant;
		r2 = r1->suivant;

		partage(r2, p1);

		r1->suivant = p1;
		p->suivant = r2;
		p1 = r1;
	}
}

template <class Element>
void fusion(Maillon<Element> * & p1, Maillon<Element> * & p2, bool(*estPlusPetitOuEgal)(const Element * a1, const Element * a2))
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
		Maillon<Element> * r;
		r = p1->suivant;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->suivant = r;
	}
	else // p1->v > p2->v
	{
		Maillon<Element> * r;
		r = p2->suivant;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->suivant = p1;
		p1 = p2;
		p2 = NULL;
	}
}

template <class Element>
void tri(Maillon<Element>* & p, bool(*estPlusPetitOuEgal)(const Element * a1, const Element * a2))
{
	if (p != NULL && p->suivant != NULL)
	{
		Maillon<Element> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}




