#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"

using namespace std;

template <class infoSommet>
class Sommet : public GElement<infoSommet>
{
public:
int degre;
bool marque;

Sommet(const int clef, const infoSommet & v):GElement<infoSommet>(clef,v),degre(0), marque(false){ }

operator string () const;

};

template <class infoSommet>
Sommet<infoSommet>::operator string () const
{
ostringstream oss;

oss <<"Sommet{"<<endl;
oss << GElement<infoSommet>::operator string()<<endl;
oss<<"degre = " << degre << endl;
oss<<"}"<<endl;
return oss.str();
}

template <class infoSommet>
ostream & operator << (ostream & os, const Sommet<infoSommet> & sommet)
{
return os << (string)sommet;
}
