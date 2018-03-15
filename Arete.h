#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Sommet.h"

using namespace std;

template <class infoArete, class infoSommet>
class Arete
{
public:
Sommet <infoSommet> *debut, *fin;
infoArete info;

Arete(const infoArete & v, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin) : debut(debut), fin(fin), info(v)
{
debut->degre++; fin->degre++;
}

~Arete() { debut->degre--; fin->degre--; }

operator string () const;

bool estEgal( const Sommet<infoSommet> * s1, const Sommet<infoSommet> * s2) const;
};

template <class infoArete, class infoSommet>
Arete<infoArete,infoSommet>::operator string () const
{
ostringstream oss;

oss <<"Arete{"<< endl;
oss << "Debut = " << *debut<< endl;
oss << "Fin = " << *fin << endl;
oss << endl << "infos : " << info << endl;
oss << "}" <<endl;
return oss.str();

}

template <class infoArete, class infoSommet>
ostream & operator << (ostream & os, const Arete<infoArete,infoSommet> & arete)
{
return os << (string)arete;
}

template <class infoArete, class infoSommet>
bool Arete<infoArete,infoSommet>::estEgal( const Sommet<infoSommet> * s1, const Sommet<infoSommet> * s2) const
{
return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
}
