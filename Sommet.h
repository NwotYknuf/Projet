#pragma once

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class infoSommet>
class Sommet
{
public:
int degre;
bool marque;
infoSommet info;

Sommet(const infoSommet & v) : info(v), degre(0), marque(false) { }

operator string () const;

};

template <class infoSommet>
Sommet<infoSommet>::operator string () const
{
ostringstream oss;

oss <<"Sommet{"<<endl;
oss << "degre = " << degre << endl;
oss << "marque = " << marque ? "oui" : "non";
oss << endl << endl << "infos : " << endl << info << endl;
oss<<"}"<<endl;
return oss.str();
}

template <class infoSommet>
ostream & operator << (ostream & os, const Sommet<infoSommet> & sommet)
{
return os << (string)sommet;
}
