#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"
#include "Sommet.h"

using namespace std;

template <class infoArete, class infoSommet>
class Arete : public GElement<infoArete>
{
public:
Sommet <infoSommet> *debut, *fin;

Arete( const int clef, const infoArete & v, Sommet<infoSommet> * debut, Sommet<infoSommet> * fin) : GElement<infoArete>( clef, v) ,debut( debut), fin( fin)
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
oss << GElement<infoArete>::operator string()<<endl;
oss << "clef debut = " << debut->clef<< endl;
oss << "clef fin = " << fin->clef << endl;
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
